#include "power_custom_diag.h"

#include <stdio.h>
#include <string.h>

#include "debugger.h"
#include "log.h"
#include "mcal_types.h"
#include "num_to_str.h"
#include "power_mcal.h"
#include "power_manager.h"
#include "table_utils.h"
#include "writer_config.h"
#include "power_manager_X8632B1Mx.h"
#include "power_custom_diag.h"

const char* PowerFc73ModeToStr(power_mode_stat_t power_mode) {
    char * name = "?";
    switch(power_mode) {
        case STAT_RUN: name="Run"; break;
        case STAT_SLEEP: name="Sleep"; break;
        case STAT_DEEPSLEEP: name="DeepSleep"; break;
        case STAT_STANDBY: name="StandBy"; break;
        default: name="?"; break;
    }
    return name;
}

bool power_diag_low_level(uint8_t num, const char* const keyword) {
    bool res = false;
    const PowerInfo_t* Info = PowerGetInfo(num);
    if(Info) {
    	power_mode_stat_t power_mode = STAT_INVALID;
    	power_manager_user_config_t config={0};
        POWER_SYS_GetDefaultConfig(&config);
    	power_mode = POWER_SYS_GetCurrentMode(&config);
        LOG_INFO(POWER, "%u=%s", power_mode, PowerFc73ModeToStr(power_mode));
    }
    return res;
}

static const Reg32_t PowerReg[] = {
    { .offset = 0x00, .name = "STS", .valid = true,  },
    { .offset = 0x04, .name = "SSTS", .valid = true, },
    { .offset = 0x08, .name = "INTE", .valid = true, },
    { .offset = 0x0C, .name = "CTRL", .valid = true, },
    { .offset = 0x10, .name = "TRIM50", .valid = true, },
    { .offset = 0x14, .name = "TRIM25", .valid = true, },
    { .offset = 0x18, .name = "TRIM11", .valid = true, },
};

static uint32_t power_reg_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(PowerReg);
    return cnt;
}

bool power_raw_reg_diag(uint8_t num) {
    bool res = false;
    const PowerInfo_t* Info = PowerGetInfo(num);
    if(Info) {
        LOG_INFO(POWER, "POWER%u,Base:0x%p", num, Info->POWERx);
        uint32_t reg_cnt = power_reg_cnt();
        res = debug_raw_reg_diag(POWER, (uint32_t) Info->POWERx, PowerReg, reg_cnt);
    }

    return res;
}
