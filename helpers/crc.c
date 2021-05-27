/**********************************************************************
 *
 * Filename:    crc.c
 * 
 * Description: Slow and fast implementations of the CRC standards.
 *
 * Notes:       The parameters for each supported CRC standard are
 *				defined in the header file crc.h.  The implementations
 *				here should stand up to further additions to that list.
 *
 * Website: https://barrgroup.com/downloads/code-crc-c 
 *  
 * Copyright (c) 2000 by Michael Barr.  This software is placed into
 * the public domain and may be used for any purpose.  However, this
 * notice must not be changed or removed and no warranty is either
 * expressed or implied by its publication or distribution.
 * 
 * The functions were modified to fit the project specifications
 **********************************************************************/
#include "crc.h"

crc16 crc_table[256];

/*********************************************************************
 *
 * Function:    crc_16_ccitt_init()
 * 
 * Description: Populate the partial CRC lookup table.
 *
 * Notes:		This function must be rerun any time the CRC standard
 *				is changed.  If desired, it can be run "offline" and
 *				the table results stored in an embedded system's ROM.
 *
 * Returns:		None defined.
 *
 *********************************************************************/
void crc_16_ccitt_init(void)
{
    unsigned short polynomial = POLYNOMIAL_16;
    crc16 remainder;
    int dividend;
    unsigned char bit;

    // Compute the remainder of each possible dividend.
    for (dividend = 0; dividend < 256; ++dividend)
    {
        // Start with the dividend followed by zeros.
        remainder = dividend << 8;

        // Perform modulo-2 division, a bit at a time.
        for (bit = 8; bit > 0; --bit)
        {
            //	Try to divide the current data bit.
            if (remainder & 0x8000)
            {
                remainder = (remainder << 1) ^ polynomial;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }

        // Store the result into the table.
        crc_table[dividend] = remainder;
    }
}

/*********************************************************************
 *
 * Function:    crc_16_ccitt()
 * 
 * Description: Compute the CRC of a given message.
 *
 * Notes:		crc_16_ccitt_init() must be called first.
 *
 * Returns:		The CRC of the message.
 *
 *********************************************************************/
crc16 crc_16_ccitt(const unsigned long message, int n_bytes)
{
    crc16 remainder = INITIAL_REMAINDER_16;
    unsigned char data;
    int byte;
    unsigned char tmp;

    // Divide the message by the polynomial, a byte at a time.
    for (byte = 0; byte < n_bytes; ++byte)
    {
        tmp = (message >> (byte * 8)) & 0b11111111;
        data = tmp ^ (remainder >> 8);
        remainder = crc_table[data] ^ (remainder << 8);
    }

    // The final remainder is the CRC.
    return remainder;
}

unsigned char crc5(unsigned char const message)
{
    unsigned char remainder = INITIAL_REMAINDER_5;
    unsigned char polynomial = POLYNOMIAL_5;
    unsigned char bit;

    // For each bit position in the message....
    for (bit = 8; bit > 0; --bit)
    {
        // If the uppermost bit is a 1...
        if (remainder & 0x80)
        {
            // XOR the previous remainder with the divisor.
            remainder ^= polynomial;
        }

        // Shift the next bit of the message into the remainder.
        remainder = (remainder << 1);
    }

    // Return only the relevant bits of the remainder as CRC.
    return (remainder >> 3);
}
