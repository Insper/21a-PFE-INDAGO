/************************************************************************/
/* prototypes                                                           */
/************************************************************************/
void fm0_encode0(void);
void fm0_encode1(void);
void encode_FM0(char *buffer, uint32_t size);


/************************************************************************/
/* functions                                                            */
/************************************************************************/
/*!
 *  @brief Send FM0 signal when bit value is low
 */
void fm0_encode0(void){
    GPIO_toggle(DIGITAL_TX);
    sleep(TARI/2);
    GPIO_toggle(DIGITAL_TX);
    sleep(TARI/2);
}

/*!
 *  @brief Send FM0 signal when bit value is high
 */
void fm0_encode1(void){
    GPIO_toggle(DIGITAL_TX);
    sleep(TARI);
}

/*!
 *  @brief Process a buffer to send through FM0 based encoder
 *
 *  @param      buffer  Buffer pointer
 *  @param      size    Buffer size
 */
void encode_FM0(char *buffer, uint32_t size) {
    // Value that helps to work bits
    char helper = 0x80;
    int value, i, info;

    // Iterate through buffer
    for (info = 0; info < size; info++) {
        // Process byte info
        for (i=7; i>=0; i--) {
            value = buffer[info] & helper;
            value >>= i;
            if (value) {
                fm0_encode1();
            } else {
                fm0_encode0();
            }
            helper>>=1;
        }
        helper = 0x80;
    }
}
