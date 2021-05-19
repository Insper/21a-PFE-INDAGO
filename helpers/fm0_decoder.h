/************************************************************************/
/* prototypes                                                           */
/************************************************************************/
#ifndef FM0_DECODER_H
#define FM0_DECODER_H

extern volatile char READING;
extern volatile unsigned int dt;
extern volatile unsigned int reading_timer;
extern volatile unsigned int resultante_tempo;

int fm0_decoder(int tari, unsigned int *payload, unsigned int *n, unsigned short pin_rx,
                unsigned char port_rx);

#endif /* FM0_DECODER_H */
