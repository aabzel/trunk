#ifndef CORE_TYPES_H
#define CORE_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rv32imc_const.h"

typedef union {
    uint64_t u64;
    uint32_t u32[2];
} Counter64bit_t;

typedef union {
    uint32_t dword;
    struct {
        uint32_t  MODE :2; /*Vector mode (0-direct mode, 1-vectored mode) */
        uint32_t  res: 4; /*Read as zero*/
        uint32_t  BASE :26; /*Vector base address (upper 26 bits) */
    };
}__attribute__((__packed__)) Scr1RegMTVEC_t;



typedef union {
    uint32_t dword;
    struct {
        uint32_t  RSV1 :3; /*Reserved */
        uint32_t  MIE :1; /*Global interrupt enable */
        uint32_t  RSV2: 3; /*Reserved */
        uint32_t  MPIE :1; /* Previous global interrupt enable */
        uint32_t  RSV3 :3; /*Reserved  */
        uint32_t  MPP :2; /* Previous privilege mode (hardwired to 11) */
        uint32_t  RSV4 :19; /* Reserved */
    };
}__attribute__((__packed__)) Scr1RegMSTATUS_t;


typedef union {
    uint32_t dword;
    struct {
        uint32_t  RSV1 :3; /*Reserved */
        uint32_t  MSIE :1; /* Machine Software Interrupt Enable */
        uint32_t  RSV2: 3; /*Reserved */
        uint32_t  MTIE :1; /* Machine Timer Interrupt Enable.*/
        uint32_t  RSV3 :3; /*Reserved  */
        uint32_t  MEIE :1; /* Machine External Interrupt Enable.*/
        uint32_t  RSV4 :20; /* Reserved */
    };
}__attribute__((__packed__)) Scr1RegMIE_t;



#ifdef __cplusplus
}
#endif

#endif /* CORE_TYPES_H */
