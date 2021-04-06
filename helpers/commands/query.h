#ifndef QUERY_H
#define QUERY_H
#include "../config.h"
#include "../crc.h"

const unsigned char QUERY_COMMAND = 0b1000;
const unsigned int QUERY_SIZE = 22;

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
	unsigned int size;
	unsigned int result_data;
} query;
void query_init(query *query, unsigned char dr, unsigned char m, unsigned char trext, unsigned char sel, unsigned char session, unsigned char target, unsigned char q);
void query_build(query *query);

#endif /* QUERY_H */