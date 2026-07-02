#ifndef INTERRUPT_DIAG_H
#define INTERRUPT_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

const char* IntPriToStr(int8_t priority);
const char* NvicToStr(int8_t int_n);

#ifdef __cplusplus
}
#endif

#endif /* INTERRUPT_DIAG_H  */
