#ifndef SYSTICK_GENERAL_TYPES_H
#define SYSTICK_GENERAL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#include "systick_const.h"

typedef union {
    uint32_t reg_val;
    struct{
        uint32_t enable:1;
        uint32_t tickint:1;
        uint32_t clksourse: 1;
        uint32_t res1:13;
        uint32_t countflag:1;
        uint32_t res2:15;
    };
}SysTickCntl_t;

typedef union {
    uint32_t reg_val;
    struct{
        uint32_t reload:24;
        uint8_t res;
    };
}SysTickReload_t;

typedef union {
    uint32_t reg_val;
    struct{
        uint32_t current:24;
        uint8_t res;
    };
}SysTickValue_t;

typedef union {
    uint32_t reg_val;
    struct{
        uint32_t tenms:24;
        uint32_t res:6;
        uint32_t skew:1;
        uint32_t no_ref:1;
    };
}SysTickCalibValue_t;

typedef struct {
  volatile SysTickCntl_t Cntl;          /* Offset: 0x000 (R/W)  SysTick Control and Status Register */
  volatile SysTickReload_t Load;        /* Offset: 0x004 (R/W)  SysTick Reload Value Register */
  volatile SysTickValue_t Val;          /* Offset: 0x008 (R/W)  SysTick Current Value Register */
  volatile SysTickCalibValue_t Calib;   /* Offset: 0x00C (R/ )  SysTick Calibration Register */
} SysTickMap_t;

typedef struct {
    uint32_t err_cnt;
    SysTickMap_t* base_address;
    volatile uint32_t up_time_ms;
    volatile uint32_t int_cnt;
    bool init_done;
}SysTick_t;

typedef struct {
    uint32_t base_address;
    uint32_t period_ms;
  //  uint32_t bus_clock_hz;
    bool int_enable;
}SysTickConfig_t;

#ifdef __cplusplus
}
#endif

#endif /* SYSTICK_GENERAL_TYPES_H */
