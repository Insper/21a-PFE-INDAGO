#include "write.h"

long write_command(write *write) {
	int result = 0;

	result |= (write->command << 49);
	result |= (write->mem_bank << 47);
	result |= (write->word_ptr << 39);
	result |= (write->data << 32);
	result |= (write->rn << 16);
	result |= write->crc;

	return result;
}