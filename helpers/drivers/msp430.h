#if defined MSP430 && !defined MSP430_H
#define MSP430_H

void _GPIO_toggle(unsigned short pin, unsigned char port);
void _usleep(unsigned int time);
unsigned int _GPIO_read(unsigned short pin, unsigned char port);

#endif /* MSP430 && MSP430_H */