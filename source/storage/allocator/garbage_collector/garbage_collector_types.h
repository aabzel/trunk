#ifndef GARBAGE_COLLECTOR_TYPES_H
#define GARBAGE_COLLECTOR_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "garbage_collector_const.h"

typedef struct{
	uint32_t free_cnt;
}GarbageCollector_t;

#ifdef __cplusplus
}
#endif

#endif /* GARBAGE_COLLECTOR_TYPES_H */
