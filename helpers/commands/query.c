#include "query.h"

void query_init(query *query, unsigned char dr, unsigned char m, unsigned char trext, unsigned char sel, unsigned char session, unsigned char target, unsigned char q) {
	query->command = QUERY_COMMAND;
	query->size = QUERY_SIZE;
  query->dr = dr;
	query->m = m;
	query->trext = trext;
	query->sel = sel;
	query->session = session;
	query->target = target;
	query->q = q;
}

void query_command(query *query) {
	query->result_data = 0;

	query->result_data |= (query->command << 13);
	query->result_data |= (query->dr << 12);
	query->result_data |= (query->m << 10);
	query->result_data |= (query->trext << 9);
	query->result_data |= (query->sel << 7);
	query->result_data |= (query->session << 5);
	query->result_data |= (query->target << 4);
	query->result_data |= query->q;
	
	query->crc = crc5(query->result_data, INITIAL_REMAINDER_5, POLYNOMIAL_5);
	
	query->result_data <<= 5;
	query->result_data |= (query->crc);
}
