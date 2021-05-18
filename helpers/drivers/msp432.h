
#define MSP432
#ifdef MSP432
#ifndef MSP432_H
#define MSP432_H

extern volatile unsigned int dt;

void _GPIO_toggle(unsigned short pin, unsigned char port);
void _usleep(unsigned int time);
unsigned int _GPIO_read(unsigned short pin, unsigned char port);

#endif /* MSP432_H */
#endif /* MSP432 */
