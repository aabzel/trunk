#include "systick_diag.h"

#include "common_diag.h"
#include "diag_inc.h"
#include "systick_const.h"
#include "systick_mcal.h"
#include "time_mcal.h"

const char* SysTickClockSourceToStr(const SysTickClkSrc_t code) {
    char* name = "?";
    switch(code) {
    case SYSTICK_CLK_SRC_EXT:
        name = "External";
        break;
    case SYSTICK_CLK_SRC_PROC:
        name = "Processor";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

bool systick_diag(void) {
    bool res = true;

    SysTickHandle_t* Node = SysTickGetNode(1);
    if(Node) {

        SysTickClkSrc_t clock_src = systick_source_get();
#ifdef HAS_LOG
        LOG_INFO(LG_SYSTICK, "Enable %s", OnOffToStr(systick_is_run()));
        LOG_INFO(LG_SYSTICK, "ClockSrc:%s", SysTickClockSourceToStr(clock_src));
        LOG_INFO(LG_SYSTICK, "Cnt:%u", systick_cnt_get());
        LOG_INFO(LG_SYSTICK, "Load:%u", systick_get_load());
        LOG_INFO(LG_SYSTICK, "Err %u", Node->err_cnt);

        uint32_t up_time_ms = systick_get_ms();
        uint64_t up_time_us = systick_get_us();
        LOG_INFO(LG_SYSTICK, "up_time_us: %llu us", up_time_us);
        LOG_INFO(LG_SYSTICK, "up_time_ms: %llu ms", up_time_ms);
        LOG_INFO(LG_SYSTICK, "IntCnt32bit: %u ms", Node->up_time_ms32);
        LOG_INFO(LG_SYSTICK, "IntCnt64bit: %llu ms", Node->up_time_ms64);
        LOG_INFO(LG_SYSTICK, "up_time_ms: %f s", MSEC_2_SEC(up_time_ms));
        LOG_INFO(LG_SYSTICK, "up_time_ms: %f m", MSEC_2_MIN(up_time_ms));
#endif
    }
    return res;
}

const char* SysTickConfigToStr(const SysTickConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sClock:%u Hz,", text, Config->bus_clock_hz);
        snprintf(text, sizeof(text), "%sPeriod:%u ms,", text, Config->period_ms);
        snprintf(text, sizeof(text), "%sInt:%s,", text, OnOffToStr(Config->interrupt_on));
        snprintf(text, sizeof(text), "%sPHY:0x%p,", text, Config->SYSTICKx);
    }
    return text;
}
