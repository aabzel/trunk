#include "test_mic2026.h"

#include <stdint.h>

#include "array.h"
#include "data_utils.h"
#include "log.h"
#include "macro_utils.h"
#include "mic2026_const.h"
#include "mic2026_drv.h"
#include "none_blocking_pause.h"
#include "unit_test_check.h"

// tsr mic
static bool test_mic2026_write_one(Mic2026Channel_t chan, GpioLogicLevel_t LogicLevelSet) {
    LOG_INFO(TEST, "%s() Ch:%u LL:%u", __FUNCTION__, chan, LogicLevelSet);
    bool res = true;
    GpioLogicLevel_t LogicLevelReal;
    GpioLogicLevel_t LogicLevelOrig;
    LogicLevelOrig = mic2026_get_channel_ctrl(chan);

    ASSERT_TRUE(mic2026_set_channel_ctrl(chan, LogicLevelSet));
    ASSERT_TRUE(wait_in_loop_ms(3000));

    LogicLevelReal = mic2026_get_channel_ctrl(chan);
    ASSERT_EQ(LogicLevelReal, LogicLevelSet);

    ASSERT_TRUE(mic2026_set_channel_ctrl(chan, LogicLevelOrig));

    return res;
}

bool test_mic2026_read(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    GpioLogicLevel_t LogicLevelReal;
    LogicLevelReal = mic2026_get_channel_ctrl(CHANNEL_A);
    EXPECT_NE(GPIO_LVL_UNDEF, LogicLevelReal);
    LogicLevelReal = mic2026_get_channel_ctrl(CHANNEL_B);
    EXPECT_NE(GPIO_LVL_UNDEF, LogicLevelReal);
    return res;
}

bool test_mic2026_write(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE(test_mic2026_write_one(CHANNEL_B, GPIO_LVL_HI));
    ASSERT_TRUE(test_mic2026_write_one(CHANNEL_B, GPIO_LVL_LOW));
    ASSERT_TRUE(test_mic2026_write_one(CHANNEL_A, GPIO_LVL_HI));
    ASSERT_TRUE(test_mic2026_write_one(CHANNEL_A, GPIO_LVL_LOW));

    return res;
}
