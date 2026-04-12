#ifndef CLOCK_DIAG_H
#define CLOCK_DIAG_H

#include "clock_types.h"

#ifdef HAS_CLOCK_CUSTOM_DIAG
#include "clock_custom_diag.h"
#endif

const char* ClockConfigToStr(const ClockConfig_t* const Config);
const char* ClockSettingToStr(const ClockSetting_t* const Node);
const char* ClkSrcToStr(ClockSource_t src);
const char* ClockBusToStr(ClockBus_t clock_bus);
const char* ClockMuxToStr(const ClockMux_t clock_mux);
bool clock_diag(void);

#endif
