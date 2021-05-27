#include "read.h"

void read_init(read *read, unsigned char mem_bank, unsigned char word_ptr,
               unsigned char word_count, unsigned short rn, unsigned short crc)
{
    read->command = READ_COMMAND;
    read->size = READ_SIZE;

    read->mem_bank = mem_bank;
    read->word_ptr = word_ptr;
    read->word_count = word_count;
    read->rn = rn;
    read->crc = crc;
}

void read_build(read *read)
{
    read->result_data = 0;

    read->result_data |= (read->command << 49);
    read->result_data |= (read->mem_bank << 47);
    read->result_data |= (read->word_ptr << 39);
    read->result_data |= (read->word_count << 32);
    read->result_data |= (read->rn << 16);
    read->result_data |= read->crc;
}
