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
