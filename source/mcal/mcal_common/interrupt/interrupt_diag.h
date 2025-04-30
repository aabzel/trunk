#ifndef INTERRUPT_DIAGNOSTIC_H
#define INTERRUPT_DIAGNOSTIC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "interrupt_types.h"

//const char* IntPri2Str(int8_t priority);
const char* InterruptConfigToStr(const InterruptConfig_t* const Config);
bool interrupt_diag(char* key_word1, char* key_word2);
const char* InterruptNumToStr(int16_t int_n);
const char* interrupt2Str(int8_t int_n);

#ifdef __cplusplus
}
#endif

#endif /* INTERRUPT_DIAGNOSTIC_H  */
