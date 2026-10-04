#include "schmitt_trigger_config.h"

#include "data_utils.h"
#include "light_navigator.h"
#include "log.h"

static bool schmitt_trigger1_proc_up(void) {
    bool res = false;
    LOG_WARNING(SCHMITT_TRIGGER, "Up");
    res = light_navigator_sunrise_proc(1);
    return res;
}

static bool schmitt_trigger1_proc_down(void) {
    bool res = false;
    LOG_WARNING(SCHMITT_TRIGGER, "Down");
    res = light_navigator_sunset_proc(1);
    return res;
}

static bool schmitt_trigger2_proc_up(void) {
    bool res = false;
    LOG_WARNING(SCHMITT_TRIGGER, "Up");
    res = light_navigator_sunrise_proc(2);
    return res;
}

static bool schmitt_trigger2_proc_down(void) {
    bool res = false;
    LOG_WARNING(SCHMITT_TRIGGER, "Down");
    res = light_navigator_sunset_proc(2);
    return res;
}

const SchmittTriggerConfig_t SECTION_CFG_DATA SchmittTriggerConfig[] = {
    {
        .num = 1,
        .up_call_back = schmitt_trigger1_proc_up,
        .down_call_back = schmitt_trigger1_proc_down,
        .hysteresis = 0.4,
        .switching_value = LIGHT_NAVIGATOR_DAY_NIGHT_BORDER,
        .name = "PhotoResister",
        .valid = true,
    },

    {
        .num = 2,
        .up_call_back = schmitt_trigger2_proc_up,
        .down_call_back = schmitt_trigger2_proc_down,
        .hysteresis = 2,
        .switching_value = 71, /* (too long day  48 50 52 54 56-60 <x <436 to short day)*/
        .name = "BH1750",
        .valid = true,
    },
};

SchmittTriggerHandle_t SchmittTriggerInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
    {
        .num = 2,
        .valid = true,
    },
};

COMPONENT_GET_CNT(SchmittTrigger, schmitt_trigger)

