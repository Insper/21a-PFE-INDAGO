#ifndef REQ_RN_H
#define REQ_RN_H
#include "../crc.h"

#define REQ_RN_COMMAND 0b11000001
#define REQ_RN_SIZE 40

extern volatile rn16 HANDLE;

typedef struct
{
    unsigned char command;
    unsigned short rn;
    unsigned short crc;
    unsigned int size;
    unsigned long result_data;
} req_rn;

void req_rn_init(req_rn *req_rn, unsigned short rn);
void req_rn_build(req_rn *req_rn);
int req_rn_process(unsigned long *command, unsigned int command_size, int STATE, unsigned short pin_tx,
                  unsigned char port_tx);

#endif /* REQ_RN_H */
