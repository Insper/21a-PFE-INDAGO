/* --COPYRIGHT--,BSD
 * Copyright (c) 2014, Texas Instruments Incorporated
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
 * --/COPYRIGHT--*/
/*******************************************************************************
 *
 * main.c
 *
 * Out of Box Demo for the MSP-EXP430FR5969
 * Main loop, initialization, and interrupt service routines
 *
 * June 2014
 * E. Chen
 *
 ******************************************************************************/
#define MSP430

#include "main.h"
#include "driverlib.h"
#include "main_includes.h"
#include <msp430.h>

volatile char STATE = 0;
volatile char READING = 0;
volatile unsigned int dt = 0;
volatile unsigned int reading_timer = 0;
volatile unsigned int delta_time = 0;

enum
{
    READY, ARBITRATE, REPLY, ACKNOWLEDGED, OPEN, SECURED, KILLED, ERROR,
} COMMUNICATION_STATE;

#if defined(__IAR_SYSTEMS_ICC__)
#pragma location = 0x9000
__no_init uint16_t dataArray[12289];
#endif

//-----------------------------------------------------------------------------
int _system_pre_init(void)
{
    // Stop Watchdog timer
    WDT_A_hold(__MSP430_BASEADDRESS_WDT_A__); // Stop WDT

    /*==================================*/
    /* Choose if segment initialization */
    /* should be done or not. */
    /* Return: 0 to omit initialization */
    /* 1 to run initialization */
    /*==================================*/
    return 1;
}

/*
 * main.c
 */
int main(void)
{

    // Board initializations
    _system_pre_init();
    Init_GPIO();
    Init_Clock();

    // Encoder Driver
    encoder_driver tx_driver;
    tx_driver.port_tx = GPIO_PORT_P2;
    tx_driver.pin_tx = GPIO_PIN6;
    tx_driver.tari = TARI;

    // Decoder Driver
    decoder_driver rx_driver;
    rx_driver.port_rx = GPIO_PORT_P4;
    rx_driver.pin_rx = GPIO_PIN2;
    rx_driver.tari = TARI;
    rx_driver.timeout = COMMUNICATION_TIMEOUT;

    unsigned int n = 0;
    //unsigned short random_number = rn16_generate();
    __delay_cycles(10000000);

    query _query;
    rn16 _rn16;
    rn16 rn16_2;
    rn16 handle;
    ack _ack;
    req_rn _req_rn;

    unsigned long query_response = 0;
    unsigned int ack_response = 0;
    unsigned long long req_rn_response = 0;
    unsigned int command_response = 0;

    unsigned int query_response_size = 0;
    unsigned int ack_response_size = 0;
    unsigned int req_rn_response_size = 0;
    unsigned int command_response_size = 0;
    int res = 0;
    int rr = 0;
    unsigned char ccr;
    unsigned char ccr2;
    int comm_error = 0;

    crc_16_ccitt_init();
    COMMUNICATION_STATE = READY;
    while (1)
    {

        switch (COMMUNICATION_STATE)
        {

        case READY:
            comm_error = fm0_decoder(&query_response, &query_response_size,
                                     rx_driver);
            if (comm_error)
            {
                COMMUNICATION_STATE = ERROR;
            }

            res = query_validate(&query_response, query_response_size);
            if (res)
            {
                _rn16.value = rn16_generate();
                _rn16.size = 16;
                fm0_encoder(_rn16.value, _rn16.size, tx_driver);
                COMMUNICATION_STATE = REPLY;
            }
            else
            {
                COMMUNICATION_STATE = ERROR;
            }

            break;

        case ARBITRATE:
            COMMUNICATION_STATE = READY;
            break;

        case REPLY:
            comm_error = fm0_decoder(&ack_response, &ack_response_size,
                                     rx_driver);
            if (comm_error)
                COMMUNICATION_STATE = ERROR;
            else
            {
                res = ack_validate(&ack_response, ack_response_size);
                if (res)
                {
                    COMMUNICATION_STATE = ACKNOWLEDGED;
                    rn16_2.value = rn16_generate();
                    rn16_2.size = 16;
                    fm0_encoder(rn16_2.value, rn16_2.size, tx_driver);
                }
                else
                {
                    COMMUNICATION_STATE = ERROR;
                }
            }
            break;
        case ACKNOWLEDGED:
            comm_error = fm0_decoder(&req_rn_response, &req_rn_response_size,
                                     rx_driver);
            if (comm_error)
                COMMUNICATION_STATE = ERROR;
            else
            {
                res = req_rn_validate(&req_rn_response, req_rn_response_size);
                if (res)
                {
                    COMMUNICATION_STATE = OPEN;
                    handle.value = rn16_generate();
                    handle.size = 16;
                    fm0_encoder(handle.value, handle.size, tx_driver);
                }
                else
                {
                    COMMUNICATION_STATE = ERROR;
                }
            }
            break;
        case OPEN:
            comm_error = fm0_decoder(&command_response, &command_response_size,
                                     rx_driver);
            if (comm_error)
                COMMUNICATION_STATE = ERROR;
            else
            {
                res = nak_validate(&command_response, command_response_size);
                if (res)
                {
                    COMMUNICATION_STATE = ARBITRATE;

                }
                else
                {
                    COMMUNICATION_STATE = ERROR;
                }

            }

            break;
        case ERROR:
            COMMUNICATION_STATE = READY;
            break;
        }
    }
}

