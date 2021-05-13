#include "fm0_decoder.h"

#define dec

#ifdef dec
#include <ti/drivers/GPIO.h>
#include "ti_drivers_config.h"
#endif

enum { start, read, um, read_zero, zero, erro, fim } satte;

// __pin_handler()
// {
//     flag = 1;
// }

static int change_edge(int edge, unsigned short pin_rx)
{
#ifdef dec
    if (edge)
        GPIO_setConfig(pin_rx, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);
    else
        GPIO_setConfig(pin_rx, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_RISING);

    return !edge;
#else
    return 0;
#endif
}

// void fm0_decoder(int tari, int *package, unsigned short pin_rx,
//                  unsigned char port_rx)
int fm0_decoder(int tari, unsigned int *payload, unsigned short pin_rx, unsigned char port_rx)
{
#ifdef dec
    int c_bit = 0;

    int edge = 0;  // 0: high to low
                   // 1: low  to high
    //unsigned int dt;
    int veioDoUm = 0;

    edge = _GPIO_read(pin_rx, port_rx);
    char c[32];

    //  pin_irq_edge(edge);
//    edge = change_edge(edge, pin_rx);

    int state = start;
    c[0] = 's';
    ////UART_write(uart, c, 1);

    //unsigned int tinit;
    //unsigned int tatual;

    while (1)
    {
        switch (state)
        {
        case start:

            //GPIO_write(HAMBURGER_PIN, READING);
            if (READING)
            {
                dt=0;
                //GPIO_write(HAMBURGER_PIN, READING);
                READING = 0;
                edge = change_edge(edge, pin_rx);
//                tinit = Timer_getCount(timer0);
         //       tinit = read_time();
                state = read;
            }
            break;
        case read:
            // bit ?
            c[0] = 'r';
            ////UART_write(uart, c, 1);
            //tatual = Timer_getCount(timer0);
            //dt = tatual - tinit;
            if (READING)
            {
                READING = 0;
                dt=dt*10;
                edge = change_edge(edge, pin_rx);
                if (dt > 0.65 * tari  && dt < 1.35 * tari)
                {
                    state = um;
                }
                else if (dt > 0.35 * tari && dt < 0.65 * tari)
                {
                    state = read_zero;
                    // edge = change_edge(edge, pin_rx);
                }
                else
                {
                    state = erro;
                }
                dt = 0;
                //tinit = tatual;
                break;
                //GPIO_write(HAMBURGER_PIN, READING);
            }

            // fim da transmissao

            if (dt > 5 * tari)
            {
                if (veioDoUm == 1)
                    state = fim;
                else
                    state = erro;
            }
            //GPIO_write(HAMBURGER_PIN, 1);

            //usleep(500);
            //GPIO_write(HAMBURGER_PIN, 0);

            break;
        case read_zero:
            c[0] = 'z';
            //UART_write(uart, c, 1);
            //tatual = Timer_getCount(timer0);
            //dt = tatual - tinit;
            dt=dt*10;
            if (READING)
            {
                READING = 0;
                edge = change_edge(edge, pin_rx);
                if (dt > 0.35 * tari && dt < 0.65 * tari)
                {
                    state = zero;
                    // edge = change_edge(edge, pin_rx);
                }
                else
                {
                    state = erro;
                }
                dt=0;

            }
            break;
        case um:
            c[0] = '1';
           //UART_write(uart, c, 1);
            *payload = (*payload << 1) | 0x01;
            c_bit++;
            state = read;
            veioDoUm = 1;
            break;
        case zero:
            c[0] = '0';
            //UART_write(uart, c, 1);
            *payload = (*payload << 1);
            c_bit++;
            state = read;
            veioDoUm = 0;
            break;
        case fim:
            c[0] = 'f';
           //UART_write(uart, c, 1);
            *payload = (*payload >> 1);
            return (c_bit - 1);
        case erro:
            c[0] = 'e';
            //UART_write(uart, c, 1);
            *payload = 0;
            return (dt);//(0);
        default:
            state = erro;
            break;
        }
    }
#else
    return(0);
#endif
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
