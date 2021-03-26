#include "query_rep.h"

int query_rep_command(query_rep *query_rep) {
	int result = 0;

	result |= (query_rep->command << 2);
	result |= query_rep->session;

	return result;
}