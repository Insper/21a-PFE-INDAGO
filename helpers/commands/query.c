#include "query.h"

void query_init(query *query, unsigned char dr, unsigned char m,
                unsigned char trext, unsigned char sel, unsigned char session,
                unsigned char target, unsigned char q)
{
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

void query_build(query *query)
{
    query->result_data = 0;

    query->result_data |= (query->command << 13);
    query->result_data |= (query->dr << 12);
    query->result_data |= (query->m << 10);
    query->result_data |= (query->trext << 9);
    query->result_data |= (query->sel << 7);
    query->result_data |= (query->session << 5);
    query->result_data |= (query->target << 4);
    query->result_data |= query->q;

    query->crc = crc5(query->result_data);

    query->result_data <<= 5;
    query->result_data |= (query->crc);
}

int query_process(unsigned long *command, unsigned int command_size, int STATE, unsigned short pin_tx,
                  unsigned char port_tx)
{
    if (command_size != QUERY_SIZE)
    {
        return READY;
    }

    query _query;
    _query.crc = *command & 0b11111;
    _query.q = (*command >> 5) & 0b1111;
    _query.target = (*command >> 9) & 1;
    _query.session = (*command >> 10) & 0b11;
    _query.sel = (*command >> 12) & 0b11;
    _query.trext = (*command >> 14) & 0b1;
    _query.m = (*command >> 15) & 0b11;
    _query.dr = (*command >> 17) & 0b1;

    if (crc5(*command >> 5) != _query.crc)
    {
        return READY;
    }

    switch (STATE)
    {
    case READY:
        HANDLE.value = rn16_generate();
        HANDLE.size = 16;
        fm0_encoder(HANDLE.value, HANDLE.size, TARI, pin_tx, port_tx);
        return REPLY;
        break;

    case ARBITRATE:
        HANDLE.value = rn16_generate();
        HANDLE.size = 16;
        fm0_encoder(HANDLE.value, HANDLE.size, TARI, pin_tx, port_tx);
        return REPLY;
        break;

    case REPLY:
        HANDLE.value = rn16_generate();
        HANDLE.size = 16;
        fm0_encoder(HANDLE.value, HANDLE.size, TARI, pin_tx, port_tx);
        return REPLY;
        break;
        
    case ACKNOWLEDGED:
        HANDLE.value = rn16_generate();
        HANDLE.size = 16;
        fm0_encoder(HANDLE.value, HANDLE.size, TARI, pin_tx, port_tx);
        return REPLY;
        break;
    case OPEN:
        HANDLE.value = rn16_generate();
        HANDLE.size = 16;
        fm0_encoder(HANDLE.value, HANDLE.size, TARI, pin_tx, port_tx);
        return REPLY;
        break;
    case SECURED:
        HANDLE.value = rn16_generate();
        HANDLE.size = 16;
        fm0_encoder(HANDLE.value, HANDLE.size, TARI, pin_tx, port_tx);
        return REPLY;
        break;
    case KILLED:
        return KILLED;
        break;
    default:
        return READY;
        break;
    }
}
