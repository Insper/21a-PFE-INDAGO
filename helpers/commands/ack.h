#ifndef ACK_H
#define ACK_H

const int ACK_COMMAND = 0b01;
const int ACK_SIZE = 18;

typedef struct {
	unsigned char command;
	unsigned short rn;
	unsigned int size;
	unsigned int result_data;
} ack;
void ack_init(ack *ack, unsigned short rn);
void ack_build(ack *ack);

#endif /* ACK_H */