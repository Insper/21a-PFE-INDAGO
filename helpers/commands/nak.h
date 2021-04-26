#ifndef NAK_H
#define NAK_H

#define NAK_COMMAND 0b11000000
#define NAK_SIZE 8

typedef struct {
	unsigned char command;
	unsigned int size;
	unsigned char result_data;
} nak;
void nak_init(nak *nak);
void nak_build(nak *nak);

#endif /* NAK_H */
