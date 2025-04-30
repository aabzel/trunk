#ifndef AT32F413RC_DIAG_H
#define AT32F413RC_DIAG_H

#include "std_includes.h"
#ifdef HAS_AT32F413_FIRMWARE_LIB
#include "at32f413.h"
#endif
#include "interrupt_types.h"

const char* InterruptNumberToStr(int8_t int_n);

#endif /* AT32F413RC_DIAG_H */
