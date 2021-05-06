#include "write.h"

void write_init(write *write, unsigned char mem_bank, unsigned char word_ptr,
                unsigned short data, unsigned short rn, unsigned short crc)
{
    write->command = WRITE_COMMAND;
    write->size = WRITE_SIZE;

    write->mem_bank = mem_bank;
    write->word_ptr = word_ptr;
    write->data = data;
    write->rn = rn;
    write->crc = crc;

}

void write_build(write *write)
{
    write->result_data = 0;

    write->result_data |= (write->command << 49);
    write->result_data |= (write->mem_bank << 47);
    write->result_data |= (write->word_ptr << 39);
    write->result_data |= (write->data << 32);
    write->result_data |= (write->rn << 16);
    write->result_data |= write->crc;
}
