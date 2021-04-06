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

/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>


/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>
// #include <ti/drivers/I2C.h>
// #include <ti/drivers/SPI.h>
#include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>

/* Driver configuration */
#include "ti_drivers_config.h"


/* IGNORAR ISSO */
#include "main.h"

char STATE = 0;

void timerCallback(Timer_Handle myHandle, int_fast16_t status);

void gpioButtonFxn1(uint_least8_t index)
{
    int tari = 20000;
    int res;
    //fm0_decoder(&res, DIGITAL_RX, tari);
    int i =0;
    int pos = 0;
    for (i= 0; i < 32; i++){

        //GPIO_write(CONFIG_GPIO_LED_0,res[i]);
        usleep(500000);

    }
}


void timerCallback(Timer_Handle myHandle, int_fast16_t status) {
    STATE = 0;
}
/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    /* 1 second delay */
    uint32_t time = 2;

    const char  echoPrompt[] = "Echoing characters:\r\n";

    UART_Handle uart;
    UART_Params uartParams;

    /* Call driver init functions */
    GPIO_init();
    UART_init();
    Timer_init();


    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(DIGITAL_TX, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(DIGITAL_RX, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);

    GPIO_setCallback(DIGITAL_RX, gpioButtonFxn1);

    /* Create a UART with data processing off. */
   UART_Params_init(&uartParams);
   uartParams.writeDataMode = UART_DATA_BINARY;
   uartParams.readDataMode = UART_DATA_BINARY;
   uartParams.readReturnMode = UART_RETURN_FULL;
   uartParams.baudRate = 115200;

   uart = UART_open(CONFIG_UART_0, &uartParams);
   if (uart == NULL) {
           /* UART_open() failed */
           while (1);
   }
   UART_write(uart, echoPrompt, sizeof(echoPrompt));


   /* Enable interrupts */
   GPIO_enableInt(DIGITAL_RX);

   /* Turn on user LED */
   GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);

   Timer_Handle timer0;
   Timer_Params params;

   Timer_Params_init(&params);
   params.period = 100000;
   params.periodUnits = Timer_PERIOD_US; // microseconds
   params.timerMode = Timer_ONESHOT_CALLBACK;
   params.timerCallback = timerCallback;
   timer0 = Timer_open(CONFIG_TIMER_0, &params);




   query query;


    while (1) {

        switch (STATE)
        {
        case 0:
            UART_write(uart, "Enviando\r\n", sizeof("Enviando\r\n"));
            query_init(&query, 0, 0, 0, 1, 0, 0, 0);
            query_build(&query);
            fm0_encoder(query.result_data, query.size, DIGITAL_TX, TARI);
            if (Timer_start(timer0) == Timer_STATUS_ERROR) {
                    /* Failed to start timer */
                    while (1) {}
                }

            STATE = 1;
            break;

        case 1:
            UART_write(uart, echoPrompt, sizeof(echoPrompt));
            break;

        }


    	//query query;
        //query_init(&query, 0, 0, 0, 1, 0, 0, 0);
    	//query_build(&query);
    	//fm0_encoder(query.result_data, query.size, DIGITAL_TX, TARI);
        //fm0_encoder(10, 8, DIGITAL_TX, TARI);


        //sleep(time);
        //GPIO_toggle(CONFIG_GPIO_LED_0);
    	// Inicia comunicao
				// Envia query
				// recebe rn16
				// envia ack(rn16)
    			// recebe { pc | xpc, epc }
    			// envia req_rn(rn16)
    			// recebe handle
    			// envia command(handle)
        // sleep(time);
        // GPIO_toggle(CONFIG_GPIO_LED_0);
        // UART_write(uart, echoPrompt, sizeof(echoPrompt));
    }
}
