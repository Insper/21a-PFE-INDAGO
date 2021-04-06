#ifndef LOCK_H
#define LOCK_H

const unsigned char LOCK_COMMAND = 0b11000101;
const unsigned int LOCK_SIZE = 60;

typedef struct {
	unsigned char command;
	unsigned int payload;
	unsigned short rn;
	unsigned short crc;
	unsigned int size;
	unsigned long result_data;
} lock;

void lock_init(lock *lock, unsigned int payload, unsigned short rn, unsigned short crc);
void lock_build(lock *lock);

#endif /* LOCK_H */