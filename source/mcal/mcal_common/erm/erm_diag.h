#ifndef ERM_DIAG_H
#define ERM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_ERM
#error "+HAS_ERM"
#endif /*HAS_ERM*/

#include <stdint.h>

#include "erm_types.h"
#include "erm_custom_diag.h"

bool erm_diag(void);
bool ErmDiagConfig(const ErmConfig_t* const Config);
const char* ErmConfigToStr(const ErmConfig_t* const Config);

#ifdef __cplusplus
}
#endif

#endif /* ERM_DIAG_H */
