#include "watchdog_mcal.h"


#include "array.h"
#include "std_includes.h"
#include "watchdog_config.h"
#include "watchdog_custom.h"
#include "hal_diag.h"
#include "watchdog_custom_diag.h"
#include "watchdog_custom_types.h"
#include "log.h"
#include "mik32_hal.h"
#include "sys_config.h"
#ifdef HAS_PARAM
#include "param_drv.h"
#endif

bool watchdog_proc(void) {
    bool res = true;
    if (WatchDogInstance.on) {
        LOG_DEBUG(WATCHDOG, "Refresh");
        WatchDogInstance.WATCHDOGx->KEY.KEY=WATCHDOG_KEY_UNLOCK;
        WatchDogInstance.WATCHDOGx->KEY.KEY=WATCHDOG_KEY_LAUNCH_REFRESH;
    } else {
        LOG_DEBUG(WATCHDOG, "Skip");
    }
    return res;
}

bool watchdog_ctrl(bool on_off) {
    bool res = true;

    WatchDogInstance.WATCHDOGx->KEY.KEY=WATCHDOG_KEY_UNLOCK;
    if(on_off){
        WatchDogInstance.WATCHDOGx->KEY.KEY=WATCHDOG_KEY_LAUNCH_REFRESH;
    }else{
        WatchDogInstance.WATCHDOGx->KEY.KEY=WATCHDOG_KEY_STOP;
    }
    return res;
}

static const WatchDogInfo_t WatchDogInfo[] = {
        { .divider = 1, .prescale = MIK32_WATCH_DOG_PRE_SCALE_DIV_1, },
        { .divider = 2, .prescale = MIK32_WATCH_DOG_PRE_SCALE_DIV_2, },
        { .divider = 4, .prescale = MIK32_WATCH_DOG_PRE_SCALE_DIV_4, },
        { .divider = 16, .prescale = MIK32_WATCH_DOG_PRE_SCALE_DIV_16, },
        { .divider = 64, .prescale = MIK32_WATCH_DOG_PRE_SCALE_DIV_64, },
        { .divider = 256, .prescale = MIK32_WATCH_DOG_PRE_SCALE_DIV_256, },
        { .divider = 1024, .prescale = MIK32_WATCH_DOG_PRE_SCALE_DIV_1024, },
        { .divider = 4096, .prescale = MIK32_WATCH_DOG_PRE_SCALE_DIV_4096, },
};

 uint32_t WatchDogPrescalerCodeToDivider(const Mik32WatchDogPreScale_t prescale) {
    uint32_t divider = 1;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(WatchDogInfo);
    for (i = 0; i < cnt; i++) {
        if (WatchDogInfo[i].prescale == prescale) {
            divider = WatchDogInfo[i].divider;
            break;
        }
    }
    return divider;
}

 uint32_t WatchDogDividerToPrescalerCode(const uint32_t divider) {
    Mik32WatchDogPreScale_t prescale = 1;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(WatchDogInfo);
    for (i = 0; i < cnt; i++) {
        if (WatchDogInfo[i].divider == divider) {
            prescale = WatchDogInfo[i].prescale;
            break;
        }
    }
    return prescale;
}

#if 0
float watchdog_custom_calc_period_s(uint16_t clock_hz, uint16_t prescaler, uint16_t reload) {
    float period_s = 0.0;
    float tick_time = ((float) prescaler) / clock_hz;
    period_s = tick_time * ((float) reload);
    return period_s;
}
#endif

bool watchdog_apply_config(const WatchDogConfig_t *const Config,
		                   WatchDogRegConfig_t* const RegConfig){
	bool res = false ;
    float clock_period_s = 1.0/Config->base_freq_hz;

    uint32_t need_divider = Config->timeout_s/clock_period_s;
    uint32_t i = 0 ;
    uint32_t cnt = ARRAY_SIZE(WatchDogInfo) ;
    for(i=0;i<cnt;i++){
    	float tick_period_s = clock_period_s*((float)WatchDogInfo[i].divider);
    	need_divider =(uint32_t) Config->timeout_s/tick_period_s;
    	if( need_divider < RELOAD_VAL_MAX) {
    		RegConfig->PRELOAD = need_divider;
    		RegConfig->PRESCALE = WatchDogInfo[i].prescale;
    		WatchDogDiagRegConfig(RegConfig);
    		res = true;
            break;
    	}
    }
    return res;
}

static bool watchdog_mcal_init_ll(const WatchDogConfig_t *const Config,
                                  WatchDogHandle_t *const Node) {
    bool res = false;
    if (Config) {
        LOG_WARNING(WATCHDOG, "%s",WatchDogConfigToStr(Config));
        if (Node) {
        	Node->WATCHDOGx=WDT_BASE_ADDRESS;
            Node->valid = Config->valid;
            Node->on = Config->on;
            Node->bitness = Config->bitness;
            Node->base_freq_hz = Config->base_freq_hz;
            Node->timeout_s = Config->timeout_s;

            WatchDogRegConfig_t RegConfig = {0};
            res = watchdog_apply_config(Config, &RegConfig);
            if(res) {
            	Node->WATCHDOGx->KEY.KEY = WATCHDOG_KEY_UNLOCK;
                Node->WATCHDOGx->CON.dword = RegConfig.dword;
                res= watchdog_ctrl(  Node->on);
            }
        }
    }
    return res;
}

bool watchdog_mcal_init(void) {
    bool res = false;
    LOG_INFO(WATCHDOG, "Init");
    res = watchdog_mcal_init_ll(&WatchDogConfig, &WatchDogInstance);
    return res;
}
