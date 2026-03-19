#ifndef MPU_CUSTOM_H
#define MPU_CUSTOM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "microcontroller_const.h"
#include "mpu_custom_isr.h"
#include "mpu_custom_diag.h"

uint8_t MpuSizeToCortexRegionSize(const uint32_t size) ;

#ifdef __cplusplus
}
#endif

#endif /* MPU_CUSTOM_H  */
