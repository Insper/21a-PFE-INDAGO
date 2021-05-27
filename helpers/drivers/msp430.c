#include "msp430.h"
#include "driverlib.h"

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

unsigned int _GPIO_read(unsigned short pin, unsigned char port)
{
    return GPIO_getInputPinValue(port, pin);
}

unsigned int _change_edge(int edge, unsigned short pin_rx, unsigned char port)
{
    GPIO_selectInterruptEdge(port, pin_rx, !edge);
    return !edge;
}
