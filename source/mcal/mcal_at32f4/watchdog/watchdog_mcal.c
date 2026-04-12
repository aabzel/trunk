#include "watchdog_mcal.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "bit_const.h"
#include "clock.h"
#include "data_utils.h"
#include "log.h"
#include "microcontroller_const.h"
#include "time_mcal.h"
#include "utils_math.h"
#include "watchdog_custom_types.h"
#ifdef HAS_FLOAT_UTILS
#include "float_utils.h"
#endif
#ifdef HAS_PARAM
#include "param_drv.h"
#endif

static const WdtDivisionInfo_t WdtDivisionInfo[] = {
    {
        .code = WDT_CLK_DIV_4,
        .divider = 4,
    },
    {
        .code = WDT_CLK_DIV_8,
        .divider = 6,
    },
    {
        .code = WDT_CLK_DIV_16,
        .divider = 16,
    },
    {
        .code = WDT_CLK_DIV_32,
        .divider = 32,
    },
    {
        .code = WDT_CLK_DIV_64,
        .divider = 64,
    },
    {
        .code = WDT_CLK_DIV_128,
        .divider = 128,
    },
    {
        .code = WDT_CLK_DIV_256,
        .divider = 256,
    },
};

static uint16_t PrescalerCode2Num(wdt_division_type code) {
    uint32_t divider = 0;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(WdtDivisionInfo);
    for(i = 0; i < cnt; i++) {
        if(WdtDivisionInfo[i].code == code) {
            divider = WdtDivisionInfo[i].divider;
            break;
        }
    }

    return divider;
}

static wdt_division_type PrescalerToCode(uint32_t divider) {
    wdt_division_type code = WDT_CLK_DIV_256;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(WdtDivisionInfo);
    for(i = 0; i < cnt; i++) {
        if(WdtDivisionInfo[i].divider == divider) {
            code = WdtDivisionInfo[i].code;
            break;
        }
    }

    return code;
}
#if 0
static bool watchdog_find_timing(uint32_t timeout_ms, uint32_t* out_prescaler, uint32_t* out_reload) {
    bool res = false;
    if(out_prescaler && out_reload) {
        uint32_t prescaler = 1;
        uint32_t reload = 0;
        uint32_t reload_val_max = int_pow(2, WatchDogInstance.bitness);
        double tick_time = 0.0;
        double cur_period_s = 0.0;
        double des_period_s = ((double)timeout_ms) / 1000.0;
        for(prescaler = 4; prescaler <= 256; prescaler *= 2) {
            for(reload = 1; reload <= reload_val_max - 2; reload++) {
                tick_time = ((double)prescaler) / ((double)LSI_FREQ);
                cur_period_s = tick_time * ((double)reload);
                res = is_double_equal_absolute(cur_period_s, des_period_s, 0.00001);
                if(res) {
                    LOG_DEBUG(WATCHDOG, "Spot Psc %u Reload %u", prescaler, reload);
                    *out_reload = reload;
                    *out_prescaler = prescaler;
                    return res;
                }
            }
        }
    }
    if(false == res) {
        LOG_ERROR(WATCHDOG, "UnrealisticPeriod %u", timeout_ms);
    }
    return res;
}
#endif

double watchdog_calc_period_s(uint16_t clock_hz, uint16_t prescaler, uint16_t reload) {
    double period_s = 0.0;
    double tick_time = ((double)prescaler) / clock_hz;
    period_s = tick_time * ((double)reload);
    return period_s;
}

bool watchdog_timeout_get(uint32_t* const timeout_ms) {
    bool res = false;
    LOG_INFO(WATCHDOG, "WDT_BASE:0x%x", WDT_BASE);
    WdtRegMap_t* RegMap = (WdtRegMap_t*)WDT_BASE;
    if(RegMap) {
        uint16_t prescaler = PrescalerCode2Num((wdt_division_type)RegMap->Div.div);
        LOG_INFO(WATCHDOG, "div:%u", prescaler);
        uint16_t reload = RegMap->Rld.rldf;
        LOG_INFO(WATCHDOG, "reload:%u", reload);
        double period_s = clock_calc_period_s(WatchDogInstance.base_freq_hz, prescaler, reload);
        *timeout_ms = SEC_2_MSEC(period_s);
        res = true;
    }

    return res;
}

