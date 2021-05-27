/*
 * Copyright (c) 2015-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== empty.c ========
 */

#define MSP432
/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>

/* Driver configuration */
#include "ti_drivers_config.h"

/* IGNORAR ISSO */
#include "main_includes.h"

volatile char READING = 0;
volatile unsigned int dt = 0;
volatile unsigned int reading_timer = 0;
volatile unsigned int delta_time = 0;

Timer_Handle timer0;

enum
{
    start,
    send_query,
    receive_rn16,
    send_ack,
    receive_pc,
    send_req_rn,
    receive_handle,
    send_command,
    error,
} COMMUNICATION_STATE;

// Callback for reading RX
void rx_callback(uint_least8_t index)
{
    reading_timer = dt;
    READING = 1;
    dt = 0;
}

// Timer Counter
void timer_callback(uint_least8_t index)
{
    dt = dt + 1;
}

/*
 *  ======== mainThread ========
 */
void* mainThread(void *arg0)
{
    /* Call driver init functions */
    GPIO_init();
    Timer_init();

    // Encoder Driver
    encoder_driver tx_driver;
    tx_driver.port_tx = 0;
    tx_driver.pin_tx = DIGITAL_TX;
    tx_driver.tari = TARI;

    // Decoder Driver
    decoder_driver rx_driver;
    rx_driver.port_rx = 0;
    rx_driver.pin_rx = DIGITAL_RX;
    rx_driver.tari = TARI;
    rx_driver.timeout = COMMUNICATION_TIMEOUT;

    GPIO_setConfig(tx_driver.pin_tx, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(rx_driver.pin_rx,
                   GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_BOTH_EDGES);

    GPIO_setCallback(rx_driver.pin_rx, rx_callback);

    /* Enable interrupts */
    GPIO_enableInt(rx_driver.pin_rx);

    // Configuring timer
    Timer_Params params;
    Timer_Params_init(&params);
    params.period = 100;
    params.periodUnits = Timer_PERIOD_US; // microseconds
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = timer_callback;
    timer0 = Timer_open(CONFIG_TIMER_0, &params);

    query _query;
    ack _ack;
    rn16 _rn16;
    req_rn _req_rn;
    nak _nak;

    unsigned long long query_response = 0;
    unsigned long long ack_response = 0;
    unsigned long long req_rn_response = 0;

    unsigned int query_response_size = 0;
    unsigned int ack_response_size = 0;
    unsigned int req_rn_response_size = 0;
    int comm_error = 0;

    if (Timer_start(timer0) == Timer_STATUS_ERROR)
    {
        while (1)
        {
        }
    }
    crc_16_ccitt_init();

    COMMUNICATION_STATE = start;
    while (1)
    {
        switch (COMMUNICATION_STATE)
        {
        case start:
            _usleep(1000000);
            COMMUNICATION_STATE = send_query;
            break;

        case send_query:
            query_init(&_query, 0, 0, 0, 1, 0, 0, 0);
            query_build(&_query);
            fm0_encoder(_query.result_data, _query.size, tx_driver);
            COMMUNICATION_STATE = receive_rn16;
            break;

        case receive_rn16:
            comm_error = fm0_decoder(&query_response, &query_response_size,
                                     rx_driver);
            if (comm_error || query_response_size != 16)
                COMMUNICATION_STATE = error;
            else
            {
                _rn16.value = query_response;
                _rn16.size = query_response_size;
                COMMUNICATION_STATE = send_ack;
            }
            break;

        case send_ack:
            ack_init(&_ack, _rn16.value);
            ack_build(&_ack);
            fm0_encoder(_ack.result_data, _ack.size, tx_driver);
            COMMUNICATION_STATE = receive_pc;
            break;

        case receive_pc:
            comm_error = fm0_decoder(&ack_response, &ack_response_size,
                                     rx_driver);
            if (comm_error)
                COMMUNICATION_STATE = error;
            else
                COMMUNICATION_STATE = send_req_rn;
            break;

        case send_req_rn:
            req_rn_init(&_req_rn, _rn16.value);
            req_rn_build(&_req_rn);

            fm0_encoder(_req_rn.result_data, _req_rn.size, tx_driver);
            COMMUNICATION_STATE = receive_handle;
            break;

        case receive_handle:
            comm_error = fm0_decoder(&req_rn_response, &req_rn_response_size,
                                     rx_driver);
            if (comm_error)
                COMMUNICATION_STATE = error;
            else
                COMMUNICATION_STATE = send_command;
            break;

        case send_command:
            // Initiate communication
            nak_init(&_nak);
            nak_build(&_nak);
            fm0_encoder(_nak.result_data, _nak.size, tx_driver);
            COMMUNICATION_STATE = start;
            break;

        case error:
            COMMUNICATION_STATE = start;
            break;

        default:
            COMMUNICATION_STATE = error;
            break;
        }
    }
}
