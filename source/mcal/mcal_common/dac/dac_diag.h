#ifndef DAC_DIAG_H
#define DAC_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_DAC
#error "+HAS_DAC"
#endif /*HAS_DAC*/

#include <stdint.h>

#include "dac_types.h"

bool dac_diag(void);
bool DacDiagConfig(const DacConfig_t* const Config);
const char* DacConfigToStr(const DacConfig_t* const Config);

#ifdef __cplusplus
}
#endif

#endif /* DAC_DIAG_H */
