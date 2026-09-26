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

const SchmittTriggerConfig_t SchmittTriggerConfig[] = {
    {
        .num = 1,
        .up_call_back = schmitt_trigger1_proc_up,
        .down_call_back = schmitt_trigger1_proc_down,
        .hysteresis = 0.001,
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

COMPONENT_GET_CNT(SchmittTrigger, schmitt_trigger)

