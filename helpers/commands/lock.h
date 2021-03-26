#ifndef LOCK_H
#define LOCK_H

typedef struct {
	unsigned char command;
	unsigned int payload;
	unsigned short rn;
	unsigned short crc;
} lock;
long lock_command(lock *lock);

#endif /* LOCK_H */