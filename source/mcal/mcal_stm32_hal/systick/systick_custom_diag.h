#ifndef SYSTICK_STM32_DIAG_H
#define SYSTICK_STM32_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

const char* SysTickCountFlagToStr(uint8_t code);
const char* SysTickClkSrcToStr(uint8_t code);
const char* SysTickIntToStr(uint8_t code);
const char* SysTickEnToStr(uint8_t code);

#ifdef __cplusplus
}
#endif

#endif // SYSTICK_STM32_DIAG_H
