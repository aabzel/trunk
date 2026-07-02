#ifndef STM32F746NG_H
#define STM32F746NG_H

#include <stm32f746xx.h>
// #include "stm32f7xx.h"
#include "stm32fx_hal.h"
#include "stm32f746ng_types.h"
#include "stm32f746ng_diag.h"

extern const IntNumInfo_t InterruptsNameDiag[];

const char* InterruptNumToStr(int16_t int_n);

#endif /* STM32F746NG_H */
