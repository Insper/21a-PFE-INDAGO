#include "lock.h"

void lock_init(lock *lock, unsigned int payload, unsigned short rn,
               unsigned short crc)
{
    lock->command = LOCK_COMMAND;
    lock->size = LOCK_SIZE;

    lock->payload = payload;
    lock->rn = rn;
    lock->crc = crc;
}

void lock_build(lock *lock)
{
    lock->result_data = 0;

    lock->result_data |= (lock->command << 52);
    lock->result_data |= (lock->payload << 32);
    lock->result_data |= (lock->rn << 16);
    lock->result_data |= lock->crc;
}
