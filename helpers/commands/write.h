#ifndef WRITE_H
#define WRITE_H

#define WRITE_COMMAND 0b11000011
#define WRITE_SIZE 58

typedef struct
{
    unsigned char command;
    unsigned char mem_bank;
    unsigned char word_ptr; // EBV
    unsigned short data;
    unsigned short rn;
    unsigned short crc;
    unsigned int size;
    unsigned long result_data;
} write;

void write_init(write *write, unsigned char mem_bank, unsigned char word_ptr,
                unsigned short data, unsigned short rn, unsigned short crc);
void write_build(write *write);

#endif /* WRITE_H */
