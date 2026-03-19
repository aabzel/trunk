#ifndef GARLAND_CONFIG_H
#define GARLAND_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "garland_types.h"

extern const GarLandConfig_t GarLandConfig[];
extern GarLandHandle_t GarLandInstance[];

uint32_t garland_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* GARLAND_CONFIG_H */
