#ifndef GARBAGE_COLLECTOR_H
#define GARBAGE_COLLECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "garbage_collector_types.h"

#ifndef HAS_MCU
#error  "That code only for MCU where all RAM memory is physical"
#endif

#ifndef HAS_GARBAGE_COLLECTOR
#error "It is needed HAS_GARBAGE_COLLECTOR option for that component"
#endif

bool garbage_collector_proc(void);

#ifdef __cplusplus
}
#endif

#endif /* GARBAGE_COLLECTOR_H */
