/************************************************************************/
/* prototypes                                                           */
/************************************************************************/
#ifndef FM0_DECODER_H
#define FM0_DECODER_H


#include <ti/drivers/UART.h>

void fm0_decoder(int pin_rx, int tari,int *package , UART_Handle uart);

#endif /* FM0_DECODER_H */

