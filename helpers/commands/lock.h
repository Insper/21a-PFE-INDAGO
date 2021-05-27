#ifndef LOCK_H
#define LOCK_H

#define LOCK_COMMAND 0b11000101
#define LOCK_SIZE 60

typedef struct
{
    unsigned char command;
    unsigned int payload;
    unsigned short rn;
    unsigned short crc;
    unsigned int size;
    unsigned long result_data;
} lock;

void lock_init(lock *lock, unsigned int payload, unsigned short rn,
               unsigned short crc);
void lock_build(lock *lock);

#endif /* LOCK_H */
