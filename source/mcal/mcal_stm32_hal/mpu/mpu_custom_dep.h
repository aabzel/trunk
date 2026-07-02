#ifndef MPU_CUSTOM_DEP_H
#define MPU_CUSTOM_DEP_H

#ifdef __cplusplus
extern "C" {
#endif


#ifndef __MPU_PRESENT
#error "+Enable FPU support in ARM-Cortex-M7 kernel settings."
#endif

#ifndef HAS_MPU
#error "+HAS_MPU"
#endif

#ifndef HAS_INTERRUPT
#error "+HAS_INTERRUPT"
#endif


#ifdef __cplusplus
}
#endif

#endif /* MPU_CUSTOM_DEP_H */
