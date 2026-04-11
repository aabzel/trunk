#ifndef CLOCK_CUSTOM_DIAG_H
#define CLOCK_CUSTOM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "clock_custom_types.h"

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

#ifndef HAS_CLOCK
#error "+HAS_CLOCK"
#endif

const char*  Stm32RccCsrToStr(const  Stm32RccCsr_t* const  Reg) ;
bool periph_clock_diag(char *keyWord1,char *keyWord2);
bool clock_custom_diag(void);

#ifdef __cplusplus
}
#endif

#endif // CLOCK_CUSTOM_DIAG_H
