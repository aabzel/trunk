#ifndef MPU_CUSTOM_TYPES_H
#define MPU_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mpu_custom_const.h"
#include "microcontroller.h"
#include "clock_const.h"
#include "mcal_types.h"


#define MPU_CUSTOM_VARIABLES    \
    volatile MPU_Type *MPUx;


typedef struct {
    volatile MPU_Type* MPUx;
    IRQn_Type irq_n;
    bool valid;
    Reg32_t* Regs;
    uint8_t num;
}MpuInfo_t;

typedef struct {
    bool valid;
    uint8_t code; /*see CORTEX_MPU_Region_Size*/
    uint32_t size;
}MpuRegionSizeInfo_t;

#ifdef __cplusplus
}
#endif

#endif /* MPU_CUSTOM_TYPES_H  */
