#ifndef LIMITER_H
#define LIMITER_H

#include <stdbool.h>
#include <stdint.h>

#include "limiter_types.h"

#ifndef HAS_LIMITER
#error "+ HAS_LIMITER"
#endif /*HAS_LIMITER*/

#ifndef HAS_TIME
#warning "+ HAS_TIME"
#endif /*HAS_TIME*/

#ifndef HAS_FLASH
#warning "+ HAS_FLASH"
#endif /*HAS_FLASH*/

uint64_t limiter_get_time_us(void);
bool limiter_init(Limiter_t* const node, uint64_t period_us);
bool limiter(Limiter_t* const node, uint32_t period_us, uint64_t cur_us);

#endif /* SRC_LIMITER_H */
