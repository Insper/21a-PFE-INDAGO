#ifndef ACK_H
#define ACK_H

typedef struct {
	unsigned char command;
	unsigned short rn;
} ack;
int ack_command(ack *ack);

#endif /* ACK_H */