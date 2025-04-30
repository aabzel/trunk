#include "systick_mcal.h"

#include <stdlib.h>

#include "bit_const.h"
#include "clock.h"
#include "clock_utils.h"
#include "log.h"
 #include "compiler_const.h"
#include "systick_custom.h"
#include "time_mcal.h"
#ifdef HAS_DIAG
#include "common_diag.h"
#endif


_WEAK_FUN_ bool systick_custom_init(void){
    bool res = false;
    return res;
}

void SysTickIntHandler(void) { SysTickItem.up_time_ms++; }

#ifdef HAS_SYSTIC_INT
/*if call every 1ms 32bit overflows after 49 days*/
#endif /*HAS_SYSTICK_INT*/

static bool systick_general_init_one(const SysTickConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(LG_SYSTICK, "Period: %u ms", Config->period_ms);
        SysTickItem.up_time_ms = 0;
        if(Config->base_address) {

            SysTickItem.base_address = (SysTickMap_t*)Config->base_address;

            uint32_t core_freq_hz = clock_core_freq_get();
            SysTickItem.base_address->Load.reload = SEC_TO_TIMER_PERIOD(MSEC_2_SEC(Config->period_ms), core_freq_hz);
            LOG_INFO(LG_SYSTICK, "Reload: %u", SysTickItem.base_address->Load.reload);
            SysTickItem.base_address->Val.current = 0;

            SysTickCntl_t SysTickCntlNew;
            SysTickCntlNew.reg_val = 0;
            SysTickCntlNew.enable = 1;
            SysTickCntlNew.tickint = 0;

            if(Config->int_enable) {
                SysTickCntlNew.tickint = 1;
            }

            SysTickItem.base_address->Cntl.reg_val = SysTickCntlNew.reg_val;
            res = true;
        }
    }
    return res;
}

bool systick_general_init(void) {
    bool res = true;
    res = systick_general_init_one(&SysTickConfig);
    return res;
}

bool systick_general_is_run(void) {
    bool res = false;
    if(SysTickItem.base_address) {
        if(SysTickItem.base_address->Cntl.enable) {
            res = true;
        }
    }
    return res;
}

bool systick_general_stop(void) {
    SysTickCntl_t SysTickCntl;
    SysTickCntl.reg_val = SysTickItem.base_address->Cntl.reg_val;
    SysTickCntl.enable = 0;
    SysTickCntl.tickint = 0;

    SysTickItem.base_address->Cntl.reg_val = SysTickCntl.reg_val;

    return true;
}

bool systick_general_start(void) {
    SysTickCntl_t SysTickCntl;
    SysTickCntl.reg_val = SysTickItem.base_address->Cntl.reg_val;
    SysTickCntl.enable = 1;
    SysTickCntl.tickint = 1;
    SysTickItem.base_address->Cntl.reg_val = SysTickCntl.reg_val;
    return true;
}

bool systick_general_set_load(uint32_t new_load) {
    SysTickReload_t SysTickReload;
    SysTickReload.reg_val = 0;
    SysTickReload.reload = MASK_24BIT & new_load;
    SysTickItem.base_address->Load.reg_val = SysTickReload.reg_val;
    return true;
}

uint32_t systick_general_get_load(void) {
    SysTickReload_t SysTickReload;
    SysTickReload.reg_val = SysTickItem.base_address->Load.reg_val;
    return SysTickReload.reload;
}

uint64_t systick_general_get_us(void) {
    /*Sys tick counts down (Wrap to zero counter)*/
    static uint64_t cur_time_us = 0;
    uint64_t up_time_ms;

    static uint64_t prev_time_us = 0;
    up_time_ms = SysTickItem.up_time_ms;
    prev_time_us = cur_time_us;
    cur_time_us = ((uint64_t)up_time_ms) * ((uint64_t)1000UL);
#if 0
    uint32_t up_cnt=0;
    uint32_t usec;
    up_cnt = (SysTickItem.base_address->Load.reload) - (SysTickItem.base_address->Val.current);
    usec = up_cnt / CLOCK_FOR_US;
    cur_time_us +=  ((uint64_t)usec));
#endif
    if(cur_time_us < prev_time_us) { /*Error*/
        SysTickItem.err_cnt++;
    }

    return cur_time_us;
}

uint32_t systick_general_get_ms(void) {
    uint64_t up_time_ms = 0;
    bool res = systick_general_is_run();
    if(res) {
        up_time_ms = SysTickItem.up_time_ms;
    } else {
        SysTickItem.err_cnt++;
    }
    return up_time_ms;
}

bool systick_ctrl(bool on_off) {
    bool res = false;
#ifdef HAS_DIAG
    LOG_INFO(LG_SYSTICK, "Ctrl:%s", OnOffToStr(on_off));
#endif
    switch((uint32_t)on_off) {
    case true:
        res = systick_general_start();
        break;
    case false:
        res = systick_general_stop();
        break;
    default:
        res = false;
        break;
    }
    return res;
}

bool systick_init(void) {
    bool res = true;
    res = systick_general_init();
    res = systick_custom_init();
    return res;
}
