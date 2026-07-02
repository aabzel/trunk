#ifndef SYSTICK_GENERAL_DIAG_H
#define SYSTICK_GENERAL_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "systick_const.h"

const char* SysTickClockSourceToStr(const SysTickClkSrc_t code);
bool systick_diag(void);

#ifdef __cplusplus
}
#endif

#endif /* SYSTICK_GENERAL_DIAG_H */
