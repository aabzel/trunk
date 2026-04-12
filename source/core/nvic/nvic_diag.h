#ifndef NVIC_DIAG_H
#define NVIC_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

const char* IntPriToStr(int8_t priority);
const char* NvicToStr(int8_t int_n);

#ifdef __cplusplus
}
#endif

#endif /* NVIC_DIAG_H  */
