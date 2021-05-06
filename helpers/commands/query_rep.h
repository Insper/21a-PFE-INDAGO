#ifndef QUERY_REP_H
#define QUERY_REP_H

#define QUERY_REP_COMMAND 0b00
#define QUERY_REP_SIZE 4

typedef struct
{
    unsigned char command;
    unsigned char session;
    unsigned int size;
    unsigned int result_data;
} query_rep;
void query_rep_init(query_rep *query_rep, unsigned char session);
void query_rep_build(query_rep *query_rep);

#endif /* QUERY_REP_H */
