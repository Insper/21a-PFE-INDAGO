/************************************************************************/
/* prototypes                                                           */
/************************************************************************/
#ifndef FM0_ENCODER_H
#define FM0_ENCODER_H

static void fm0_encode0(int tari, unsigned short pin_tx, unsigned char port_tx);
static void fm0_encode1(int tari, unsigned short pin_tx, unsigned char port_tx);
void fm0_encoder(int package, int size, int tari, unsigned short pin_tx, unsigned char port_tx);

#endif /* FM0_ENCODER_H */
