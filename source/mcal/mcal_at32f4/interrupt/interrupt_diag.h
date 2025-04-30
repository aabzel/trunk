#ifndef INTERRUPT_DIAGNOSTIC_H
#define INTERRUPT_DIAGNOSTIC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//const char* IntPri2Str(int8_t priority);
const char* interrupt2Str(int8_t int_n);

#ifdef __cplusplus
}
#endif

#endif /* INTERRUPT_DIAGNOSTIC_H  */
