#include "ack.h"

void ack_init(ack *ack, unsigned short rn) {
	ack->command = ACK_COMMAND;
	ack->size = ACK_SIZE;

	ack->rn = rn;
}

void ack_build(ack *ack) {
	ack->result_data = 0;

	ack->result_data |= (ack->command << 16);
	ack->result_data |= ack->rn;
}
