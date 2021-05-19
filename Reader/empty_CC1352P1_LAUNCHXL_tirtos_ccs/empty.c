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
#include <ti/drivers/UART.h>

/* Driver configuration */
#include "ti_drivers_config.h"

/* IGNORAR ISSO */
#include "main_includes.h"

volatile char READING = 0;
volatile unsigned int dt = 0;
volatile unsigned int reading_timer = 0;
volatile unsigned int resultante_tempo = 0;
// UART_Handle uart;
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

void rx_callback(uint_least8_t index)
{
    reading_timer = dt;
    READING = 1;
    dt = 0;
}

void timre_callback(uint_least8_t index)
{
    dt = dt + 1;
}

/*
 *  ======== mainThread ========
 */
void* mainThread(void *arg0)
{
    /* 1 second delay */
    uint32_t time = 1000;

    const char echoPrompt[] = "Echoing characters:\r\n";

    // UART_Handle uart;
    UART_Params uartParams;

    /* Call driver init functions */
    GPIO_init();
    // UART_init();
    Timer_init();

    GPIO_setConfig(DIGITAL_TX, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(DIGITAL_RX, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_BOTH_EDGES);

    GPIO_setCallback(DIGITAL_RX, rx_callback);

    /* Enable interrupts */
    GPIO_enableInt(DIGITAL_RX);

    /* Create a UART with data processing off. */
    // UART_Params_init(&uartParams);
    // uartParams.writeDataMode = UART_DATA_BINARY;
    // uartParams.readDataMode = UART_DATA_BINARY;
    // uartParams.readReturnMode = UART_RETURN_FULL;
    // uartParams.baudRate = 115200;
    // uart = UART_open(CONFIG_UART_0, &uartParams);
    // if (uart == NULL)
    // {
    //     /* UART_open() failed */
    //     while (1)
    //         ;
    // }
    Timer_Params params;

    // Timer_Params_init(&params);
    // params.period = 10;
    // params.periodUnits = Timer_PERIOD_US; // microseconds
    // params.timerMode = Timer_CONTINUOUS_CALLBACK;
    // params.timerCallback = timre_callback;
    // timer0 = Timer_open(CONFIG_TIMER_0, &params);
    Timer_Params_init(&params);
    params.period = 100;
    params.periodUnits = Timer_PERIOD_US; // microseconds
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = timre_callback;
    timer0 = Timer_open(CONFIG_TIMER_0, &params);

    query query;
    ack ack;
    rn16 rn16;
    req_rn req_rn;
    nak nak;

    unsigned int query_response = 0;
    unsigned int ack_response = 0;
    unsigned int req_rn_response = 0;
    
    unsigned int query_response_size = 0;
    unsigned int ack_response_size = 0;
    unsigned int req_rn_response_size = 0;

    int comm_error = 0;
    
    if (Timer_start(timer0) == Timer_STATUS_ERROR) { while (1){} }

    char papa[32];
    // UART_write(uart, "Vai comecar: ", sizeof("Vai comecar: "));
    COMMUNICATION_STATE = start;
    while (1)
    {
        switch (COMMUNICATION_STATE)
        {
            case start:
                COMMUNICATION_STATE = send_query;
                break;

            case send_query:
                query_init(&query, 0, 0, 0, 1, 0, 0, 0);
                query_build(&query);
                fm0_encoder(query.result_data, query.size, TARI, DIGITAL_TX, 0);
                COMMUNICATION_STATE = receive_rn16;
                break;

            case receive_rn16:
                comm_error = fm0_decoder(TARI, &query_response, &query_response_size, DIGITAL_RX, 0, COMMUNICATION_TIMEOUT);
                if (comm_error || query_response_size!=16)
                    COMMUNICATION_STATE = error;
                else {
                    rn16.value = query_response;
                    rn16.size = query_response_size;
                    COMMUNICATION_STATE = send_ack;
                }
                break;

            case send_ack:
                ack_init(&ack, rn16.value);
                ack_build(&ack);
                fm0_encoder(ack.result_data, ack.size, TARI, DIGITAL_TX, 0);
                COMMUNICATION_STATE = receive_pc;
                break;
            
            case receive_pc:
                comm_error = fm0_decoder(TARI, &ack_response, &ack_response_size, DIGITAL_RX, 0, COMMUNICATION_TIMEOUT);
                if (comm_error)
                    COMMUNICATION_STATE = error;
                else
                    COMMUNICATION_STATE = send_req_rn;
                break;

            case send_req_rn:
                req_rn_init(&req_rn, rn16.value, 0x10);
                req_rn_build(&req_rn);
                fm0_encoder(req_rn.result_data, req_rn.size, TARI, DIGITAL_TX, 0);
                COMMUNICATION_STATE = receive_handle;
                break;

            case receive_handle:
                comm_error = fm0_decoder(TARI, &req_rn_response, &req_rn_response_size, DIGITAL_RX, 0, COMMUNICATION_TIMEOUT);
                if (comm_error)
                    COMMUNICATION_STATE = error;
                else
                    COMMUNICATION_STATE = send_command;
                break;
            
            case send_command:
                // Initiate communication
                nak_init(&nak);
                nak_build(&nak);
                fm0_encoder(nak.result_data, nak.size, TARI, DIGITAL_TX, 0);
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
