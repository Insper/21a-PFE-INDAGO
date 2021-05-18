#include "msp430.h"

void _GPIO_toggle(unsigned short pin, unsigned char port)
{
    GPIO_toggleOutputOnPin(port, pin);
}

void _usleep(unsigned int time)
{
    if (time >= 1000)
    {
        __delay_cycles(7979);
    }
    else
    {
        __delay_cycles(3837);
    }
}

inline void _usleep_tari(void)
{
    // TODO: Criar nossa propria funcao
    asm(" NOP");
    asm(" NOP");
    asm(" NOP");
    asm(" NOP");
    asm(" NOP");
}

unsigned int _GPIO_read(unsigned short pin, unsigned char port)
{
    return GPIO_getInputPinValue(port, pin);
}

unsigned int _change_edge(int edge, unsigned short pin_rx)
{
    GPIO_write(HAMBURGER_PIN, edge);
    if (edge)
        //GPIO_setConfig(pin_rx, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);
    else
        //GPIO_setConfig(pin_rx, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_RISING);

    return !edge;
}
