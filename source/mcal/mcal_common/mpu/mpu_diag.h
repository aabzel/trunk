#ifndef MPU_DIAG_H
#define MPU_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "mpu_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_MPU
#error "+HAS_MPU"
#endif /*HAS_MPU*/

#ifndef HAS_MPU_DIAG
#error "+HAS_MPU_DIAG"
#endif /*HAS_DIAG_MPU*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

bool mpu_diag(void);
const char* MpuPermissionToStr(const MpuPermission_t* const permission);
const char* MpuRegionToStr(const MpuRegionConfig_t* const Region);
const char* MpuConfigToStr(const MpuConfig_t* const Config);
const char* MpuNodeToStr(const MpuHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* MPU_DIAG_H  */
