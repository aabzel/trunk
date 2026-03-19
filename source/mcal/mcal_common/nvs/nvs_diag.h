#ifndef NVS_DIAG_H
#define NVS_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "nvs_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /**/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

#ifndef HAS_NVS
#error "+HAS_NVS"
#endif /**/

#ifndef HAS_NVS_DIAG
#error "+HAS_NVS_DIAG"
#endif /**/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /**/

bool nvs_diag_one(uint8_t num);
bool nvs_diag(void);
const char* NvsConfigToStr(const NvsConfig_t* const Config);
const char* NvsNodeToStr(const NvsHandle_t* const Node);
#ifdef __cplusplus
}
#endif

#endif /* NVS_DIAG_H  */
