/**********************************************************************
 *
 * Filename:    crc.h
 * 
 * Description: A header file describing the various CRC standards.
 *
 * Notes:       
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
#ifndef CRC_H
#define CRC_H


// CRC-16 parameters
#define POLYNOMIAL_16        0x1021
#define INITIAL_REMAINDER_16 0xFFFF

// CRC-5 parameters
#define POLYNOMIAL_5        0x29
#define INITIAL_REMAINDER_5 0x9

typedef unsigned short  crc16;
void crc_16_ccitt_init(void);
crc16 crc_16_ccitt(const unsigned long message, int n_bytes);
unsigned char crc5(unsigned char const message);
#endif /* CRC_H */
