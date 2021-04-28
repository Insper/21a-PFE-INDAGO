#include "msp430.h"

void _GPIO_toggle(unsigned short pin, unsigned char port) {
  GPIO_toggleOutputOnPin(port, pin);
}

void _usleep(unsigned int time) {
  // TODO: Criar nossa propria funcao
}

unsigned int _GPIO_read(unsigned short pin, unsigned char port) {
  return GPIO_getInputPinValue(port, pin);
}