#ifndef SMOOTH_LAMP_CONFIG_H
#define SMOOTH_LAMP_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "smooth_lamp_types.h"
#include "smooth_lamp_dep.h"

extern const SmoothLampConfig_t SmoothLampConfig[];
extern SmoothLampHandle_t SmoothLampInstance[];

uint32_t smooth_lamp_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* SMOOTH_LAMP_CONFIG_H */
