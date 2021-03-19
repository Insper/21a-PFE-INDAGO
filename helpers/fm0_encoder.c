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
 *  @brief Process a buffer to send through FM0 based encoder
 *
 *  @param      buffer  Buffer pointer
 *  @param      size    Buffer size
 */
void encode_FM0(char *buffer, uint32_t size, int pin_tx, int tari) {
    // Value that helps to work bits
    char helper = 0x80;
    int value, i, info;

    // Iterate through buffer
    for (info = 0; info < size; info++) {
        // Process byte info
        for (i=7; i>=0; i--) {
            value = buffer[info] & helper;
            value >>= i;
            if (value) {
                fm0_encode1(pin_tx, tari);
            } else {
                fm0_encode0(pin_tx, tari);
            }
            helper>>=1;
        }
        helper = 0x80;
    }
    fm0_encode1(pin_tx, tari);
}
