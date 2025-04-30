#include "systick_general.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "bit_const.h"
#include "log.h"
#ifdef HAS_CLOCK
#include "clock.h"
#endif
#include "nrf_systick.h"
#include "systick_config.h"
#include "systick_general_diag.h"
#include "time_mcal.h"

void SysTickIntHandler(void) { SysTickItem.systick_up_time_ms++; }
#ifdef HAS_SYSTIC_INT
/*if call every 1ms 32bit overflows after 49 days*/
#endif /*HAS_SYSTICK_INT*/

bool systick_general_is_run(void) {
    bool res = false;
    if(SysTickItem.SysTickMapPtr) {
        if(SysTickItem.SysTickMapPtr->Cntl.enable) {
            res = true;
        }
    }
    return res;
}

bool systick_general_stop(void) {
    bool res = false;
    SysTickCntl_t SysTickCntl = {0};
    if(SysTickItem.SysTickMapPtr) {

        LOG_WARNING(LG_SYSTICK, "Stop");
        SysTickCntl.reg_val = SysTickItem.SysTickMapPtr->Cntl.reg_val;
        SysTickCntl.enable = 0;
        SysTickCntl.tickint = 0;

        SysTickItem.SysTickMapPtr->Cntl.reg_val = SysTickCntl.reg_val;
        res = true;
    }

    return res;
}

bool systick_disable(void) {
    bool res = false;
    res = systick_general_stop();
    return res;
}

bool systick_general_start(void) {
    SysTickCntl_t SysTickCntl;
    LOG_WARNING(LG_SYSTICK, "Start");
    SysTickCntl.reg_val = SysTickItem.SysTickMapPtr->Cntl.reg_val;
    SysTickCntl.enable = 1;
    SysTickCntl.tickint = 1;
    SysTickItem.SysTickMapPtr->Cntl.reg_val = SysTickCntl.reg_val;
    return false;
}

bool systick_general_set_load(uint32_t new_load) {
    bool res = false;
    if(new_load < SYSTICK_MAX_VAL) {
        SysTickReload_t SysTickReload;
        SysTickReload.reg_val = 0;
        SysTickReload.reload = MASK_24BIT & new_load;
        SysTickItem.SysTickMapPtr->Load.reg_val = SysTickReload.reg_val;
        res = true;
#ifdef HAS_LOG
        LOG_DEBUG(LG_SYSTICK, "SetLoad %u %x Ok", new_load, new_load);
#endif
    } else {
#ifdef HAS_LOG
        LOG_ERROR(LG_SYSTICK, "TooBigLoad %u %x", new_load, new_load);
#endif
    }
    return res;
}

uint32_t systick_general_get_load(void) {
    SysTickReload_t SysTickReload;
    SysTickReload.reg_val = SysTickItem.SysTickMapPtr->Load.reg_val;

    return SysTickReload.reload;
}

uint64_t systick_get_us(void) {
    /*Sys tick counts down (Wrap to zero counter)*/
    static uint64_t cur_time_us = 0;
    uint64_t up_time_ms = 0;
    uint32_t usec = 0;

    static uint64_t prev_time_us = 0;
    up_time_ms = SysTickItem.systick_up_time_ms;
#if SYSTICK_US_ACCURACY
#error rrrsdd
    uint32_t up_cnt;
    up_cnt = (SysTickItem.SysTickMapPtr->Load.reload) - (SysTickItem.SysTickMapPtr->Val.current);
    usec = up_cnt / CLOCK_FOR_US;
#endif
    prev_time_us = cur_time_us;
    cur_time_us = ((((uint64_t)up_time_ms) * ((uint64_t)1000UL)) + ((uint64_t)usec));
    if(cur_time_us < prev_time_us) { /*Error*/
        SysTickItem.err_cnt++;
    }
    return cur_time_us;
}

double systick_general_get_period(uint32_t systick_clock_hz) {
    double period_s = 0.0;
    double tick_s = 1.0 / ((double)systick_clock_hz);
    uint32_t load = systick_general_get_load();
    period_s = tick_s * ((double)load);
    return period_s;
}

bool systick_general_set_period_s(uint32_t systick_clock_hz, double period_s) {
    bool res = false;
    uint32_t load = 0;
#ifdef HAS_LOG
    LOG_INFO(LG_SYSTICK, "Clock: %u Hz", systick_clock_hz);
#endif
    double tick_s = 1.0 / ((double)systick_clock_hz);
#ifdef HAS_LOG
    LOG_INFO(LG_SYSTICK, "Tick:%f", tick_s);
#endif
    load = (uint32_t)(period_s / tick_s);
#ifdef HAS_LOG
    LOG_INFO(LG_SYSTICK, "load:%u", load);
#endif
    res = systick_general_set_load(load);
    return res;
}

uint32_t systick_general_get_ms(void) {
    uint64_t up_time_ms = 0;
    up_time_ms = SysTickItem.systick_up_time_ms;
    bool res = systick_general_is_run();
    if(false == res) {
        SysTickItem.err_cnt++;
    }
    return up_time_ms;
}

uint64_t systick_general_get_us(void) {
    uint64_t up_time_us = 0;
    up_time_us = MSEC_2_USEC(SysTickItem.systick_up_time_ms);
    bool res = systick_general_is_run();
    if(false == res) {
        SysTickItem.err_cnt++;
    }
    return up_time_us;
}

bool systick_general_set_clksrc(ClkSrc_t clksrc) {
    bool res = false;
    if(SysTickItem.SysTickMapPtr) {
        SysTickItem.SysTickMapPtr->Cntl.clksourse = clksrc;
        res = true;
    }
    return res;
}

bool systick_general_init(uint32_t base_addr, uint32_t clk) {
    bool res = true;
#ifdef HAS_LOG
    LOG_INFO(LG_SYSTICK, "clk %u Hz", clk);
#endif
    SysTickItem.systick_up_time_ms = 0;
    SysTickItem.SysTickMapPtr = (SysTickMap_t*)base_addr;

    SysTickItem.SysTickMapPtr->Load.reload = 0x00FFFFFF;
    SysTickItem.SysTickMapPtr->Val.current = 0;

    SysTickCntl_t SysTickCntlNew;
    SysTickCntlNew.reg_val = 0;
    SysTickCntlNew.enable = 1;
    SysTickCntlNew.clksourse = SysTickConfig.clksourse;
    SysTickCntlNew.tickint = 0;
#ifdef HAS_SYSTICK_DIAG
    LOG_INFO(LG_SYSTICK, "clksourse %u %s", SysTickConfig.clksourse, SysTickClockSource2Str(SysTickConfig.clksourse));
#endif

#ifdef HAS_SYSTICK_INT
    LOG_INFO(LG_SYSTICK, "IntEnable");
    SysTickCntlNew.tickint = 1;
#endif /*HAS_SYSTICK_INT*/

    res = systick_general_set_period_s(clk, MSEC_2_SEC(SysTickConfig.period_ms));
    SysTickItem.SysTickMapPtr->Cntl.reg_val = SysTickCntlNew.reg_val;

    return res;
}

bool systick_set_load(uint32_t load) {
    bool res = false;
    res = systick_general_set_load(load);
    return res;
}
