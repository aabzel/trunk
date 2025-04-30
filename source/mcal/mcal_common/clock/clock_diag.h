#ifndef CLOCK_DIAG_H
#define CLOCK_DIAG_H

#include "clock_types.h"
#ifdef HAS_DIAG
#include "clock_custom_diag.h"
#endif

const char* ClockSettingToStr(const ClockSetting_t* const Node);
const char* ClkSrc2Str(ClockSource_t src);
const char* ClockBusToStr(ClockBus_t clock_bus);

#endif /* CLOCK_DIAG_H */
