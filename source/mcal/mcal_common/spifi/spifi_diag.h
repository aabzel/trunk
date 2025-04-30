#ifndef SPIFI_DIAG_H
#define SPIFI_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_SPIFI
#error "+HAS_SPIFI"
#endif /*HAS_SPIFI*/

#include "std_includes.h"
#include "spifi_types.h"

bool spifi_diag(void);
bool SpiFiDiagConfig(const SpiFiConfig_t* const Config);
const char* SpiFiConfigToStr(const SpiFiConfig_t* const Config);

#ifdef __cplusplus
}
#endif

#endif /* SPIFI_DIAG_H */
