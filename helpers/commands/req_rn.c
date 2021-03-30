#include "req_rn.h"

long req_rn_command(req_rn *req_rn) {
	long result = 0;

	result |= (req_rn->command << 32);
	result |= (req_rn->rn << 16);
	result |= req_rn->crc;

	return result;
}