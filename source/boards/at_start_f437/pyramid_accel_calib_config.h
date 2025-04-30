#ifndef LIS3DH_CONFIG_H
#define LIS3DH_CONFIG_H

#include "std_includes.h"
#include "pyramid_accel_calib_types.h"

extern const PyramidAccelCalibConfig_t PyramidAccelCalibConfig[];
extern PyramidAccelCalibHandle_t PyramidAccelCalibInstance[];

uint32_t pyramid_accel_calib_get_cnt(void);

#endif /* LIS3DH_CONFIG_H */
