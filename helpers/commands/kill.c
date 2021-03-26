#include "kill.h"

long kill_command(kill *kill) {
	long result = 0;

	result |= (kill->command << 51);
	result |= (kill->password << 35);
	result |= (kill->rfu << 32);
	result |= (kill->rn << 16);
	result |= kill->crc;

	return result;
}