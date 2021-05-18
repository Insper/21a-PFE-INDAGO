#include "fm0_encoder.h"

/************************************************************************/
/* functions                                                            */
/************************************************************************/
/*!
 *  @brief Send FM0 signal when bit value is low
 * 
 *  @param      pin_tx   pin board int to send the signal
 *  @param      tari     tari value to properly send the signal
 */
static void fm0_encode0(int tari, unsigned short pin_tx, unsigned char port_tx)
{
    _GPIO_toggle(pin_tx, port_tx);
    _usleep(tari / 2); // microseconds
    _GPIO_toggle(pin_tx, port_tx);
    _usleep(tari / 2); // microseconds
}

/*!
 *  @brief Send FM0 signal when bit value is high
 * 
 *  @param      pin_tx   pin board int to send the signal
 *  @param      tari     tari value to properly send the signal
 */
static void fm0_encode1(int tari, unsigned short pin_tx, unsigned char port_tx)
{
    _GPIO_toggle(pin_tx, port_tx);
    _usleep(tari); // microseconds
}

/*!
 *  @brief Process the package to send through FM0 based encoder
 *
 *  @param      package  package pointer
 *  @param      size     package size
 *  @param      pin_tx   pin board int to send the signal
 *  @param      tari     tari value to properly send the signal
 */
void fm0_encoder(int package, int size, int tari, unsigned short pin_tx,
                 unsigned char port_tx)
{
    int i;
    for (i = (size - 1); i >= 0; i--)
    {
        if ((package >> i) & 1)
        {
            fm0_encode1(tari, pin_tx, port_tx);
        }
        else
        {
            fm0_encode0(tari, pin_tx, port_tx);
        }
    }
    fm0_encode1(tari, pin_tx, port_tx);
    _GPIO_toggle(pin_tx, port_tx);
}
