#ifndef SYSTICK_MCAL_DIAG_H
#define SYSTICK_MCAL_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "systick_types.h"

const char* SysTickConfigToStr(const SysTickConfig_t* const Config);
const char* SysTickClockSourceToStr(const SysTickClkSrc_t code);
bool systick_diag(void);

#ifdef __cplusplus
}
#endif

#endif /* SYSTICK_MCAL_DIAG_H */
