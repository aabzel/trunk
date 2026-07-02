#ifndef STM32F407VG_H
#define STM32F407VG_H

#include <stm32f407xx.h>
#include "stm32f4xx.h"

#include "stm32f407vg_const.h"
#include "stm32f407vg_diag.h"

extern const IntNumInfo_t InterruptsNameDiag[];

const char* InterruptNumToStr(int16_t int_n);

#endif /* STM32F407VG_H */