static bool wdt_clock_calc_prescaler(uint32_t base_freq_hz, uint32_t max_val, uint32_t timeout_ms,
                                     ClockSetting_t* const Node) {
    LOG_INFO(CLK, "Clock:%uHz,Max:%u,Period:%u s", base_freq_hz, max_val, timeout_ms);
    bool res = false;
    double timeout_s = MSEC_2_SEC(timeout_ms);
    double bus_tick_s = 1.0 / ((double)base_freq_hz);
    LOG_INFO(CLK, "bus_tick:%f s", bus_tick_s);
    double tick_s = bus_tick_s;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(WdtDivisionInfo);
    for(i = 0; i < cnt; i++) {
        tick_s = bus_tick_s * ((double)WdtDivisionInfo[i].divider);
        double period_max_s = tick_s * ((double)max_val);
        LOG_DEBUG(CLK, "Div:%u,Max:%f s", WdtDivisionInfo[i].divider, period_max_s);
        if(timeout_s < period_max_s) {
            Node->divider = WdtDivisionInfo[i].divider;
            Node->period = (uint32_t)timeout_s / tick_s;
            res = true;
            break;
        }
    }
#ifdef HAS_CLOCK_DIAG
    LOG_INFO(SYS, "%s", ClockSettingToStr(Node));
#endif
    return res;
}

bool watchdog_timeout_set(uint32_t timeout_ms) {
    bool res = false;
    LOG_INFO(WATCHDOG, "SetTimeOut:%u ms", timeout_ms);
    ClockSetting_t WatchDogSetting;
    uint32_t reload_val_max = int_pow(2, WatchDogInstance.bitness);
    res =
        clock_calc_prescaler(WatchDogConfig.base_freq_hz, reload_val_max, WatchDogConfig.timeout_ms, &WatchDogSetting);
#ifdef HAS_CLOCK_DIAG
    LOG_INFO(SYS, "Best:%s", ClockSettingToStr(&WatchDogSetting));
#endif

    WatchDogSetting.divider = 256;
    WatchDogSetting.period = reload_val_max - 1;
    res = wdt_clock_calc_prescaler(WatchDogConfig.base_freq_hz, reload_val_max, WatchDogConfig.timeout_ms,
                                   &WatchDogSetting);
#ifdef HAS_CLOCK_DIAG
    LOG_INFO(SYS, "Real:%s", ClockSettingToStr(&WatchDogSetting));
#endif
    wdt_register_write_enable(TRUE);

    wdt_division_type code = PrescalerToCode(WatchDogSetting.divider);
    wdt_divider_set(code);

    wdt_reload_value_set(WatchDogSetting.period - 1);
    wdt_counter_reload();
    return res;
}

bool watchdog_proc(void) {
    bool res = true;
    LOG_PARN(WATCHDOG, "Proc");
    if(WatchDogInstance.on) {
        LOG_DEBUG(WATCHDOG, "Refresh");
        wdt_counter_reload();
    } else {
        LOG_DEBUG(WATCHDOG, "Skip");
    }
    return res;
}

bool watchdog_ctrl(bool on_off) {
    bool res = false;
    if(on_off) {
        wdt_counter_reload();
        wdt_enable();
        LOG_WARNING(WATCHDOG, "Start");
        res = true;
    } else {
        LOG_ERROR(WATCHDOG, "StopNotAllowed");
        res = false;
    }
    return res;
}

bool watchdog_mcal_init(void) {
    bool res = false;
#ifdef HAS_WATCHDOG_DIAG
    LOG_WARNING(WATCHDOG, "Init:%s", WatchDogConfigToStr(&WatchDogConfig));
#endif /*HAS_WATCHDOG_DIAG*/
    WatchDogInstance.valid = WatchDogConfig.valid;
    WatchDogInstance.on = WatchDogConfig.on;
    WatchDogInstance.base_address = WatchDogConfig.base_address;
    WatchDogInstance.bitness = WatchDogConfig.bitness;
    WatchDogInstance.base_freq_hz = WatchDogConfig.base_freq_hz;
    WatchDogInstance.timeout_ms = WatchDogConfig.timeout_ms;

#ifdef HAS_PARAM
    bool out_res = true;
    (void)out_res;
#ifdef HAS_BOOTLOADER
    LOAD_PARAM(WATCHDOG, PAR_ID_WATCHDOG_BOOTLOADER_ON, WatchDogInstance.on, false);
#endif /*HAS_BOOTLOADER*/

#ifdef HAS_GENERIC
    LOAD_PARAM(WATCHDOG, PAR_ID_WATCHDOG_GENERIC_ON, WatchDogInstance.on, true);
#endif /*HAS_GENERIC*/

    LOAD_PARAM(WATCHDOG, PAR_ID_WATCHDOG_TIME_OUT_MS, WatchDogInstance.timeout_ms, WatchDogConfig.timeout_ms);
#endif /*HAS_PARAM*/

    if(WatchDogInstance.on) {
        res = watchdog_timeout_set(WatchDogInstance.timeout_ms);
        res = watchdog_ctrl(WatchDogInstance.on);
        res = watchdog_proc();
    } else {
        LOG_WARNING(WATCHDOG, "Off");
        res = true;
    }

    res = watchdog_timeout_get(&WatchDogInstance.timeout_ms);
    return res;
}
