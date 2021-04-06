#ifndef QUERY_ADJUST_H
#define QUERY_ADJUST_H

const unsigned char QUERY_ADJUST_COMMAND = 0b1001;
const unsigned int QUERY_ADJUST_SIZE = 9;

typedef struct {
	unsigned char command;
	unsigned char session;
	unsigned char updn;
	unsigned int size;
	unsigned int result_data;
} query_adjust;
void query_adjust_init(query_adjust *query_adjust, unsigned char session, unsigned char updn);
void query_adjust_build(query_adjust *query_adjust);

#endif /* QUERY_ADJUST_H */