#ifndef DRV8870_DIAG_H
#define DRV8870_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "drv8870_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_DRV8870
#error "+HAS_DRV8870"
#endif

#ifndef HAS_DRV8870_DIAG
#error "+HAS_DRV8870_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool drv8870_diag(void);
const char* Drv8870ConfigToStr(const Drv8870Config_t* const Config);
const char* Drv8870NodeToStr(const Drv8870Handle_t* const Node);
const char* Drv8870ModeToStr(const Drv8870Mode_t mode);

#ifdef __cplusplus
}
#endif

#endif /* DRV8870_DIAG_H  */
