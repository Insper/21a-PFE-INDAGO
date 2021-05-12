/************************************************************************/
/* prototypes                                                           */
/************************************************************************/
#ifndef FM0_DECODER_H
#define FM0_DECODER_H

#include <ti/drivers/UART.h>


extern volatile char READING;

extern UART_Handle uart;


static int change_state(int state, unsigned short pin_rx);
int fm0_decoder(int tari, unsigned int *payload, unsigned short pin_rx, unsigned char port_rx);

// void fm0_decoder(int tari, int *package, unsigned short pin_rx,
//                  unsigned char port_rx);

#endif /* FM0_DECODER_H */
