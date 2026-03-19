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



static bool schmitt_trigger2_proc_up(void) {
    bool res = false;
    LOG_WARNING(SCHMITT_TRIGGER, "Up");
#ifdef HAS_LIGHT_NAVIGATOR
    res = light_navigator_sunrise_proc(2);
#endif
    return res;
}

static bool schmitt_trigger2_proc_down(void) {
    bool res = false;
    LOG_WARNING(SCHMITT_TRIGGER, "Down");
#ifdef HAS_LIGHT_NAVIGATOR
    res = light_navigator_sunset_proc(2);
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
        .switching_value = 0.006,
        .name = "LTR390",
        .valid = true,
    },
    {
        .num = 2,
        .up_call_back = schmitt_trigger2_proc_up,
        .down_call_back = schmitt_trigger2_proc_down,
        .hysteresis = 3,
        .switching_value = 105, /* (too long day  48 50 52 54 56-60 62 63 65 67 70 75 80<x < 143 436)*/
        .name = "LTR390",
        .valid = true,
    },
};

SchmittTriggerHandle_t SchmittTriggerInstance[] = {
    {        .num = 1,        .valid = true,    },
    {        .num = 2,        .valid = true,    },
};

COMPONENT_GET_CNT(SchmittTrigger, schmitt_trigger)

