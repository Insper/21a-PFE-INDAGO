#include "req_rn.h"

void req_rn_init(req_rn *req_rn, unsigned short rn)
{
    req_rn->command = REQ_RN_COMMAND;
    req_rn->size = REQ_RN_SIZE;

    req_rn->rn = rn;
}

void req_rn_build(req_rn *req_rn)
{
    req_rn->result_data = 0;

    req_rn->result_data |= (req_rn->command << 24);
    req_rn->result_data |= (req_rn->rn);
    req_rn->crc = crc_16_ccitt(req_rn->result_data, 3);
    req_rn->result_data <<= 16;
    req_rn->result_data |= req_rn->crc;
}
