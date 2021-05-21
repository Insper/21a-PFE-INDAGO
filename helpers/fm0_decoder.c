#include "fm0_decoder.h"

enum
{
    start,
    read,
    um,
    read_zero,
    zero,
    erro,
    fim
} state;

int fm0_decoder(int tari, unsigned int *payload, unsigned int *n, unsigned short pin_rx,
                unsigned char port_rx, unsigned int timeout)
{

    int c_bit = 0;

    int edge = 0; // 0: high to low
                  // 1: low  to high

    int veioDoUm = 0;

    edge = _GPIO_read(pin_rx, port_rx);
    edge = _change_edge(!edge, pin_rx, port_rx);

    int state = start;

    READING = 0;
    resultante_tempo = 0;
    dt=0;
    while (1)
    {
        switch (state)
        {
        case start:
            if (READING)
            {
                READING = 0;
                edge = _change_edge(edge, pin_rx, port_rx);
                state = read;
            } else if (dt>timeout) {
                state = erro;
            }
            break;
        case read:
            if (READING)
            {
                READING = 0;
                edge = _change_edge(edge, pin_rx, port_rx);
                if ((reading_timer * 100 > (0.65 * tari)) && (reading_timer * 100 < (1.35 * tari)))
                {
                    state = um;
                }
                else if (reading_timer * 100 > 0.35 * tari && reading_timer * 100 < 0.65 * tari)
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
            if (dt * 100 > 6 * tari)
            {
                if (veioDoUm == 1)
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
                edge = _change_edge(edge, pin_rx, port_rx);
                resultante_tempo = reading_timer - dt;
                if (reading_timer * 100 > 0.35 * tari && reading_timer * 100 < 0.65 * tari)
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
            veioDoUm = 1;
            break;
        case zero:
            *payload = (*payload << 1);
            c_bit++;
            state = read;
            veioDoUm = 0;
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

// /************************************************************************/
// /* functions                                                            */
// /************************************************************************/
// /*!
//  *  @brief Receive FM0 data from PIN_RX and translate and store data to package
//  *
//  *  @param      pin_rx  pin RX
//  *  @param      tari    tari time
//  *  @param      package package pointer
//  */
// void fm0_decoder(int tari, int *package, unsigned short pin_rx,
//                  unsigned char port_rx)
// {
//     unsigned int actual, last;        // current and last data signal

//     while (1)
//     {
//         last = _GPIO_read(pin_rx, port_rx);
//         _usleep(tari / 2); // microseconds
//         actual = _GPIO_read(pin_rx, port_rx);
//         _usleep(tari / 2); // microseconds
//         *package <<= 1;
//         if (actual == last)
//         {
//             if (_GPIO_read(pin_rx, port_rx) == last)
//             {
//                 break;
//             }
//             *package |= 1;
//         }
//     }
// }