/*
 * GPIO Initialization
 */
void Init_GPIO()
{
    // Set all GPIO pins to output low for low power
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    //GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN6);

    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsInputPin(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN6);

    // Configure P2.0 - UCA0TXD and P2.1 - UCA0RXD
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2, GPIO_PIN1,
    GPIO_SECONDARY_MODULE_FUNCTION);

    // Saet PJ.4 nd PJ.5 as Primary Module Function Input, LFXT.
    GPIO_setAsPeripheralModuleFunctionInputPin(
    GPIO_PORT_PJ,
                                               GPIO_PIN4 + GPIO_PIN5,
                                               GPIO_PRIMARY_MODULE_FUNCTION);

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PMM_unlockLPM5();

    GPIO_selectInterruptEdge(GPIO_PORT_P4, GPIO_PIN2,
    GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_clearInterrupt(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN2);

    // initialize Timer0_A
    TA0CCR0 = 0;
    TA0CCTL0 |= CCIE;
    TA0CTL = TASSEL_2 + ID_0 + MC_1;

    __enable_interrupt();
    TA0CCR0 = 795; // Magia , FAVOR N�O ALTERAR
}

/*
 * Clock System Initialization
 */
void Init_Clock()
{
    // Set DCO frequency to 8 MHz
    CS_setDCOFreq(CS_DCORSEL_0, CS_DCOFSEL_6);
    //Set external clock frequency to 32.768 KHz
    CS_setExternalClockSource(32768, 0);
    //Set ACLK=LFXT
    CS_initClockSignal(CS_ACLK, CS_LFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);
    // Set SMCLK = DCO with frequency divider of 1
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    // Set MCLK = DCO with frequency divider of 1
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    //Start XT1 with no time out
    CS_turnOnLFXT(CS_LFXT_DRIVE_0);
}

/*
 * PIN interrupt to read content
 */
#pragma vector = PORT4_VECTOR
__interrupt void PIN_RX_ISR(void)
{
    READING = 1;
    reading_timer = dt;
    dt = 0;
    GPIO_clearInterrupt(GPIO_PORT_P4, GPIO_PIN2);
}

/* 
 * Timer Interrupt 
 */
#pragma vector = TIMER0_A0_VECTOR
__interrupt void myTimerISR(void)
{
    dt = dt + 1;
}
