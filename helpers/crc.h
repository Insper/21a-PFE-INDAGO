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

typedef uint16_t  crc16;
void crc_16_ccitt_init(uint16_t polynomial);
crc16 crc_16_ccitt(unsigned char const message[], int nBytes, crc16	 remainder);
uint8_t crc5(uint8_t const message, uint8_t  remainder, uint8_t  polynomial);

#endif /* CRC_H */