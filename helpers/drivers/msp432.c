#include "msp432.h"

void _GPIO_toggle(unsigned short pin, unsigned char port)
{
    GPIO_toggle(pin);
}

void _usleep(unsigned int time)
{
    dt = 0;
    while(dt*100<time){}

}

unsigned int _GPIO_read(unsigned short pin, unsigned char port)
{
    return GPIO_read(pin);
}
