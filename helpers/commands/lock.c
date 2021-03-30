#include "lock.h"

long lock_command(lock *lock) {
	long result = 0;

	result |= (lock->command << 52);
	result |= (lock->payload << 32);
	result |= (lock->rn << 16);
	result |= lock->crc;

	return result;
}