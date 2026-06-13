#ifndef SMOOTH_LAMP_DIAG_H
#define SMOOTH_LAMP_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "smooth_lamp_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_SMOOTH_LAMP
#error "+HAS_SMOOTH_LAMP"
#endif /**/

#ifndef HAS_SMOOTH_LAMP_DIAG
#error "+HAS_SMOOTH_LAMP_DIAG"
#endif /**/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /**/

bool smooth_lamp_diag(void);
const char* SmoothLampConfigToStr(const SmoothLampConfig_t* const Config);
const char* SmoothLampNodeToStr(const SmoothLampHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* SMOOTH_LAMP_DIAG_H  */
