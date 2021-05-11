/************************************************************************/
/* prototypes                                                           */
/************************************************************************/
#ifndef FM0_DECODER_H
#define FM0_DECODER_H

static int change_state(int state, unsigned short pin_rx);
int fm0_decoder(int tari, int *payload, unsigned short pin_rx, unsigned char port_rx, char *flag);

// void fm0_decoder(int tari, int *package, unsigned short pin_rx,
//                  unsigned char port_rx);

#endif /* FM0_DECODER_H */
