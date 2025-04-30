#ifndef LIS3DH_CONFIG_H
#define LIS3DH_CONFIG_H

#include "std_includes.h"
#include "lis3dh_types.h"

extern const Lis3dhConfig_t Lis3dhConfig[];
extern Lis3dhHandle_t Lis3dhInstance[];

uint32_t lis3dh_get_cnt(void);

#endif /* LIS3DH_CONFIG_H */
