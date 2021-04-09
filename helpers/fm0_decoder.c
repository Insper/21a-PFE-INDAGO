#include "fm0_decoder.h"


#include <ti/drivers/UART.h>

/************************************************************************/
/* functions                                                            */
/************************************************************************/
/*!
 *  @brief Receive FM0 data from PIN_RX and translate and store data to package 
 *
 *  @param      pin_rx  pin RX
 *  @param      tari    tari time
 *  @param      package package pointer
 */
void fm0_decoder(int pin_rx , int tari ,int *package , UART_Handle uart) {
    unsigned int package_pointer = 0;    // pointer of current data
    unsigned int actual = 0;        // current data signal
    unsigned int last = 0;          // last data signal


    while(1){
        last = GPIO_read(pin_rx);
        usleep(tari/2); // microseconds
        actual = GPIO_read(pin_rx);
        if(actual == last){
            usleep(tari/2); // microseconds
            
            if(GPIO_read(pin_rx) == last){
                break;
            }
            UART_write(uart, "1", sizeof("1"));

            package[package_pointer] = 1;  
        }
        else{
            usleep(tari/2); // microseconds
            package[package_pointer] = 0;

            UART_write(uart, "0", sizeof("0"));
        }
        package_pointer ++;
    }

    UART_write(uart, "\r\n", sizeof("\r\n"));

}
