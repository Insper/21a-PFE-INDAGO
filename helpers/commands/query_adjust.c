#include "query_adjust.h"

int query_adjust_command(query_adjust *query_adjust) {
	int result = 0;

	result |= (query_adjust->command << 5);
	result |= (query_adjust->session << 3);
	result |= query_adjust->updn;

	return result;
}