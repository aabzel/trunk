#ifndef CORTEX_MPU_MCAL_DIAG_H
#define CORTEX_MPU_MCAL_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "cortex_mpu_types.h"
#include "microcontroller.h"

bool cortex_mpu_diag(void);
bool cortex_mpu_region(void);
bool CortexMpuRegsDiag(const MPU_Type* const Base) ;
bool CortexMpuRegsDiagLL(const MpuRegMap_t* const  PHY) ;
bool mpu_raw_reg_diag(void);

#ifdef __cplusplus
}
#endif

#endif /* CORTEX_MPU_MCAL_DIAG_H */
