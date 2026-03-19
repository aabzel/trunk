#ifndef MULTICORE_DIAG_H
#define MULTICORE_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_MULTICORE
#error "+HAS_MULTICORE"
#endif /*HAS_MULTICORE*/

#include <stdint.h>

#include "multicore_types.h"

bool multicore_diag(void);
bool MultiCoreDiagConfig(const MultiCoreConfig_t* const Config);
const char* MultiCoreConfigToStr(const MultiCoreConfig_t* const Config);

#ifdef __cplusplus
}
#endif

#endif /* MULTICORE_DIAG_H */
