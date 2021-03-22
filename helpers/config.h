/************************************************************************/
/* defines                                                              */
/************************************************************************/
#define TARI 8 // Tari value specified by protocol documentation - Time in microseconds

#define POLYNOMIAL 0x1D0F
typedef uint16_t crc;

#define WIDTH  (8 * sizeof(crc))
#define TOPBIT (1 << (WIDTH - 1))