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

volatile char STATE = 0;
volatile char READING = 0;
UART_Handle uart;

void rx_callback(uint_least8_t index)
{
    READING = 1;
}

void timerCallback(Timer_Handle myHandle, int_fast16_t status)
{
    STATE = 0;
}

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    /* 1 second delay */
    uint32_t time = 1000;

    const char echoPrompt[] = "Echoing characters:\r\n";

    //UART_Handle uart;
    UART_Params uartParams;

    /* Call driver init functions */
    GPIO_init();
    UART_init();
    Timer_init();

    GPIO_setConfig(DIGITAL_TX, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(DIGITAL_RX, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_BOTH_EDGES);

    GPIO_setConfig(HAMBURGER_PIN, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

    GPIO_setCallback(DIGITAL_RX, rx_callback);

    /* Enable interrupts */
    GPIO_enableInt(DIGITAL_RX);

    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.baudRate = 115200;

    uart = UART_open(CONFIG_UART_0, &uartParams);
    if (uart == NULL)
    {
        /* UART_open() failed */
        while (1)
            ;
    }
    UART_write(uart, echoPrompt, sizeof(echoPrompt));

    Timer_Handle timer0;
    Timer_Params params;

    Timer_Params_init(&params);
    params.period = 300000;
    params.periodUnits = Timer_PERIOD_US; // microseconds
    params.timerMode = Timer_ONESHOT_CALLBACK;
    params.timerCallback = timerCallback;
    timer0 = Timer_open(CONFIG_TIMER_0, &params);

    query query;
    unsigned int query_response = 0;
    GPIO_write(HAMBURGER_PIN, 0);
    while (1)
    {
        // GPIO_toggle(HAMBURGER_PIN);
        //int papapa = fm0_decoder(TARI, &query_response, DIGITAL_RX, 0);
        //char papa[10];
        //  sprintf(papa, "DT: %d\r\n", papapa);
        //UART_write(uart, papa, sizeof(papa));
        fm0_encoder(query_response, 1, TARI, DIGITAL_TX, 0);

        // switch (STATE)
        // {
        // case 0:   // Envia Query
        //     UART_write(uart, "Enviando\r\n", sizeof("Enviando\r\n"));
        //     query_init(&query, 0, 0, 0, 1, 0, 0, 0);
        //     query_build(&query);
        //     fm0_encoder(query.result_data, query.size, TARI, DIGITAL_TX, 0);
        //     if (Timer_start(timer0) == Timer_STATUS_ERROR) {
        //             /* Failed to start timer */
        //             while (1) {}
        //         }

        //     STATE = 1;
        //     break;

        // case 1: // Aguarda resposta
        //     if(READING){
        //         GPIO_disableInt(DIGITAL_RX);
        //         fm0_decoder(TARI, &query_response, DIGITAL_RX, 0);
        //         // fm0_decoder(TARI, &query_response, DIGITAL_RX, 0);
        //         READING = 0;
        //         GPIO_enableInt(DIGITAL_RX);
        //     }
        //     break;

        // }
    }
}
