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
void fm0_decoder(int pin_rx , int tari ,int *package) {
    unsigned int actual = 0;        // current data signal
    unsigned int last = 0;          // last data signal

    char condition_inter = 1;
    while(1){
        last = GPIO_read(pin_rx);
        usleep(tari/2); // microseconds
        actual = GPIO_read(pin_rx);
        usleep(tari/2); // microseconds
        *package<<1;
        if(actual == last){            
            if(GPIO_read(pin_rx) == last){
            	break;
            }
            *package |= 1;
        }
    }
}
