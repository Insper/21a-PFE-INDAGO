/************************************************************************/
/* prototypes                                                           */
/************************************************************************/
#ifndef FM0_DECODER_H
#define FM0_DECODER_H

typedef struct
{
    int tari;
    unsigned char pin_rx;
    unsigned char port_rx;
    unsigned int timeout;
} decoder_driver;

extern volatile char READING;
extern volatile unsigned int dt;
extern volatile unsigned int reading_timer;
extern volatile unsigned int resultante_tempo;

int fm0_decoder(unsigned long long *payload, unsigned int *n, decoder_driver driver);

#endif /* FM0_DECODER_H */
