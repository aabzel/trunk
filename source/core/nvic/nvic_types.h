#ifndef NVIC_TYPES_S
#define NVIC_TYPES_S

#ifdef __cplusplus
extern "C" {
#endif

#include "nvic_dep.h"
#include "std_includes.h"
#include "interrupt_types.h"

#ifdef HAS_VENDOR_SDK
#ifndef HAS_CMSIS
#error "+HAS_CMSIS"
#endif
#endif

#ifndef HAS_NVIC
#error "+HAS_NVIC"
#endif


#ifdef __cplusplus
}
#endif

#endif /* NVIC_TYPES_S  */
