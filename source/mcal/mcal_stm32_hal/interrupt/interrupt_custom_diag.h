#ifndef INTERRUPT_CUSTOM_DIAGNOSTIC_H
#define INTERRUPT_CUSTOM_DIAGNOSTIC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

//const char* IntPriToStr(int8_t priority);
const char* InterruptToStr(int16_t int_n);
bool interrupt_custom_diag(char* key_word1, char* key_word2) ;

#ifdef __cplusplus
}
#endif

#endif /* INTERRUPT_CUSTOM_DIAGNOSTIC_H  */
