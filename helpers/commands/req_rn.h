#ifndef REQ_RN_H
#define REQ_RN_H
#include "../crc.h"

#define REQ_RN_COMMAND 0b11000001
#define REQ_RN_SIZE 40

typedef struct
{
    unsigned char command;
    unsigned short rn;
    unsigned short crc;
    unsigned int size;
    unsigned long long result_data;
} req_rn;

void req_rn_init(req_rn *req_rn, unsigned short rn);
void req_rn_build(req_rn *req_rn);
int req_rn_validate(unsigned long long *command, unsigned int command_size);

#endif /* REQ_RN_H */
