#ifndef MULTICORE_CUSTOM_TYPE_H
#define MULTICORE_CUSTOM_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "multicore_custom_const.h"

#define MULTICORE_CUSTOM_VARIABLES

typedef struct {
    bool valid;
    uint8_t num;
}MultiCoreInfo_t;


/* see RGM_C1_RST field descriptions
       RGM_C2_RST (CPU2 Reset Register)
   CPU1 software reset control and status register.
 */
typedef union {
	volatile uint32_t dword;
    struct {
    	volatile uint32_t Cx_SWRST:1;  /* bit:0; WO CPU1 SW Reset Control
                                          Writing 1 to this field will issue a CPU1 reset.*/
        volatile uint32_t Cx_OUT_OF_RST:1;   /* bit:1; RO  CPU1 Out of Reset Flag*/
        volatile uint32_t RES:30;            /* bit:32-2; */
    }__attribute__((__packed__));
}__attribute__((__packed__))CPUxResetRegister_t;


/*  40h SCM_CORE_HOLD (Core Hold Register) 32 RW 0006_0006h page
    SCM_CORE_HOLD field descriptions
    */
typedef union {
    uint32_t dword;
    struct {
        volatile uint32_t RES1:1;              /* bit:0 */
        volatile uint32_t CPU1_CORE_HOLD:1;    /* bit:1 RW */
        volatile uint32_t CPU2_CORE_HOLD:1;    /* bit:2 RW */
        volatile uint32_t RES2:25;             /* bit:27-3 */
        volatile uint32_t WPB:3;               /* bit:30-28 RW  Write Permission*/
        volatile uint32_t WPB_LOCK:1;          /* bit:31 RW  Write Permission Lock*/
    }__attribute__((__packed__));
}__attribute__((__packed__))CORE_HOLD_t;


/*
  CPU Initial Vector
      SCM_CPU2VTOR (CPU2 Vector Table Register)
  34h SCM_CPU1VTOR (CPU1 Vector Table Register) 32 RW 0240_0200h page
  24.6.12 SCM_CPU1VTOR (CPU1 Vector Table Register)
 */
typedef union {
	volatile uint32_t dword;
    struct{
        volatile uint32_t CPUx_INIT_VECTOR:28;     /* bit:27:0   RW The CM7 initial vector */
        volatile uint32_t WPB:3;                   /* bit:30-28; RW Write Permission     */
        volatile uint32_t WPB_LOCK:1;              /* bit:31;    RW Write Permission Lock   */
    }__attribute__((__packed__));
}__attribute__((__packed__))CPUxVTOR_t;



/*
CPU1 Release Register, offset: 0x20C
20Ch RGM_C1_RLS (CPU1 Release Register) 32 RW 0000_0000h page
 */
typedef union {
	volatile uint32_t dword;
    struct{
    	volatile uint32_t Cx_RELEASE:1; /* bit:0;   RW     CPU1 Release Register
                                           Writing 1 to release CPU1. After writing, this bit will be locked until the next system reset or CPU1 reset */
        volatile uint32_t RES:31;                   /* bit:31-1;   RW                         */

    }__attribute__((__packed__));
}__attribute__((__packed__))Cx_RLS_t;


#ifdef __cplusplus
}
#endif

#endif /* MULTICORE_CUSTOM_TYPE_H */
