#ifndef YTM32X_DIAG_H
#define YTM32X_DIAG_H

#include "std_includes.h"
#include "interrupt_types.h"

const char* InterruptNumberToStr(int16_t int_n);
extern const IntNumInfo_t IntNumInfo[];
uint32_t interrupt_info_get_cnt(void);
#endif /* YTM32X_DIAG_H */
