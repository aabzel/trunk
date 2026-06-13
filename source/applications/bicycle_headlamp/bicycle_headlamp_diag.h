#ifndef BICYCLE_HEADLAMP_DIAG_H
#define BICYCLE_HEADLAMP_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "bicycle_headlamp_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_BICYCLE_HEADLAMP
#error "+HAS_BICYCLE_HEADLAMP"
#endif

#ifndef HAS_BICYCLE_HEADLAMP_DIAG
#error "+HAS_BICYCLE_HEADLAMP_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool bicycle_headlamp_diag(void);
bool bicycle_headlamp_diag_one(uint8_t num);
const char* BicycleHeadLampConfigToStr(const BicycleHeadLampConfig_t* const Config);
const char* BicycleHeadLampNodeToStr(const BicycleHeadLampHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* BICYCLE_HEADLAMP_DIAG_H  */
