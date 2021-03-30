#ifndef QUERY_H
#define QUERY_H

typedef struct {
	unsigned char command;
	unsigned char dr;
	unsigned char m;
	unsigned char trext;
	unsigned char sel;
	unsigned char session;
	unsigned char target;
	unsigned char q;
} query;
int query_command(query *query, uint8_t  remainder, uint8_t  polynomial);

#endif /* QUERY_H */