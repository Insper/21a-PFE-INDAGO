#include "kill.h"

void kill_init(kill *kill, unsigned short password, unsigned char rfu,
               unsigned short rn, unsigned short crc)
{
    kill->command = KILL_COMMAND;
    kill->size = KILL_SIZE;

    kill->password = password;
    kill->rfu = rfu;
    kill->rn = rn;
    kill->crc = crc;
}

void kill_build(kill *kill)
{
    kill->result_data = 0;

    kill->result_data |= (kill->command << 51);
    kill->result_data |= (kill->password << 35);
    kill->result_data |= (kill->rfu << 32);
    kill->result_data |= (kill->rn << 16);
    kill->result_data |= kill->crc;
}
