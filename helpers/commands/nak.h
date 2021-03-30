#ifndef NAK_H
#define NAK_H

typedef struct {
	unsigned char command;
} nak;
char nak_command(nak *nak);

#endif /* NAK_H */