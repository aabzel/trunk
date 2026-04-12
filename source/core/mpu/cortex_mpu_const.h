#ifndef CORTEX_MPU_MCAL_CONST_H
#define CORTEX_MPU_MCAL_CONST_H

#ifdef __cplusplus
extern "C" {
#endif


#include "cortex_mpu_dep.h"

#if 0
typedef enum{
    /*                                Privileged                 */
    MPU_PRIV_ACCESS_PERM_NO_ACCESS = 0,    /*  No access                   */
    MPU_PRIV_ACCESS_PERM_FULL_ACCESS= 1,   /*  Read/write                  */
    MPU_PRIV_ACCESS_PERM_FULL_ACCESS1= 2,  /*  Read/write                  */
    MPU_PRIV_ACCESS_PERM_FULL_ACCESS2= 3,  /*  Read/write                  */
    MPU_PRIV_ACCESS_PERM_UNPREDICTABLE = 4,/*  UNPREDICTABLE             */
    MPU_PRIV_ACCESS_PERM_READ_ONLY = 5,    /*  Read-only           */
    MPU_PRIV_ACCESS_PERM_READ_ONLY1 = 6,   /*  Read-only           */
    MPU_PRIV_ACCESS_PERM_READ_ONLY2 = 7,   /*  Read-only           */
    MPU_PRIV_ACCESS_PERM_UNDEF=8,          /*       */
} MpuAccessPermissionsPrivileged_t ;


typedef enum {
    /*                                            Unprivileged       */
    MPU_UN_PRIV_ACCESS_PERM_NO_ACCESS = 0,   /*   No access          */
    MPU_UN_PRIV_ACCESS_PERM_NO_ACCESS2 = 1,  /*   No access          */
    MPU_UN_PRIV_ACCESS_PERM_READ_ONLY=2,     /*   Read-only          */
    MPU_UN_PRIV_ACCESS_PERM_FULL_ACCESS=3,   /*   Read/write         */
    MPU_UN_PRIV_ACCESS_PERM_UNPREDICTABLE=4, /*   UNPREDICTABLE       */
    MPU_UN_PRIV_ACCESS_PERM_NO_ACCESS2=5,    /*   No access  */
    MPU_UN_PRIV_ACCESS_PERM_READ_ONLY=6,     /*   Read-only  */
    MPU_UN_PRIV_ACCESS_PERM_READ_ONLY=7,     /*   Read-only  */
    MPU_UN_PRIV_ACCESS_PERM_UNDEF=8,         /*       */
} MpuAccessPermissionsUnPrivileged_t ;
#endif


/* Table B3-15 Access permissions field encoding */
typedef enum{
    /*                                Privileged           Unprivileged       */
    MPU_ACCESS_PERM_NO_ACCESS = 0,   /*  No access            No access          */
    MPU_ACCESS_PERM_FULL_ACCESS = 3, /*  Read/write           Read/write         */
    MPU_ACCESS_PERM_READONLY = 6,    /*  Read-only            Read-only  */
    MPU_ACCESS_PERM_READONLY2 = 7,   /*  Read-only            Read-only  */
    MPU_ACCESS_PERM_UNDEF=8,         /*       */
} MpuAccessPermissions_t ;


#ifdef __cplusplus
}
#endif

#endif /* CORTEX_MPU_MCAL_CONST_H*/
