#include "select.h"

int select_command(select *select) {
	int result = 0;

	result |= (select->command << 40);
	result |= (select->target << 37);
	result |= (select->action << 34);
	result |= (select->mem_bank << 32);
	result |= (select->pointer << 24);
	result |= (select->length << 16);
	result |= (select->mask << 2);
	result |= (select->truncate << 2);
	result |= select->crc;

	return result;
}