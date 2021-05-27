/************************************************************************/
/* prototypes                                                           */
/************************************************************************/
#ifndef FM0_ENCODER_H
#define FM0_ENCODER_H

typedef struct
{
    int tari;
    unsigned char pin_tx;
    unsigned char port_tx;
} encoder_driver;

static void fm0_encode0(int tari, unsigned short pin_tx, unsigned char port_tx);
static void fm0_encode1(int tari, unsigned short pin_tx, unsigned char port_tx);
void fm0_encoder(long long package, int size, encoder_driver driver);

#endif /* FM0_ENCODER_H */
