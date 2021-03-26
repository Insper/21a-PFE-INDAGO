#include "query.h"

int query_command(query *query) {
	int result = 0;

	result |= (query->command << 18);
	result |= (query->dr << 17);
	result |= (query->m << 15);
	result |= (query->trext << 14);
	result |= (query->sel << 12);
	result |= (query->session << 10);
	result |= (query->target << 9);
	result |= (query->q << 5);
	result |= query->crc;

	return result;
}