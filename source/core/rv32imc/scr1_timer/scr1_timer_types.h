#ifndef SCR1_TIMER_TYPES_H
#define SCR1_TIMER_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "clock_const.h"
#include "scr1_timer_const.h"

//https://mik32-amur.ru/Appendix/systim64.html

typedef union {
    uint32_t dword;
    struct {
        uint32_t ENABLE :1; //
        uint32_t CLKSRC :1; //
        uint32_t RES :30; //
    };
} Scr1TimerRegCTRL_t;

typedef union {
    uint32_t dword;
    struct {
        uint32_t DIV :10; //
        uint32_t RES :22; //
    };
} __attribute__ ((packed)) Scr1TimerRegDIV_t;

typedef union {
    uint32_t dword;
    struct {
        uint32_t MTIME;
    };
} Scr1TimerRegMTIME_t;

typedef union {
    uint32_t dword;
    struct {
        uint32_t MTIMEH;
    };
} Scr1TimerRegMTIMEH_t;

typedef union {
    uint32_t dword;
    struct {
        uint32_t MTIMECMP;
    };
} Scr1TimerRegMTIMECMP_t;

typedef union {
    uint32_t dword;
    struct {
        uint32_t MTIMECMPH;
    };
} Scr1TimerRegMTIMECMPH_t;

typedef struct {
    volatile Scr1TimerRegCTRL_t CTRL;//0
    volatile Scr1TimerRegDIV_t DIV;//4
    volatile Scr1TimerRegMTIME_t MTIME;//8
    volatile Scr1TimerRegMTIMEH_t MTIMEH; //12
    volatile Scr1TimerRegMTIMECMP_t MTIMECMP;//16
    volatile Scr1TimerRegMTIMECMPH_t MTIMECMPH;//20
} Scr1TimerRegs_t;

typedef struct {
    Scr1TimerRegs_t *Scr1TimerRegMapPtr;
    uint64_t int_cnt;
    uint32_t err_cnt;
    float up_time_s;
    bool valid;
    volatile uint64_t scr1_timer_up_time_us;
} Scr1Timer_t;

typedef struct {
    uint32_t base_addr;
    float tick_s;
    ClockSource_t clock_source;
    bool valid;
} Scr1TimerConfig_t;

#ifdef __cplusplus
}
#endif

#endif /* SCR1_TIMER_TYPES_H */
