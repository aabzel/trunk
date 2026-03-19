#ifndef MPU_CUSTOM_DIAG_H
#define MPU_CUSTOM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "mpu_custom_types.h"

bool mpu_diag_low_level(uint8_t num, const char* const keyword);
const char* MpuInfoToStr(const MpuInfo_t* const Info);
const char* MpuRegionSizeInfoToStr(const MpuRegionSizeInfo_t *const RegionInfo);

#ifdef __cplusplus
}
#endif

#endif /* MPU_CUSTOM_DIAG_H */
