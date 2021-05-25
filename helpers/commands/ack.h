#ifndef ACK_H
#define ACK_H

#define ACK_COMMAND 0b01
#define ACK_SIZE 18

extern volatile rn16 HANDLE;

typedef struct
{
    unsigned char command;
    unsigned short rn;
    unsigned int size;
    unsigned int result_data;
} ack;

void ack_init(ack *ack, unsigned short rn);
void ack_build(ack *ack);
int  ack_process(unsigned long *command, unsigned int command_size, int STATE, unsigned short pin_tx,
                  unsigned char port_tx);

#endif /* ACK_H */
