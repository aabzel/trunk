#ifndef MPU_CUSTOM_CONST_H
#define MPU_CUSTOM_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mpu_dep.h"

#if 0
/* Table B3-15 Access permissions field encoding */
typedef enum{
    /*                                Privileged           Unprivileged       */
    MPU_ACCESS_PERM_NO_ACCESS = 0,   /*  No access            No access          */
    MPU_ACCESS_PERM_FULL_ACCESS = 3, /*  Read/write           Read/write         */
    MPU_ACCESS_PERM_READONLY = 6,    /*  Read-only            Read-only  */
    MPU_ACCESS_PERM_READONLY2 = 7,   /*  Read-only            Read-only  */
    MPU_ACCESS_PERM_UNDEF=8,         /*       */
} MpuAccessPermissions_t ;
#endif


#ifdef __cplusplus
}
#endif

#endif /* MPU_CUSTOM_CONST_H  */
