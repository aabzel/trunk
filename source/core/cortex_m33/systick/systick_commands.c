#include "systick_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "convert.h"
#include "clock.h"
#include "clock_utils.h"
#include "common_diag.h"

#include "log.h"

#include "systick_general.h"
#include "time_mcal.h"
#include "timer_utils.h"
#include "sys_config.h"
#include "systick_general_diag.h"
#include "systick_config.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

bool systick_set_load_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t load = 0;
    if(0==argc){
        res = true;
    }
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &load);
        if(false == res) {
            LOG_ERROR(LG_SYSTICK, "ParseErr period %s", argv[0]);
        }
    }

    if( res) {
        if(1<=argc){
            res = systick_general_set_load(load);
        }else{
            load = systick_general_get_load( );
            LOG_INFO(LG_SYSTICK, "load %u 0x%x",load,load);
        }
    }else {
        LOG_ERROR(LG_SYSTICK, "Usage: stkl load");
    }
    return res;
}

bool systick_clksrc_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t clksrc=CLK_SRC_EXT;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &clksrc);
        if(false == res) {
            LOG_ERROR(LG_SYSTICK, "ParseErr clksrc %s", argv[0]);
        }
    }
    if(res){
        res = systick_general_set_clksrc(clksrc);
        if(res){
            LOG_INFO(LG_SYSTICK, "SetClkSrc [%s] Ok",SysTickClockSource2Str(  clksrc));
        }else{
            LOG_ERROR(LG_SYSTICK, "SetClkSrc [%s] Err",SysTickClockSource2Str(  clksrc));
        }
    }else {
        LOG_ERROR(LG_SYSTICK, "Usage stkc ClkSrc");
    }
    return res;
}

bool systick_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0==argc) {
        res = true;
        LOG_INFO(LG_SYSTICK, "XTALL: %u Hz %f MHz",XTALL_FREQ,HZ_2_MHZ(XTALL_FREQ));
        LOG_INFO(LG_SYSTICK, "Base: %p 0x%x",SysTickItem.SysTickMapPtr,SysTickItem.SysTickMapPtr);
        LOG_INFO(LG_SYSTICK, "Enable %s", OnOff2Str(systick_general_is_run()));
        LOG_INFO(LG_SYSTICK, "Err %u", SysTickItem.err_cnt);
        LOG_INFO(LG_SYSTICK, "ClkSrc %u %s", SysTickItem.SysTickMapPtr->Cntl.clksourse, SysTickClockSource2Str(SysTickItem.SysTickMapPtr->Cntl.clksourse));
        uint32_t up_time_ms = systick_general_get_ms();
        double period_s = systick_general_get_period(SYS_FREQ);
        uint32_t load = systick_general_get_load() ;
        LOG_INFO(LG_SYSTICK, "Load %u 0x%x", load, load);
        LOG_INFO(LG_SYSTICK, "Period %f s", period_s);
        LOG_INFO(LG_SYSTICK, "up_time_ms %llu ms", up_time_ms);
        LOG_INFO(LG_SYSTICK, "IntCnt %llu ms", SysTickItem.systick_up_time_ms);
        LOG_INFO(LG_SYSTICK, "up_time_ms %f s", MSEC_2_SEC(up_time_ms));
        LOG_INFO(LG_SYSTICK, "up_time_ms %f m", MSEC_2_MIN(up_time_ms));

    }else {
        LOG_ERROR(LG_SYSTICK, "Usage: stkd");
    }
    return res;
}

bool systick_stop_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = systick_general_stop();
    } else {
        LOG_ERROR(LG_SYSTICK, "Usage: stkp");
    }
    return res;
}

bool systick_start_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = systick_general_start();
    } else {
        LOG_ERROR(LG_SYSTICK, "Usage: stks");
    }
    return res;
}


bool systick_init_command(int32_t argc, char* argv[]){
    bool res = false;
    uint32_t clk = XTALL_FREQ*4;
    if(0== argc) {
        res = true;
    }
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &clk);
        if(false == res) {
                LOG_ERROR(LG_SYSTICK, "ParseErr clk %s", argv[0]);
        }
    }

    if(res){
        res=systick_general_init(SysTick_BASE,clk);
        if(res){
            LOG_INFO(LG_SYSTICK, "InitOk");
        }else{
            LOG_INFO(LG_SYSTICK, "InitErr");
        }

    }else {
        LOG_ERROR(LG_SYSTICK, "Usage: stks");
    }
    return res;
}


bool systick_set_cnt_command(int32_t argc, char* argv[]){
    bool res = false;
    uint64_t up_time_ms=0;
    if(1<=argc){
        res = try_str2uint64(argv[0], &up_time_ms);
    }
    if(res){
    	LOG_INFO(LG_SYSTICK, "SetUpTime Prev %f New %f s",
    			USEC_2_SEC(SysTickItem.systick_up_time_ms),
			    USEC_2_SEC(up_time_ms));
    	SysTickItem.systick_up_time_ms = up_time_ms;
    }
    return res;
}
