#ifndef READ_H
#define READ_H

typedef struct {
	unsigned char command;
	unsigned char mem_bank;
	unsigned char word_ptr; // EBV
	unsigned char word_count;
	unsigned short rn;
	unsigned short crc;
} read;
long read_command(read *read);

#endif /* READ_H */