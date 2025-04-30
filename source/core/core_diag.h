#ifndef CORE_GENERAL_DIAG_H
#define CORE_GENERAL_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdbool.h>
#include <stdint.h>

#ifdef HAS_CORTEX_M4
#include "cortex_m4_diag.h"
#endif

#ifdef HAS_CORTEX_M33
#include "cortex_m33_diag.h"
#endif

#ifdef HAS_CORTEX_M4
#ifdef HAS_CORTEX_M33
#error  "Core contradiction!"
#endif
#endif


#ifdef __cplusplus
}
#endif

#endif /* CORE_GENERAL_DIAG_H */
