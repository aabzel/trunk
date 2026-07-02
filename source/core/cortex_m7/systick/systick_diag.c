#include "systick_diag.h"


#include "systick_mcal.h"
#include "time_mcal.h"
#include "systick_const.h"
#include "common_diag.h"
#ifdef HAS_LOG
#include "log.h"
#endif

const  char* SysTickClockSourceToStr(const SysTickClkSrc_t code){
    char* name="?";
    switch(code) {
        case SYSTICK_CLK_SRC_EXT :name="External"; break;
        case SYSTICK_CLK_SRC_PROC :name="Processor"; break;
        default:name="?"; break;
    }
    return name;
}

bool systick_diag(void) {
    bool res = true;
    SysTickClkSrc_t clock_src = systick_source_get();
#ifdef HAS_LOG
    LOG_INFO(LG_SYSTICK, "Enable %s", OnOffToStr(systick_general_is_run()));
    LOG_INFO(LG_SYSTICK, "ClockSrc:%s", SysTickClockSourceToStr(clock_src));
    LOG_INFO(LG_SYSTICK, "Cnt:%u", systick_cnt_get());
    LOG_INFO(LG_SYSTICK, "Load:%u", systick_general_get_load());
    LOG_INFO(LG_SYSTICK, "Err %u", SysTickInstance.err_cnt);

    uint32_t up_time_ms = systick_general_get_ms();
    uint64_t up_time_us = systick_general_get_us();
    LOG_INFO(LG_SYSTICK, "up_time_us %llu us", up_time_us);
    LOG_INFO(LG_SYSTICK, "up_time_ms %llu ms", up_time_ms);
    LOG_INFO(LG_SYSTICK, "IntCnt %llu ms", SysTickInstance.up_time_ms);
    LOG_INFO(LG_SYSTICK, "up_time_ms %f s", MSEC_2_SEC(up_time_ms));
    LOG_INFO(LG_SYSTICK, "up_time_ms %f m", MSEC_2_MIN(up_time_ms));
#endif
    return res;
}
