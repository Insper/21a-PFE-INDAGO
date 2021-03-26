#ifndef SELECT_H
#define SELECT_H

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
} select;
int select_command(select *select);

#endif /* SELECT_H */