#include "fm0_decoder.h"

/************************************************************************/
/* functions                                                            */
/************************************************************************/
/*!
 *  @brief Send FM0 signal when bit value is low
 */

static int* fm0_decoder(int pin_rx, int tari) {
    int package[32];
    int package_pointer = 0;
    int actual = 0;
    int last = 0;

    while(1){
        last = PIN_getOutputValue(pin_rx);
        usleep(tari/2);
        actual = PIN_getOutputValue(pin_rx);
        if(actual == last){
            usleep(tari/2);
            
            if(PIN_getOutputValue(pin_rx) == last){
                return package;
            }
            package[package_pointer] = 1;  
        }
        else{
            usleep(tari/2);
            package[package_pointer] = 0;
        }
        package_pointer ++;
    }
}
