#ifndef SELECT_H
#define SELECT_H

const unsigned char SELECT_COMMAND = 0b1010;
const unsigned int SELECT_SIZE = 44;

typedef struct {
	unsigned char command;
	unsigned char target;
	unsigned char action;
	unsigned char mem_bank;

	unsigned char pointer; // EBV

	unsigned char length;
	
	unsigned char mask; // Variable

	unsigned char truncate;
	unsigned short crc;

	unsigned int size;
	unsigned long result_data;
} select;

void select_init(select *select, unsigned char target, unsigned char action, unsigned char mem_bank, unsigned char pointer, unsigned char length, unsigned char mask, unsigned char truncate, unsigned short crc);
void select_build(select *select);

#endif /* SELECT_H */