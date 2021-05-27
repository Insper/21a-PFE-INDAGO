#ifndef SELECT_H
#define SELECT_H

#define SELECT_COMMAND 0b1010
#define SELECT_SIZE 44

typedef struct
{
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
} select_cmd;

void select_init(select_cmd *select, unsigned char target, unsigned char action,
                 unsigned char mem_bank, unsigned char pointer,
                 unsigned char length, unsigned char mask,
                 unsigned char truncate, unsigned short crc);
void select_build(select_cmd *select);

#endif /* SELECT_H */
