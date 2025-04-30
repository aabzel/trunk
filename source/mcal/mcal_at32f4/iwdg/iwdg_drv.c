#include "iwdg_drv.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "bit_const.h"

#ifdef HAS_FLOAT_UTILS
#include "float_utils.h"
#endif

#include "hal_diag.h"
#include "iwdg_types.h"
#include "log.h"
#ifdef HAS_PARAM
#include "param_drv.h"
#endif
#include "at32f435_437.h"
#include "sys_config.h"

WatchDog_t WatchDog = {
    .is_on = false,
    .period_ms = 0,
    .RegMapPtr = (iWdgRegMap_t*)IWDG_BASE_ADDR,
};

bool iwdg_proc(void) {
    bool res = true;
    if(WatchDog.is_on) {
        LOG_DEBUG(LG_IWDG, "Refresh");
        HAL_IWDG_Refresh(&WatchDog.hiwdg);
    } else {
        LOG_DEBUG(LG_IWDG, "Skip");
    }
    return res;
}

static uint32_t Prescaler2Code(uint32_t prescaler) {
    uint32_t code = 1;
    switch(prescaler) {
    case 4:
        code = 0;
        break;
    case 8:
        code = 1;
        break;
    case 16:
        code = 2;
        break;
    case 32:
        code = 3;
        break;
    case 64:
        code = 4;
        break;
    case 125:
        code = 5;
        break;
    case 256:
        code = 6;
        break;
    default:
        code = 0;
        break;
    }
    return code;
}

bool iwdg_find_timing(uint32_t period_ms, uint32_t* out_prescaler, uint32_t* out_reload) {
    bool res = false;
    if(out_prescaler && out_reload) {
        uint32_t prescaler = 1;
        uint32_t reload = 0;
        double tick_time = 0.0;
        double cur_period_s = 0.0;
        double des_period_s = ((double)period_ms) / 1000.0;
        for(prescaler = 4; prescaler <= 256; prescaler *= 2) {
            for(reload = 1; reload <= RELOAD_VAL_MAX - 2; reload++) {
                tick_time = ((double)prescaler) / ((double)LSI_FREQ);
                cur_period_s = tick_time * ((double)reload);
                res = is_double_equal_absolute(cur_period_s, des_period_s, 0.00001);
                if(res) {
                    LOG_DEBUG(LG_IWDG, "Spot Psc %u Reload %u", prescaler, reload);
                    *out_reload = reload;
                    *out_prescaler = prescaler;
                    return res;
                }
            }
        }
    }
    if(false == res) {
        LOG_ERROR(LG_IWDG, "UnrealisticPeriod %u", period_ms);
    }
    return res;
}

bool iwdg_set_period_ms(uint32_t period_ms) {
    bool res = false;
    uint32_t prescaler = 4;
    uint32_t reload = 0;
    res = iwdg_find_timing(period_ms, &prescaler, &reload);
    if(res) {
        LOG_INFO(LG_IWDG, "Spot Psc %u Reload %u", prescaler, reload);
        WatchDog.hiwdg.Instance = IWDG;
        WatchDog.hiwdg.Init.Prescaler = Prescaler2Code(prescaler);
        WatchDog.hiwdg.Init.Reload = reload;
        HAL_StatusTypeDef ret = HAL_ERROR;
        ret = HAL_IWDG_Init(&WatchDog.hiwdg);
        if(HAL_OK == ret) {
            LOG_INFO(LG_IWDG, "SetOk");
            WatchDog.is_on = true;
            res = true;
        } else {
            LOG_ERROR(LG_IWDG, "SetErr %s", HalStatus2Str(ret));
            WatchDog.is_on = false;
        }
    }

    return res;
}

static uint32_t PrescalerCode2Num(uint8_t code) {
    uint32_t prescaler = 1;
    switch(MASK_3BIT & code) {
    case 0:
        prescaler = 4;
        break;
    case 1:
        prescaler = 8;
        break;
    case 2:
        prescaler = 16;
        break;
    case 3:
        prescaler = 32;
        break;
    case 4:
        prescaler = 64;
        break;
    case 5:
        prescaler = 128;
        break;
    case 6:
        prescaler = 256;
        break;
    case 7:
        prescaler = 256;
        break;
    default:
        prescaler = 1;
        break;
    }
    return prescaler;
}

double iwdg_calc_period_s(uint16_t clock_hz, uint16_t prescaler, uint16_t reload) {
    double period_s = 0.0;
    double tick_time = ((double)prescaler) / clock_hz;
    period_s = tick_time * ((double)reload);
    return period_s;
}

uint32_t iwdg_get_period_ms(void) {
    uint32_t period_ms = 0;
    uint16_t psc_code = 0;
    uint16_t prescaler = 0;
    uint16_t reload = 0;

    psc_code = WatchDog.RegMapPtr->Prescaler.pr;
    LOG_INFO(LG_IWDG, "PscCode %u", psc_code);

    prescaler = PrescalerCode2Num(psc_code);
    LOG_INFO(LG_IWDG, "PSC %u", prescaler);

    double tick_time = ((double)prescaler) / LSI_FREQ;
    LOG_INFO(LG_IWDG, "tick_time %f", tick_time);

    reload = WatchDog.RegMapPtr->Reload.rl;
    LOG_INFO(LG_IWDG, "Reload %u", reload);

    double period_s = iwdg_calc_period_s(LSI_FREQ, prescaler, reload);
    LOG_INFO(LG_IWDG, "Period %f s", period_s);
    period_ms = (uint32_t)(period_s * 1000.0);
    return period_ms;
}

bool iwdg_init(void) {
    bool res = false;
    LOG_INFO(LG_IWDG, "Init");
    bool out_res = true;
    // IWDG clocked by 32KHz LSI
    // 12 bit reload
    // 8bit prescaller
    WatchDog.is_on = false;
    WatchDog.period_ms = IWDG_TIMEOUT_MS;
#if defined(HAS_BOOTLOADER) && defined(HAS_PARAM)
    LOAD_PARAM(LG_IWDG, PAR_ID_IWDG_BOOTLOADER_ON, WatchDog.is_on, false);
#endif

#if defined(HAS_GENERIC) && defined(HAS_PARAM)
    LOAD_PARAM(LG_IWDG, PAR_ID_IWDG_GENERIC_ON, WatchDog.is_on, false);
#endif

#ifdef HAS_PARAM
    LOAD_PARAM(LG_IWDG, PAR_ID_IWDG_PERIOD_MS, WatchDog.period_ms, IWDG_TIMEOUT_MS);
#endif

    WatchDog.RegMapPtr = (iWdgRegMap_t*)IWDG_BASE_ADDR;
    if(WatchDog.is_on && out_res) {
        LOG_WARNING(LG_IWDG, "On");
        res = iwdg_set_period_ms(WatchDog.period_ms);
        res = iwdg_proc();
    } else {
        LOG_WARNING(LG_IWDG, "Off");
        res = true;
    }
    return res;
}
