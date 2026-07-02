#include "systick_mcal.h"

#include <stdlib.h>

#include "bit_const.h"
#include "clock.h"
#include "clock_utils.h"
#include "std_includes.h"
#include "time_mcal.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_STM32
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"
#endif

void SysTickIntHandler(void) { SysTickInstance.up_time_ms++; }

#ifdef HAS_SYSTIC_INT
/*if call every 1ms 32bit overflows after 49 days*/
#endif /*HAS_SYSTICK_INT*/

static bool systick_general_init_one(const SysTickConfig_t* const Config, SysTickHandle_t* const Node) {
    bool res = false;
    if(Config) {
#ifdef HAS_LOG
        LOG_INFO(LG_SYSTICK, "Period:%u ms", Config->period_ms);
#endif
        Node->up_time_ms = 0;
        if(Config->SYSTICKx) {
            if(0 < Config->bus_clock_hz) {
                Node->SYSTICKx = (SysTickMap_t*)Config->SYSTICKx;

                Node->SYSTICKx->Load.reload = SEC_TO_TIMER_PERIOD(MSEC_2_SEC(Config->period_ms), Config->bus_clock_hz);
#ifdef HAS_LOG
                LOG_INFO(LG_SYSTICK, "Reload:%u", Node->SYSTICKx->Load.reload);
#endif
                Node->SYSTICKx->Val.current = 0;

                SysTickCntl_t SysTickCntlNew;
                SysTickCntlNew.reg_val = 0;
                SysTickCntlNew.enable = 1;
                SysTickCntlNew.tickint = 0;

                if(Config->interrupt_on) {
                    SysTickCntlNew.tickint = 1;
                }

                Node->SYSTICKx->Cntl.reg_val = SysTickCntlNew.reg_val;
                res = true;
            }
        }
    }
    return res;
}

bool systick_mcal_init(void) {
    bool res = true;
    res = systick_general_init_one(&SysTickConfig, &SysTickInstance);
    res = systick_custom_init();
    return res;
}

bool systick_general_is_run(void) {
    bool res = false;
    if(SysTickInstance.SYSTICKx) {
        if(SysTickInstance.SYSTICKx->Cntl.enable) {
            res = true;
        }
    }
    return res;
}

bool systick_mcal_stop(void) {
    SysTickCntl_t SysTickCntl;
    SysTickCntl.reg_val = SysTickInstance.SYSTICKx->Cntl.reg_val;
    SysTickCntl.enable = 0;
    SysTickCntl.tickint = 0;

    SysTickInstance.SYSTICKx->Cntl.reg_val = SysTickCntl.reg_val;

    return true;
}

bool systick_general_start(void) {
    SysTickCntl_t SysTickCntl;
    SysTickCntl.reg_val = SysTickInstance.SYSTICKx->Cntl.reg_val;
    SysTickCntl.enable = 1;
    SysTickCntl.tickint = 1;
    SysTickInstance.SYSTICKx->Cntl.reg_val = SysTickCntl.reg_val;
    return true;
}

bool systick_general_set_load(uint32_t new_load) {
    SysTickReload_t SysTickReload;
    SysTickReload.reg_val = 0;
    SysTickReload.reload = MASK_24BIT & new_load;
    SysTickInstance.SYSTICKx->Load.reg_val = SysTickReload.reg_val;
    return true;
}

SysTickClkSrc_t systick_source_get(void) {
    SysTickClkSrc_t clk_src = SYSTICK_CLK_SRC_UNDEF;
    if(SysTickInstance.SYSTICKx) {
        clk_src = SysTickInstance.SYSTICKx->Cntl.clksourse;
    }
    return clk_src;
}

uint32_t systick_general_get_load(void) {
    SysTickReload_t SysTickReload;
    SysTickReload.reg_val = SysTickInstance.SYSTICKx->Load.reg_val;
    return SysTickReload.reload;
}

uint64_t systick_general_get_us(void) {
    /*Sys tick counts down (Wrap to zero counter)*/
    static uint64_t cur_time_us = 0;
    uint64_t up_time_ms;

    static uint64_t prev_time_us = 0;
    up_time_ms = SysTickInstance.up_time_ms;
    prev_time_us = cur_time_us;
    cur_time_us = ((uint64_t)up_time_ms) * ((uint64_t)1000UL);
#if 0
    uint32_t up_cnt = 0;
    uint32_t usec;
    up_cnt = (SysTickInstance.SYSTICKx->Load.reload) - (SysTickInstance.SYSTICKx->Val.current);
    usec = up_cnt / CLOCK_FOR_US;
    cur_time_us +=  ((uint64_t)usec));
#endif
    if(cur_time_us < prev_time_us) { /*Error*/
        SysTickInstance.err_cnt++;
    }

    return cur_time_us;
}

uint32_t systick_general_get_ms(void) {
    uint32_t up_time_ms = 0;
    bool res = systick_general_is_run();
    if(res) {
    } else {
        SysTickInstance.err_cnt++;
    }
    up_time_ms = SysTickInstance.up_time_ms;
    return up_time_ms;
}
