#include "fm0_decoder.h"

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
static void fm0_decoder(int pin_rx, int tari,int *package ) {
    int package_pointer = 0;    // pointer of current data
    uint32_t actual = 0;        // current data signal 
    uint32_t last = 0;          // last data signal


    while(1){
        last = GPIO_read(pin_rx);
        usleep(tari/2); // microseconds
        actual = GPIO_read(pin_rx);
        if(actual == last){
            usleep(tari/2); // microseconds
            
            if(GPIO_read(pin_rx) == last){
                break;
            }
            package[package_pointer] = 1;  
        }
        else{
            usleep(tari/2); // microseconds
            package[package_pointer] = 0;
        }
        package_pointer ++;
    }

}
