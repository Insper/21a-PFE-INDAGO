#include "select.h"

void select_init(select_cmd *select, unsigned char target, unsigned char action,
                 unsigned char mem_bank, unsigned char pointer,
                 unsigned char length, unsigned char mask,
                 unsigned char truncate, unsigned short crc)
{
    select->command = SELECT_COMMAND;
    select->size = SELECT_SIZE;

    select->target = target;
    select->action = action;
    select->mem_bank = mem_bank;
    select->pointer = pointer;
    select->length = length;
    select->mask = mask;
    select->truncate = truncate;
    select->crc = crc;
}

void select_build(select_cmd *select)
{
    select->result_data = 0;

    select->result_data |= (select->command << 40);
    select->result_data |= (select->target << 37);
    select->result_data |= (select->action << 34);
    select->result_data |= (select->mem_bank << 32);
    select->result_data |= (select->pointer << 24);
    select->result_data |= (select->length << 16);
    select->result_data |= (select->mask << 2);
    select->result_data |= (select->truncate << 2);
    select->result_data |= select->crc;
}
