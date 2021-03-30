#ifndef KILL_H
#define KILL_H

typedef struct {
	unsigned char command;
	unsigned short password;
	unsigned char rfu;
	unsigned short rn;
	unsigned short crc;
} kill;
long kill_command(kill *kill);

#endif /* KILL_H */