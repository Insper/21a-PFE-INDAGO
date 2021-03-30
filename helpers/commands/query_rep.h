#ifndef QUERY_REP_H
#define QUERY_REP_H

typedef struct {
	unsigned char command;
	unsigned char session;
} query_rep;
int query_rep_command(query_rep *query_rep);

#endif /* QUERY_REP_H */