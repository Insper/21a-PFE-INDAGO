#include "nak.h"

void nak_init(nak *nak) {
	nak->command = NAK_COMMAND;
	nak->size = NAK_SIZE;
}

void nak_build(nak *nak) {
	nak->result_data = nak->command;
}

int nak_validate(unsigned long long *command, unsigned int command_size) {
    if(command_size!=NAK_SIZE){
        return 0;
    }
	if(((*command) & 0b11111111)!=NAK_COMMAND){
        return 0;
    }
    return 1;
}
