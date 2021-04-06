#ifndef KILL_H
#define KILL_H

const unsigned char KILL_COMMAND = 0b11000100;
const unsigned int KILL_SIZE = 59;

typedef struct {
	unsigned char command;
	unsigned short password;
	unsigned char rfu;
	unsigned short rn;
	unsigned short crc;
	unsigned int size;
	unsigned long result_data;
} kill;

void kill_init(kill *kill, unsigned short password, unsigned char rfu, unsigned short rn, unsigned short crc);
void kill_build(kill *kill);

#endif /* KILL_H */