#include "test_sw_timer.h"

#include <stdint.h>

#include "array.h"
#include "data_utils.h"
#include "log.h"
#include "macro_utils.h"
#include "none_blocking_pause.h"
#include "software_timer.h"
#include "software_timer_const.h"
#include "unit_test_check.h"

bool test_sw_timer_set_single(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(SW_TIMER, LOG_LEVEL_DEBUG);

    SoftwareTimer_t* Node = SwTimerGetNode(SW_TIMER_TEST_NUM);
    ASSERT_NE(NULL, Node);
    uint32_t handler_cnt_orig = 0;
    handler_cnt_orig = Node->handler_cnt;
    ASSERT_TRUE(sw_timer_ctrl(SW_TIMER_TEST_NUM, 100, 0, SW_TIMER_MODE_SINGLE, SW_TIMER_CNT_DIR_UP, true));
    ASSERT_TRUE(wait_in_loop_ms(1000));
    ASSERT_EQ(Node->handler_cnt, handler_cnt_orig + 1);

    ASSERT_TRUE(sw_timer_ctrl(SW_TIMER_TEST_NUM, 100, 0, SW_TIMER_MODE_SINGLE, SW_TIMER_CNT_DIR_UP, false));
    set_log_level(SW_TIMER, LOG_LEVEL_INFO);
    return true;
}

#define SW_TIMER_PERIOD_MS 100
bool test_sw_timer_set_contin(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(SW_TIMER, LOG_LEVEL_DEBUG);
    bool res = true;
    SoftwareTimer_t* Node = SwTimerGetNode(SW_TIMER_TEST_NUM);
    EXPECT_NE(NULL, Node);
    EXPECT_TRUE(
        sw_timer_ctrl(SW_TIMER_TEST_NUM, SW_TIMER_PERIOD_MS, 0, SW_TIMER_MODE_SINGLE, SW_TIMER_CNT_DIR_UP, false));
    uint32_t handler_cnt_orig = 0;
    Node->handler_cnt = 0;
    handler_cnt_orig = Node->handler_cnt;
    EXPECT_TRUE(
        sw_timer_ctrl(SW_TIMER_TEST_NUM, SW_TIMER_PERIOD_MS, 0, SW_TIMER_MODE_CONTINUOUS, SW_TIMER_CNT_DIR_UP, true));
    EXPECT_TRUE(wait_in_loop_ms(1000));

    EXPECT_TRUE(sw_timer_fast_ctrl(SW_TIMER_TEST_NUM, false));
    EXPECT_GR(Node->handler_cnt, (handler_cnt_orig + 15));
    EXPECT_GR(handler_cnt_orig + 8, Node->handler_cnt);

    EXPECT_TRUE(sw_timer_ctrl(SW_TIMER_TEST_NUM, 100, 0, SW_TIMER_MODE_SINGLE, SW_TIMER_CNT_DIR_UP, false));

    set_log_level(SW_TIMER, LOG_LEVEL_INFO);
    return res;
}

bool test_sw_timer_get_spare(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(SW_TIMER, LOG_LEVEL_DEBUG);
    bool res = true;

    uint32_t num = sw_timer_get_spare();
    ASSERT_NE(0, num);
    set_log_level(SW_TIMER, LOG_LEVEL_INFO);
    return res;
}
