#ifndef FCSMU_DIAG_H
#define FCSMU_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_FCSMU
#error "+HAS_FCSMU"
#endif /*HAS_FCSMU*/

#include <stdint.h>

#include "fcsmu_types.h"

const char* FcsmuConfigToStr(const FcsmuConfig_t* const Config) ;
bool fcsmu_diag(void);
bool FcsmuDiagConfig(const FcsmuConfig_t* const Config);


#ifdef __cplusplus
}
#endif

#endif /* FCSMU_DIAG_H */
