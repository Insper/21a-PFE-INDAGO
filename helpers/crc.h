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

typedef unsigned short  crc16;
void crc_16_ccitt_init(unsigned short polynomial);
crc16 crc_16_ccitt(const unsigned char message[], int n_bytes, crc16	 remainder);
unsigned char crc5(const unsigned char message, unsigned char  remainder, unsigned char  polynomial);

#endif /* CRC_H */
