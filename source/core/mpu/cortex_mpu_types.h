#ifndef CORTEX_MPU_MCAL_TYPES_H
#define CORTEX_MPU_MCAL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "cortex_mpu_const.h"
/*
 The MPU registers support aligned word accesses only. Byte and halfword accesses are unpredictable.
 */

/*B3.5.5 MPU Type Register, MPU_TYPE*/
typedef union{
    uint32_t dword;
    struct {
        uint32_t SEPARATE:1;   /* bit[0]  SEPARATE,   */
        uint32_t RES1:7;       /* bits[7:1] Reserved   */
        uint32_t DREGION:8;    /* bits[15:8] Number of regions supported by the MPU.             */
        uint32_t IREGION:8;    /* bits[23:16] Instruction region. RAZ. Armv7-M only supports a unified MPU   */
        uint32_t RES2:8;       /* bits[31:24]  Reserved  */
    };
}MpuRegType_t;

/*B3.5.6 MPU Control Register, MPU_CTRL*/
typedef union {
    uint32_t dword;
    struct{
        uint32_t ENABLE:1;   /* bit[0]  Enables the MPU: */
        uint32_t HFNMIENA:1;   /*Bits[1] When the ENABLE bit is set to 1, controls whether handlers executing with priority less
than 0 access memory with the MPU enabled or with the MPU disabled.  */
        uint32_t PRIVDEFENA:1;   /* DREGION, bits[15:8]           */
        uint32_t RES:29;   /* Bits[31:3] Reserved.  */
    };
}MpuRegCtrl_t;


/*B3.5.7 MPU Region Number Register, MPU_RNR*/
typedef union {
    uint32_t dword;
    struct{
        uint32_t REGION:8;   /* bits[7:0] Indicates the memory region accessed by MPU_RBAR and MPU_RASR. */
        uint32_t RES:24;   /* Bits[31:8] Reserved. */
    };
}MpuRegRnr_t;


/*B3.5.8 MPU Region Base Address Register, MPU_RBAR*/
typedef union {
    uint32_t dword;
    struct{
        uint32_t REGION:4; /* bits[3:0] On writes, can specify the number of the region to update */
        uint32_t VALID:1;  /* bit[4] On writes, indicates whether the region to update is specified by */
        uint32_t ADDR:27;  /* bits[31:5] Base address of the region */
    };
}MpuRegRbar_t;

/*B3.5.9 MPU Region Attribute and Size Register, MPU_RASR*/
typedef union {
    uint32_t dword;
    struct{
        uint32_t ENABLE:1; /* bit[0] Enables this region */
        uint32_t SIZE:5; /*  bits[5:1] Indicates the region size */
        uint32_t RES1:2; /*Bits[7:6] Reserved. */
        uint32_t SRD:8; /* bits[15:8] Subregion Disable. */
        uint32_t B:1; /* bits[16]  _____ */
        uint32_t C:1; /* bits[17]  _____ */
        uint32_t S:1; /* bits[18]  _____ */
        uint32_t TEX:3; /* bits[21 19]  _____ */
        uint32_t RES2:2; /* bits[23:22]  Reserved */
        uint32_t AP:3; /* bits[26 24]   access permissions */
        uint32_t RES3:1; /* bits[27]  Reserved */
        uint32_t XP:1; /* bits[28]   Execution of an instruction fetched from this region permission*/
        uint32_t RES4:3; /* bits[31:29]  Reserved */
    };
}MpuRegRasr_t;


/*B3.5.9 MPU Region Attribute and Size Register, MPU_RASR*/
typedef union {
    uint32_t dword[11];
    struct{
        MpuRegType_t  MPU_TYPE;
        MpuRegCtrl_t  MPU_CTRL;
        MpuRegRnr_t  MPU_RNR;
        MpuRegRbar_t  MPU_RBAR;
        MpuRegRasr_t  MPU_RASR;
        uint32_t  MPU_RBAR_A1;
        uint32_t  MPU_RASR_A1;
        uint32_t  MPU_RBAR_A2;
        uint32_t  MPU_RASR_A2;
        uint32_t  MPU_RBAR_A3;
        uint32_t  MPU_RASR_A3;
    };
}MpuRegMap_t;


#ifdef __cplusplus
}
#endif

#endif /* CORTEX_MPU_MCAL_TYPES_H */
