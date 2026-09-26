#ifndef MULTICORE_CUSTOM_DIAG_H
#define MULTICORE_CUSTOM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "multicore_custom_types.h"

bool MultiCoreDiagCpu2VtorReg(const CPUxVTOR_t* const Reg, char* prefix );
bool MultiCoreDiagCoreHoldReg(const CORE_HOLD_t* const CoreHoldReg);
bool multicore_custom_diag(void);

#ifdef __cplusplus
}
#endif

#endif /* MULTICORE_CUSTOM_DIAG_H */
