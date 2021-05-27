#ifndef READ_H
#define READ_H

#define READ_COMMAND 0b11000010
#define READ_SIZE 57

typedef struct
{
    unsigned char command;
    unsigned char mem_bank;
    unsigned char word_ptr; // EBV
    unsigned char word_count;
    unsigned short rn;
    unsigned short crc;
    unsigned int size;
    unsigned long result_data;
} read;

void read_init(read *read, unsigned char mem_bank, unsigned char word_ptr,
               unsigned char word_count, unsigned short rn, unsigned short crc);
void read_build(read *read);

#endif /* READ_H */
