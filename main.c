#include <stdio.h>

typedef struct {
	unsigned char command;
	unsigned char dr;
	unsigned char m;
	unsigned char trext;
	unsigned char sel;
	unsigned char session;
	unsigned char target;
	unsigned char q;
	unsigned char crc;
} query;


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

int main(void) {
  query query;
  query.command = 8;
  query.dr = 0;
  query.m = 0;
  query.trext = 0;
  query.sel = 0;
  query.session = 0;
  query.target = 0;
  query.q = 1;
  query.crc = 4;
  // 10 0000 0000 0000 0010 0100
  // printf("Antes: %d\n", query.command);

  int xxx = query_command(&query);
  printf("Valor: %d\n", xxx);
  return 0;
}