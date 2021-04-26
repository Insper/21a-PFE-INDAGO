#include "req_rn.h"

void req_rn_init(req_rn *req_rn, unsigned short rn, unsigned short crc) {
	req_rn->command = REQ_RN_COMMAND;
	req_rn->size = REQ_RN_SIZE;

	req_rn->rn = rn;
	req_rn->crc = crc;
}

void req_rn_build(req_rn *req_rn) {
	req_rn->result_data = 0;

	req_rn->result_data |= (req_rn->command << 32);
	req_rn->result_data |= (req_rn->rn << 16);
	req_rn->result_data |= req_rn->crc;
}
