#include "schmitt_trigger_config.h"

#include "data_utils.h"
#include "log.h"

#include "clock_divider.h"

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
    res = clock_divider_proc_period(1);
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
    res = clock_divider_proc_period(2);
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
