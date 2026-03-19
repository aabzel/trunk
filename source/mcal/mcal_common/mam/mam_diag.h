#ifndef MAM_DIAG_H
#define MAM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "mam_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_MAM
#error "+HAS_MAM"
#endif

#ifndef HAS_MAM_DIAG
#error "+HAS_MAM_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool mam_diag(void);
const char* MamMastersToStr(const MamMaster_t Masters);
const char* MamConfigToStr(const MamConfig_t* const Config);
const char* MamNodeToStr(const MamHandle_t* const Node);
const char* MamDiagRegion(const MamMemoryAccessConfig_t* const Region);

#ifdef __cplusplus
}
#endif

#endif /* MAM_DIAG_H  */
