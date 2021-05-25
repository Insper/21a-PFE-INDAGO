#include "req_rn.h"

void req_rn_init(req_rn *req_rn, unsigned short rn)
{
    req_rn->command = REQ_RN_COMMAND;
    req_rn->size = REQ_RN_SIZE;

    req_rn->rn = rn;
}

void req_rn_build(req_rn *req_rn)
{
    req_rn->result_data = 0;

    req_rn->result_data |= (req_rn->command << 24);
    req_rn->result_data |= (req_rn->rn);
    req_rn->crc = crc_16_ccitt(req_rn->result_data, 3);
    req_rn->result_data <<= 16;
    req_rn->result_data |= req_rn->crc;
}


int req_rn_process(unsigned long *command, unsigned int command_size, int STATE, unsigned short pin_tx,
                  unsigned char port_tx)
{
    if (command_size != REQ_RN_SIZE)
    {
        return READY;
    }

    req_rn _req_rn;
    _req_rn.crc = *command & 0xFFFF;
    _req_rn.rn = (*command >> 16) & 0xFFFF;

    switch (STATE)
    {
    case READY:
        return READY;
        break;

    case ARBITRATE:
        return ARBITRATE;
        break;

    case REPLY:
        return ARBITRATE;
        break;
        
    case ACKNOWLEDGED:
        if(HANDLE==_ack.rn){
            // Correct RN and ACCESS PSWD ><0  -> OPEN (BACKSCATTER HANDLE)
            // Correct RN and ACCESS PSWD =0  -> SECURED (BACKSCATTER HANDLE)
            // Incorrect -> Acknowledged
            return ACKNOWLEDGED;
        }
        // Incorrect -> Arbitrate
        return ARBITRATE;
        break;
    case OPEN:
        // Correct -> OPEN - BACKSCATTER new RN
        return OPEN;
        break;
    case SECURED:
        // Correct -> SECURED - BACKSCATTER new RN
        return SECURED;
    case KILLED:
        return KILLED;
        break;
    default:
        return READY;
        break;
    }
}