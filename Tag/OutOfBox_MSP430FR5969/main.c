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
#include "LiveTempMode.h"
#include "FRAMLogMode.h"
#include "driverlib.h"
#include "main_includes.h"

uint8_t RXData = 0;                               // UART Receive byte
int mode = 0;                                     // mode selection variable
int pingHost = 0;                                 // ping request from PC GUI
Calendar calendar;                                // Calendar used for RTC

#if defined(__IAR_SYSTEMS_ICC__)
#pragma location = 0x9000
__no_init uint16_t dataArray[12289];
#endif


int hora_da_leitura = 0;

//-----------------------------------------------------------------------------
int _system_pre_init(void)
{
    // Stop Watchdog timer
    WDT_A_hold(__MSP430_BASEADDRESS_WDT_A__);     // Stop WDT

    /*==================================*/
    /* Choose if segment initialization */
    /* should be done or not. */
    /* Return: 0 to omit initialization */
    /* 1 to run initialization */
    /*==================================*/
    return 1;
}


void send_uart(char* str) {
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN0, GPIO_SECONDARY_MODULE_FUNCTION);
                __delay_cycles(900000);
                //int i;
                while(*str != 0){
                    EUSCI_A_UART_transmitData(EUSCI_A0_BASE, *str++);

                    __delay_cycles(10000);

                }

                GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
                GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);
}
/*
 * main.c
 */
int main(void) {

    // Check if a wakeup from LPMx.5
    if (SYSRSTIV == SYSRSTIV_LPM5WU) {
    	// Button S2 pressed
        if (P1IFG & BIT1)
        {
        	// Clear P1.1 interrupt flag
        	GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN0);

        	// Exit FRAM Log Mode
        	mode = '0';

        	// Light up LED1 to indicate Exit from FRAM mode
        	Init_GPIO();
        	GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN2);
        	__delay_cycles(600000);
        }
        else
        {
        	// Continue FRAM data logging
            mode = FRAM_LOG_MODE;
            Init_GPIO();
        }
    }
    else
    {
    	Init_GPIO();
    	GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);

    	// Toggle LED1 and LED2 to indicate OutOfBox Demo start
    	int i;
    	for (i=0;i<10;i++)
    	{
            GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
            GPIO_toggleOutputOnPin(GPIO_PORT_P4, GPIO_PIN2);
            __delay_cycles(200000);
    	}
    }

    // Board initializations
    Init_GPIO();
    Init_Clock();
    Init_UART();

    unsigned int query_response = 0;
    while(1) {
        //char str[] = "teste ";
        //send_uart(&str);
        //GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

        if (hora_da_leitura) {
            GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
            fm0_decoder(TARI, &query_response, GPIO_PIN2, GPIO_PORT_P4);
            //__delay_cycles(1000000);
            fm0_encoder(query_response, 22, TARI, GPIO_PIN6, GPIO_PORT_P2);
            hora_da_leitura=0;
            GPIO_clearInterrupt(GPIO_PORT_P4, GPIO_PIN2);
            GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN2);
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
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2, GPIO_PIN1, GPIO_SECONDARY_MODULE_FUNCTION);

    // Saet PJ.4 nd PJ.5 as Primary Module Function Input, LFXT.
    GPIO_setAsPeripheralModuleFunctionInputPin(
           GPIO_PORT_PJ,
           GPIO_PIN4 + GPIO_PIN5,
           GPIO_PRIMARY_MODULE_FUNCTION
           );

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PMM_unlockLPM5();


    GPIO_selectInterruptEdge(GPIO_PORT_P4, GPIO_PIN2, GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_selectInterruptEdge(GPIO_PORT_P4, GPIO_PIN2, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_clearInterrupt(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN2);

    // Enable global interrupt
    __enable_interrupt();
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
 * UART Communication Initialization
 */
void Init_UART()
{
    // Configure UART
    EUSCI_A_UART_initParam param = {0};
    param.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_SMCLK;
    param.clockPrescalar = 52;
    param.firstModReg = 1;
    param.secondModReg = 0x49;
    param.parity = EUSCI_A_UART_NO_PARITY;
    param.msborLsbFirst = EUSCI_A_UART_LSB_FIRST;
    param.numberofStopBits = EUSCI_A_UART_ONE_STOP_BIT;
    param.uartMode = EUSCI_A_UART_MODE;
    param.overSampling = EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION;

    if(STATUS_FAIL == EUSCI_A_UART_init(EUSCI_A0_BASE, &param))
        return;

    EUSCI_A_UART_enable(EUSCI_A0_BASE);

    EUSCI_A_UART_clearInterrupt(EUSCI_A0_BASE,
                                EUSCI_A_UART_RECEIVE_INTERRUPT);

    // Enable USCI_A0 RX interrupt
    EUSCI_A_UART_enableInterrupt(EUSCI_A0_BASE,
                                 EUSCI_A_UART_RECEIVE_INTERRUPT); // Enable interrupt

    // Enable global interrupt
    __enable_interrupt();
}

/*
 * Enter Low Power Mode 3.5
 */
void enterLPM35()
{
	// Configure button S2 (P1.1) interrupt
    GPIO_selectInterruptEdge(GPIO_PORT_P1, GPIO_PIN1, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);

    // Request the disabling of the core voltage regulator when device enters
    // LPM3 (or LPM4) so that we can effectively enter LPM3.5 (or LPM4.5).
    PMM_turnOffRegulator();

    //Enter LPM3 mode with interrupts enabled
    __bis_SR_register(LPM4_bits + GIE);
    __no_operation();
}

/*
 * USCI_A0 Interrupt Service Routine that receives PC GUI's commands
 */
#pragma vector = USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
	int i;
    switch (__even_in_range(UCA0IV, USCI_UART_UCTXCPTIFG)) {
        case USCI_NONE: break;
        case USCI_UART_UCRXIFG:
            i = EUSCI_A_UART_receiveData(EUSCI_A0_BASE);
        	if (i == '5')
                pingHost = 1;
            else
                mode = i;
            __bic_SR_register_on_exit(LPM3_bits); // Exit active CPU
            break;
        case USCI_UART_UCTXIFG: break;
        case USCI_UART_UCSTTIFG: break;
        case USCI_UART_UCTXCPTIFG: break;
    }
}


/*
 * PIN interrupt to read content
 */
#pragma vector = PORT4_VECTOR
__interrupt void PIN_RX_ISR(void)
{
    GPIO_disableInterrupt(GPIO_PORT_P4, GPIO_PIN2);
    hora_da_leitura = 1;
    GPIO_clearInterrupt(GPIO_PORT_P4, GPIO_PIN2);

}
