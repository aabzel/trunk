#ifndef CORTEX_MPU_MCAL_H
#define CORTEX_MPU_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "mpu_config.h"
#include "cortex_mpu_types.h"
#include "cortex_mpu_isr.h"

#ifdef HAS_MPU_DIAG
#include "cortex_mpu_diag.h"
#endif  

bool cortex_mpu_proc(void) ;
bool cortex_mpu_mcal_init(void);

/*setters*/
bool cortex_mpu_select_region(const uint8_t region);

/*getters*/
bool cortex_mpu_get_base_addr(const uint8_t rnr, uint32_t* const base_address);
bool cortex_mpu_get_size(const uint8_t region, uint32_t* const size);
bool cortex_mpu_get_access(const uint8_t region, ControlPermission_t* const Permission);
bool mpu_is_supported(void);
uint32_t mpu_get_region_cnt(void);

#ifdef __cplusplus
}
#endif

#endif // CORTEX_MPU_MCAL_H
