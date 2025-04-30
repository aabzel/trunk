#ifndef SCR1_TIMER_DIAG_H
#define SCR1_TIMER_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool scr1_timer_diag(void);
char* Scr1TimerClockSource2Str(uint8_t code);

#ifdef __cplusplus
}
#endif

#endif /* SCR1_TIMER_DIAG_H */
