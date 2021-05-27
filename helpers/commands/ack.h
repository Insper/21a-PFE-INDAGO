#ifndef ACK_H
#define ACK_H

#define ACK_COMMAND 0b01
#define ACK_SIZE 18

typedef struct
{
    unsigned char command;
    unsigned short rn;
    unsigned int size;
    unsigned int result_data;
} ack;

void ack_init(ack *ack, unsigned short rn);
void ack_build(ack *ack);
int ack_validate(unsigned long *command, unsigned int command_size);

#endif /* ACK_H */
