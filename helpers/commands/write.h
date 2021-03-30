#ifndef WRITE_H
#define WRITE_H

typedef struct {
	unsigned char command;
	unsigned char mem_bank;
	unsigned char word_ptr; // EBV
	unsigned short data;
	unsigned short rn;
	unsigned short crc;
} write;
long write_command(write *write);

#endif /* WRITE_H */