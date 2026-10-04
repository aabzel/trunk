#ifndef LASER_SIGHT_CONFIG_H
#define LASER_SIGHT_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "laser_sight_types.h"
#include "laser_sight_dep.h"

extern const LaserSightConfig_t LaserSightConfig[];
extern LaserSightHandle_t LaserSightInstance[];

uint32_t laser_sight_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* LASER_SIGHT_CONFIG_H */
