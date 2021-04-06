#ifndef REQ_RN_H
#define REQ_RN_H

#define REQ_RN_COMMAND 0b11000001
#define REQ_RN_SIZE 40

typedef struct {
	unsigned char command;
	unsigned short rn;
	unsigned short crc;
	unsigned int size;
	unsigned long result_data;
} req_rn;

void req_rn_init(req_rn *req_rn, unsigned short rn, unsigned short crc);
void req_rn_build(req_rn *req_rn);

#endif /* REQ_RN_H */