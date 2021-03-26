#ifndef REQ_RN_H
#define REQ_RN_H

typedef struct {
	unsigned char command;
	unsigned short rn;
	unsigned short crc;
} req_rn;
long req_rn_command(req_rn *req_rn);

#endif /* REQ_RN_H */