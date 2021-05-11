#include "fm0_decoder.h"
#include <ti/drivers/GPIO.h>

enum { start, read, um, read_zero, zero, erro, fim } state;

// __pin_handler()
// {
//     flag = 1;
// }

static int change_state(int state, unsigned short pin_rx)
{
    if (state)
        GPIO_setConfig(pin_rx, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);
    else
        GPIO_setConfig(pin_rx, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_RISING);

    return !state;
}

// void fm0_decoder(int tari, int *package, unsigned short pin_rx,
//                  unsigned char port_rx)
int fm0_decoder(int tari, int *payload, unsigned short pin_rx, unsigned char port_rx, char *flag)
{
    int c_bit = 0;

    int edge = 0;  // 0: high to low
                   // 1: low  to high
    int dt;
    int veioDoUm = 0;

    edge = _GPIO_read(pin_rx, port_rx);

    //  pin_irq_edge(edge);
    edge = change_state(edge, pin_rx);

    int state = start;

    while (1)
    {
        switch (state)
        {
        case start:
            if (*flag == 1)
            {
                *flag = 0;
                edge = change_state(edge, pin_rx);
                dt = 0;
                state = read;
            }
            break;
        case read:
            // bit ?
            if (*flag == 1)
            {
                *flag = 0;
                edge = change_state(edge, pin_rx);
                if (dt > 0.85 * tari * 10 && dt < 1.15 * tari * 10)
                {
                    state = um;
                }
                else if (dt > 0.35 * tari && dt < 0.65 * tari)
                {
                    state = read_zero;
                    edge = change_state(edge, pin_rx);
                }
                else
                {
                    state = erro;
                }
                dt = 0;
            }

            // fim da transmissao
            if (dt > 5 * tari * 10)
            {
                if (veioDoUm == 1)
                    state = fim;
                else
                    state = erro;
            }

            usleep(10);
            dt++;
            break;
        case read_zero:
            if (*flag == 1)
            {
                *flag = 0;
                edge = change_state(edge, pin_rx);
                if (dt > 0.35 * tari && dt < 0.65 * tari)
                {
                    state = zero;
                    edge = change_state(edge, pin_rx);
                }
                else
                {
                    state = erro;
                }
                dt = 0;
            }
            usleep(10);
            dt++;
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
            return (c_bit - 1);
            break;
        case erro:
            *payload = 0;
            return (0);
            break;
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
