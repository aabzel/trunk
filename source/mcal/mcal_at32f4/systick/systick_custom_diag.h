#ifndef SYSTICK_CUSTOM_DIAG_H
#define SYSTICK_CUSTOM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

const char* SysTickCountFlag2Str(uint8_t code);
const char* SysTickClkSrc2Str(uint8_t code);
const char* SysTickInt2Str(uint8_t code);
const char* SysTickEn2Str(uint8_t code);

#ifdef __cplusplus
}
#endif

#endif // SYSTICK_CUSTOM_DIAG_H
