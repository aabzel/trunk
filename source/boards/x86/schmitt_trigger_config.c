#include "schmitt_trigger_config.h"

#include "data_utils.h"
#include "log.h"

#ifdef HAS_CLOCK_DIVIDER
#include "clock_divider.h"
#endif

static bool schmitt_trigger1_proc_up(void) {
    bool res = false;
    LOG_WARNING(SCHMITT_TRIGGER, "Up1");
    return res;
}

static bool schmitt_trigger1_proc_down(void) {
    bool res = false;
    LOG_WARNING(SCHMITT_TRIGGER, "Down1");

    return res;
}

static bool schmitt_trigger2_proc_up(void) {
    bool res = false;
    LOG_PARN(SCHMITT_TRIGGER, "Up2");
#ifdef HAS_CLOCK_DIVIDER
    res = clock_divider_proc_period(1);
#endif
    return res;
}

static bool schmitt_trigger2_proc_down(void) {
    bool res = true;
    LOG_PARN(SCHMITT_TRIGGER, "Down2");
    return res;
}

static bool schmitt_trigger3_proc_up(void) {
    bool res = false;
    LOG_PARN(SCHMITT_TRIGGER, "Up3");
#ifdef HAS_CLOCK_DIVIDER
    res = clock_divider_proc_period(2);
#endif
    return res;
}

static bool schmitt_trigger3_proc_down(void) {
    bool res = true;
    LOG_PARN(SCHMITT_TRIGGER, "Down3");

    return res;
}

const SchmittTriggerConfig_t SchmittTriggerConfig[] = {
    {
        .num = 1,
        .up_call_back = schmitt_trigger1_proc_up,
        .down_call_back = schmitt_trigger1_proc_down,
        .hysteresis = 0.2,
        .switching_value = 1.0, /* */
        .name = "test",
        .valid = true,
    },
    {
        .num = 2,
        .up_call_back = schmitt_trigger2_proc_up,
        .down_call_back = schmitt_trigger2_proc_down,
        .hysteresis = 0.0,
        .switching_value = 0.0, /* */
        .name = "I",
        .valid = true,
    },
    {
        .num = 3,
        .up_call_back = schmitt_trigger3_proc_up,
        .down_call_back = schmitt_trigger3_proc_down,
        .hysteresis = 0.0,
        .switching_value = 0.0, /* */
        .name = "Q",
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
    {
        .num = 3,
        .valid = true,
    },
};

COMPONENT_GET_CNT(SchmittTrigger, schmitt_trigger)

