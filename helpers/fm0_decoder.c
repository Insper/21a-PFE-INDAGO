#include "fm0_decoder.h"

enum
{
    start, read, um, read_zero, zero, erro, fim
} state;

// /************************************************************************/
// /* functions                                                            */
// /************************************************************************/
// /*!
//  *  @brief Receive FM0 data from decoder_driver and translate and store data to package
//  *
//  *  @param      payload package pointer
//  *  @param      n       package size
//  *  @param      driver  RX driver
//  */
int fm0_decoder(unsigned long long *payload, unsigned int *n,
                decoder_driver driver)
{

    int c_bit = 0;

    int edge = 0; // 0: high to low
                  // 1: low  to high

    int from_one = 0;

    edge = _GPIO_read(driver.pin_rx, driver.port_rx);
    edge = _change_edge(!edge, driver.pin_rx, driver.port_rx);

    int state = start;

    READING = 0;
    delta_time = 0;
    dt = 0;
    while (1)
    {
        switch (state)
        {
        case start:
            if (READING)
            {
                READING = 0;
                edge = _change_edge(edge, driver.pin_rx, driver.port_rx);
                state = read;
            }
            else if (dt > driver.timeout)
            {
                state = erro;
            }
            break;
        case read:
            if (READING)
            {
                READING = 0;
                edge = _change_edge(edge, driver.pin_rx, driver.port_rx);
                if ((reading_timer * 100 > (0.65 * driver.tari))
                        && (reading_timer * 100 < (1.35 * driver.tari)))
                {
                    state = um;
                }
                else if (reading_timer * 100 > 0.35 * driver.tari
                        && reading_timer * 100 < 0.65 * driver.tari)
                {
                    state = read_zero;
                }
                else
                {
                    state = erro;
                }
                break;
            }

            // fim da transmissao ou erro?
            if (dt * 100 > 6 * driver.tari)
            {
                if (from_one == 1)
                {
                    state = fim;
                }
                else
                {
                    state = erro;
                }
            }

            break;
        case read_zero:
            if (READING)
            {
                READING = 0;
                edge = _change_edge(edge, driver.pin_rx, driver.port_rx);
                delta_time = reading_timer - dt;
                if (reading_timer * 100 > 0.35 * driver.tari
                        && reading_timer * 100 < 0.65 * driver.tari)
                {
                    state = zero;
                }
                else
                {
                    state = erro;
                }
            }
            break;
        case um:
            *payload = (*payload << 1) | 0x01;
            c_bit++;
            state = read;
            from_one = 1;
            break;
        case zero:
            *payload = (*payload << 1);
            c_bit++;
            state = read;
            from_one = 0;
            break;
        case fim:
            *payload = (*payload >> 1);
            *n = c_bit - 1;
            return (0);
        case erro:
            *payload = 0;
            return (1);
        default:
            state = erro;
            break;
        }
    }
}
