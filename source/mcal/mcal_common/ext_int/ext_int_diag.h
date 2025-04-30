#ifndef EXT_INT_DIAG_H
#define EXT_INT_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_EXT_INT
#error "+HAS_EXT_INT"
#endif /*HAS_EXT_INT*/

#include <stdint.h>

#include "ext_int_types.h"

const char* ExtIntEdgeToStr(PinIntEdge_t code);
bool ext_int_diag(void);
bool ExtIntDiagConfig(const ExtIntConfig_t* const Config);
const char* ExtIntConfigToStr(const ExtIntConfig_t* const Config);

#ifdef __cplusplus
}
#endif

#endif /* EXT_INT_DIAG_H */
