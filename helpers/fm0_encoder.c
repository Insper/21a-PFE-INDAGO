#include "fm0_encoder.h"

/************************************************************************/
/* functions                                                            */
/************************************************************************/
/*!
 *  @brief Send FM0 signal when bit value is low
 */
static void fm0_encode0(int pin_tx, int tari){
    GPIO_toggle(pin_tx);
    usleep(tari/2); // microseconds
    GPIO_toggle(pin_tx);
    usleep(tari/2); // microseconds
}

/*!
 *  @brief Send FM0 signal when bit value is high
 */
static void fm0_encode1(int pin_tx, int tari){
    GPIO_toggle(pin_tx);
    usleep(tari); // microseconds
}

/*!
 *  @brief Process the package to send through FM0 based encoder
 *
 *  @param      package  package pointer
 *  @param      size    package size
 */
void encode_FM0(int package, int size, int pin_tx, int tari) {
    int i;
    for (i=(size-1); i>=0; i--) {
        if ((package >> i) & 1) {
        fm0_encode1(pin_tx, tari);
		} else {
        fm0_encode0(pin_tx, tari);
        }
    }
    fm0_encode1(pin_tx, tari);
}
