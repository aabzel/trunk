#ifndef NVIC_DIAG_H
#define NVIC_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "nvic_types.h"

const char* InterruptNumberToStr(int8_t int_n);
const char* IntPri2Str(int8_t priority);
const char* NvicToStr(int8_t int_n);

#ifdef __cplusplus
}
#endif

#endif /* NVIC_DIAG_H  */
