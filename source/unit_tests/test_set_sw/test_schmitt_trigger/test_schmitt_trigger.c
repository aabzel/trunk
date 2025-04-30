#include "test_schmitt_trigger.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "log.h"
#include "schmitt_trigger.h"
#include "unit_test_check.h"

static bool up14(void) {
    bool res = true;
    return res;
}

static bool down14(void) {
    bool res = true;
    return res;
}

static SchmittTriggerHandle_t Obj = {0};

bool test_schmitt_trigger_up(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(SCHMITT_TRIGGER, LOG_LEVEL_DEBUG);

    Obj.init = true;
    Obj.state = SCHMITT_TRIGGER_STATE_UNDEF;
    Obj.prev_state = SCHMITT_TRIGGER_STATE_UNDEF;
    Obj.up_handler_cnt = 0;
    Obj.down_handler_cnt = 0;
    Obj.value = 0.0;
    Obj.valid = true;
    Obj.units = UNITS_UNDEF;
    Obj.switching_value = 100.0;
    Obj.num = 14;
    Obj.hysteresis = 10.0;
    Obj.up_call_back = up14;
    Obj.down_call_back = down14;

    EXPECT_TRUE(schmitt_trigger_proc_val_ll(&Obj, 0.0));
    EXPECT_EQ(SCHMITT_TRIGGER_STATE_DOWN, Obj.state);

    EXPECT_TRUE(schmitt_trigger_proc_val_ll(&Obj, 80.0));
    EXPECT_EQ(SCHMITT_TRIGGER_STATE_DOWN, Obj.state);

    EXPECT_TRUE(schmitt_trigger_proc_val_ll(&Obj, 95.0));
    EXPECT_EQ(SCHMITT_TRIGGER_STATE_DOWN, Obj.state);

    EXPECT_TRUE(schmitt_trigger_proc_val_ll(&Obj, 100.0));
    EXPECT_EQ(SCHMITT_TRIGGER_STATE_DOWN, Obj.state);

    EXPECT_TRUE(schmitt_trigger_proc_val_ll(&Obj, 105.0));
    EXPECT_EQ(SCHMITT_TRIGGER_STATE_DOWN, Obj.state);

    EXPECT_TRUE(schmitt_trigger_proc_val_ll(&Obj, 115.0));
    EXPECT_EQ(SCHMITT_TRIGGER_STATE_UP, Obj.state);

    set_log_level(SCHMITT_TRIGGER, LOG_LEVEL_INFO);
    return res;
}

bool test_schmitt_trigger_down(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(SCHMITT_TRIGGER, LOG_LEVEL_DEBUG);

    set_log_level(SCHMITT_TRIGGER, LOG_LEVEL_INFO);
    return res;
}
