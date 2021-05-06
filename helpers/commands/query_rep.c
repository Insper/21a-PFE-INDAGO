#include "query_rep.h"

void query_rep_init(query_rep *query_rep, unsigned char session)
{
    query_rep->command = QUERY_REP_COMMAND;
    query_rep->size = QUERY_REP_SIZE;

    query_rep->session = session;
}

void query_rep_build(query_rep *query_rep)
{
    query_rep->result_data = 0;

    query_rep->result_data |= (query_rep->command << 2);
    query_rep->result_data |= query_rep->session;
}
