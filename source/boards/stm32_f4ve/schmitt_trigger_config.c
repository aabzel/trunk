#include "schmitt_trigger_config.h"

#include "data_utils.h"

#ifdef HAS_LIGHT_NAVIGATOR
#include "light_navigator.h"
#endif
#include "log.h"

static bool schmitt_trigger1_proc_up(void) {
    bool res = false;
    LOG_WARNING(SCHMITT_TRIGGER, "Up");
#ifdef HAS_LIGHT_NAVIGATOR
    res = light_navigator_sunrise_proc(1);
#endif
    return res;
}

static bool schmitt_trigger1_proc_down(void) {
    bool res = false;
    LOG_WARNING(SCHMITT_TRIGGER, "Down");
#ifdef HAS_LIGHT_NAVIGATOR
    res = light_navigator_sunset_proc(1);
#endif
    return res;
}

const SchmittTriggerConfig_t SchmittTriggerConfig[] = {
    {
        .num = 1,
        .up_call_back = schmitt_trigger1_proc_up,
        .down_call_back = schmitt_trigger1_proc_down,
        .hysteresis = 0.001,
        .units = UNITS_UVI,
        .switching_value = 0.006, /*105lx (too long day  48 50 52 54 56-60 62 63 65 67 70 75 80<x < 143 436)*/
        .name = "LTR390", //BH1750
        .valid = true,
    },
};


SchmittTriggerHandle_t SchmittTriggerInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

uint32_t schmitt_trigger_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(SchmittTriggerInstance);
    cnt2 = ARRAY_SIZE(SchmittTriggerConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
