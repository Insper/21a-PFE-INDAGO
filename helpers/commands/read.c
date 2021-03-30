#include "read.h"

long read_command(read *read) {
	int result = 0;

	result |= (read->command << 49);
	result |= (read->mem_bank << 47);
	result |= (read->word_ptr << 39);
	result |= (read->word_count << 32);
	result |= (read->rn << 16);
	result |= read->crc;

	return result;
}