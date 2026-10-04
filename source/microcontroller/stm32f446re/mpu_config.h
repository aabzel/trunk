#ifndef MPU_CONFIG_H
#define MPU_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "mpu_types.h"
#include "mpu_dep.h"

extern char gMpuTestDataBanWrite[];
extern char gMpuTestDataBanRead[];
extern char gMpuTestDataBanAll[];

extern const MpuConfig_t MpuConfig[];
extern MpuHandle_t MpuInstance[];

#define MPU_STACK_HEAP_REGION_SIZE 256U

uint32_t mpu_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* MPU_CONFIG_H */
