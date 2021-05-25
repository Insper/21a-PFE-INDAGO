#include "ack.h"

void ack_init(ack *ack, unsigned short rn)
{
    ack->command = ACK_COMMAND;
    ack->size = ACK_SIZE;

    ack->rn = rn;
}

void ack_build(ack *ack)
{
    ack->result_data = 0;

    ack->result_data |= (ack->command << 16);
    ack->result_data |= ack->rn;
}


int ack_process(unsigned long *command, unsigned int command_size, int STATE, unsigned short pin_tx,
                  unsigned char port_tx)
{
    if (command_size != ACK_SIZE)
    {
        return READY;
    }

    ack _ack;
    _ack.rn = *command & 0xFFFF;


    switch (STATE)
    {
    case READY:
        return READY;
        break;

    case ARBITRATE:
        return ARBITRATE;
        break;

    case REPLY:
        if(HANDLE==_ack.rn){
            // Correct -> Acknowledged
            // Tabela 6-17
            return ACKNOWLEDGED;
        }
        // Incorrect -> Arbitrate
        return ARBITRATE;
        break;
        
    case ACKNOWLEDGED:
        if(HANDLE==_ack.rn){
            // Correct -> Acknowledged
            // Tabela 6-17
            return ACKNOWLEDGED;
        }
        // Incorrect -> Arbitrate
        return ARBITRATE;
        break;
    case OPEN:
        if(HANDLE==_ack.rn){
            // Correct -> OPEN
            // Tabela 6-17
            return OPEN;
        }
        // Incorrect -> Arbitrate
        return ARBITRATE;
        break;
    case SECURED:
        if(HANDLE==_ack.rn){
            // Correct -> SECURED
            // Tabela 6-17
            return SECURED;
        }
        // Incorrect -> Arbitrate
        return ARBITRATE;
    case KILLED:
        return KILLED;
        break;
    default:
        return READY;
        break;
    }
}