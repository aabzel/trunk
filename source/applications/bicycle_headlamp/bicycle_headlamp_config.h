#ifndef BICYCLE_HEADLAMP_CONFIG_H
#define BICYCLE_HEADLAMP_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "bicycle_headlamp_types.h"
#include "bicycle_headlamp_dep.h"

extern const BicycleHeadLampConfig_t BicycleHeadLampConfig[];
extern BicycleHeadLampHandle_t BicycleHeadLampInstance[];

uint32_t bicycle_headlamp_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* BICYCLE_HEADLAMP_CONFIG_H */
