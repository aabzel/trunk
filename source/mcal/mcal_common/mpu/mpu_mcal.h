#ifndef MPU_MCAL_H
#define MPU_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "mpu_config.h"
#include "mpu_types.h"
#include "mpu_isr.h"
#ifdef HAS_MPU_DIAG
#include "mpu_diag.h"
#endif

/* API */
const MpuConfig_t* MpuGetConfig(uint8_t num);
MpuHandle_t* MpuGetNode(uint8_t num);
bool MpuIsValidConfig(const MpuConfig_t* const Config);

#ifdef HAS_MPU_CUSTOM
const MpuInfo_t* MpuGetInfo(uint8_t num);
#endif

bool mpu_mcal_init(void);
bool mpu_init_custom(void);
bool mpu_init_one(uint8_t num);
bool mpu_init_common(const MpuConfig_t* const Config,
                              MpuHandle_t* const Node);

bool mpu_proc_one(uint8_t num);
bool mpu_proc(void);

/*setters*/
bool mpu_ctrl(uint8_t num, bool on_off);

/*getters*/

#ifdef __cplusplus
}
#endif

#endif /* MPU_MCAL_H */
