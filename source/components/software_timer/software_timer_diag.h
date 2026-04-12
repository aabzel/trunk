#ifndef SOFTWARE_TIMER_DIAG_H
#define SOFTWARE_TIMER_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "software_timer_const.h"

const char *SwTimNumToStr(uint32_t num);
char *SwTimDirToStr(SwTimerCntDir_t code);
char *SwTimModeToStr(SwTimerMode_t code);

#ifdef __cplusplus
}
#endif

#endif /* SOFTWARE_TIMER_DIAG_H */
