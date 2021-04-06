// Mandatory Commands
// Definition
#include "query_rep.h"
#include "ack.h"
#include "query.h"
#include "query_adjust.h"
#include "select.h"
#include "nak.h"
#include "req_rn.h"
#include "read.h"
#include "write.h"
#include "kill.h"
#include "lock.h"

// Value
#define QUERY_ADJUST 0b1001
#define SELECT 0b1010
#define NAK 0b11000000
#define REQ_RN 0b11000001
#define READ 0b11000010
#define WRITE 0b11000011
#define KILL 0b11000100
#define LOCK 0b11000101


