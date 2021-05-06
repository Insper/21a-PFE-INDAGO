#include "query_adjust.h"

void query_adjust_init(query_adjust *query_adjust, unsigned char session,
                       unsigned char updn)
{
    query_adjust->command = QUERY_ADJUST_COMMAND;
    query_adjust->size = QUERY_ADJUST_SIZE;

    query_adjust->session = session;
    query_adjust->updn = updn;
}

int query_adjust_command(query_adjust *query_adjust)
{
    query_adjust->result_data = 0;

    query_adjust->result_data |= (query_adjust->command << 5);
    query_adjust->result_data |= (query_adjust->session << 3);
    query_adjust->result_data |= query_adjust->updn;
}
