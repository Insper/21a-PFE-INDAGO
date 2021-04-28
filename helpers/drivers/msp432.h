#if defined MSP432 && !defined MSP432_H
#define MSP432_H

void _GPIO_toggle(unsigned short pin, unsigned char port);
void _usleep(unsigned int time);
unsigned int _GPIO_read(unsigned short pin, unsigned char port);

#endif /* MSP432 && MSP432_H */