#ifndef NAK_H
#define NAK_H

const unsigned char NAK_COMMAND = 0b11000000;
const unsigned int NAK_SIZE = 8;

typedef struct {
	unsigned char command;
	unsigned int size;
	unsigned char result_data;
} nak;
void nak_init(nak *nak);
void nak_build(nak *nak);

#endif /* NAK_H */