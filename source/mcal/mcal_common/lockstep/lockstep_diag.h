#ifndef LOCKSTEP_DIAG_H
#define LOCKSTEP_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_LOCKSTEP
#error "+HAS_LOCKSTEP"
#endif /*HAS_LOCKSTEP*/

#include <stdint.h>

#include "lockstep_types.h"

bool lockstep_diag_one(uint32_t num);
bool lockstep_diag(void);
bool LockStepDiagConfig(const LockStepConfig_t* const Config);
const char* LockStepConfigToStr(const LockStepConfig_t* const Config);

#ifdef __cplusplus
}
#endif

#endif /* LOCKSTEP_DIAG_H */
