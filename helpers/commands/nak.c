#include "nak.h"

void nak_init(nak *nak) {
	nak->command = NAK_COMMAND;
	nak->size = NAK_SIZE;
}

void nak_build(nak *nak) {
	nak->result_data = nak->command;
}
