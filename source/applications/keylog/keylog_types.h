#ifndef KEYLOG_TYPES_H
#define KEYLOG_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "keylog_const.h"
#include "fifo_char.h"

typedef struct{
	uint8_t key;
	FifoChar_t Fifo;
}KeyLog_t;

#ifdef __cplusplus
}
#endif

#endif /* KEYLOG_TYPES_H */
