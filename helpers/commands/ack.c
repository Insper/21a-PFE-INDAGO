#include "ack.h"

int ack_command(ack *ack) {
	int result = 0;

	result |= (ack->command << 16);
	result |= ack->rn;

	return result;
}