#ifndef STM32F407VE_DIAG_H
#define STM32F407VE_DIAG_H

#include "std_includes.h"
#include "interrupt_types.h"

extern const IntNumInfo_t IntNumInfo[];

const char* InterruptNumberToStr(int16_t int_n);
uint32_t interrupt_info_get_cnt(void);


#endif /* STM32F407VE_DIAG_H */
