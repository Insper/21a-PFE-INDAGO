/************************************************************************/
/* prototypes                                                           */
/************************************************************************/
#ifndef FM0_ENCODER_H
#define FM0_ENCODER_H

static void fm0_encode0(int pin_tx, int tari);
static void fm0_encode1(int pin_tx, int tari);
void encode_FM0(int package, int size, int pin_tx, int tari);

#endif /* FM0_ENCODER_H */