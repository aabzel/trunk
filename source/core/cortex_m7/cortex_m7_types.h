#ifndef CORE_TYPES_H
#define CORE_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "cortex_m7_const.h"

typedef struct {
   uint32_t r0;
   uint32_t r1;
   uint32_t r2;
   uint32_t r3;
   uint32_t r12;
   uint32_t lr;
   uint32_t pc;
   uint32_t psr;
}RegContext_t ;

typedef union {
    uint32_t val;
    struct {
        uint32_t  npriv :1; /*Thread mode privilege level. Defines the Thread mode privilege level.*/
        uint32_t  spsel :1;/*Active stack pointer selection. Selects the current stack:*/
        uint32_t  fpca :1; /*Indicates whether floating-point context currently active:*/
        uint32_t  res: 29; /*Reserved*/
    };
}RegCtrl_t;

typedef union {
    uint32_t val;
    struct{
        uint32_t  primask :1;
        uint32_t  res: 30; /*Reserved*/
    };
}RegPrimask_t;

typedef union {
    uint32_t val;
    struct{
        uint32_t  faultmask :1;
        uint32_t  res: 30; /*Reserved*/
    };
}RegFaultmask_t;


typedef union {
    uint32_t val;
    struct{
        uint32_t  res1: 4; /*Reserved*/
        uint32_t  basepri :4; /*defines the base priority for exception processing.
        The processor does not process any exception with a priority value greater than or
                   equal to basepri.*/
        uint32_t  res2: 24; /*Reserved*/
    };
}RegBasePri_t;

#ifdef __cplusplus
}
#endif

#endif /* CORE_TYPES_H */
