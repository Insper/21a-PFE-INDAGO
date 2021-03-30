#include "query.h"

int query_command(query *query, uint8_t  remainder, uint8_t  polynomial) {
	int result = 0;

	result |= (query->command << 13);
	result |= (query->dr << 12);
	result |= (query->m << 10);
	result |= (query->trext << 9);
	result |= (query->sel << 7);
	result |= (query->session << 5);
	result |= (query->target << 4);
	result |= query->q;
	uint8_t crc_result = crc5(result, remainder, polynomial);
	result <<= 5;
	result |= (crc_result);

	return result;
}