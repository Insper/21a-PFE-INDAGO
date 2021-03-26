#ifndef QUERY_ADJUST_H
#define QUERY_ADJUST_H

typedef struct {
	unsigned char command;
	unsigned char session;
	unsigned char updn;
} query_adjust;
int query_adjust_command(query_adjust *query_adjust);

#endif /* QUERY_ADJUST_H */