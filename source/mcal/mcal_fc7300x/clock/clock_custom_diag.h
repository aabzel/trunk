#ifndef CLOCK_CUSTOM_DIAG_H
#define CLOCK_CUSTOM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

#include "std_includes.h"

bool clock1_diag(void) ;
bool clock2_diag(void) ;

#ifdef __cplusplus
}
#endif

#endif // CLOCK_CUSTOM_DIAG_H
