#ifndef NONE_BLOCKING_PAUSE_H
#define NONE_BLOCKING_PAUSE_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

bool wait_in_loop_ms(uint32_t wait_pause_ms);
bool wait_us(uint64_t wait_pause_us);
bool wait_ms(uint32_t wait_pause_ms);

#ifdef __cplusplus
}
#endif

#endif /* NONE_BLOCKING_PAUSE_H */
