#include "test_led_mono.h"

#include <string.h>

#include "gpio_diag.h"
#include "led_mono_diag.h"
#include "led_mono_drv.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "unit_test_check.h"

static bool test_led_mono_one_level(uint8_t led_num, GpioLogicLevel_t set_level) {
    bool res = true;
    LOG_INFO(LED_MONO, "%u Test %u=%s", led_num, set_level, GpioLevel2Str(set_level));

    Color_t orig_level = led_mono_get(led_num);

    ASSERT_TRUE(led_mono_set(led_num, set_level));
    ASSERT_TRUE(wait_ms(GPIO_TRANSITION_PROCESS_TIMEOUT_MS));

    Color_t get_level = led_mono_get(led_num);

    ASSERT_EQ(set_level, get_level);

    ASSERT_TRUE(led_mono_set(led_num, orig_level));
    return res;
}

bool test_led_mono_one(uint8_t led_num) {
    LOG_INFO(LED_MONO, "Test %u", led_num);
    bool res = true;
    ASSERT_TRUE(test_led_mono_one_level(led_num, 0));
    ASSERT_TRUE(test_led_mono_one_level(led_num, 1));
    return res;
}

bool test_led_mono_set(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(LED_MONO, LOG_LEVEL_DEBUG);
    set_log_level(GPIO, LOG_LEVEL_DEBUG);
    bool res = true;
    uint32_t led_num = 0;
    uint32_t cnt = led_mono_get_cnt();
    for(led_num = 1; led_num <= cnt; led_num++) {
        EXPECT_TRUE(test_led_mono_one(led_num));
    }
    set_log_level(LED_MONO, LOG_LEVEL_INFO);
    set_log_level(GPIO, LOG_LEVEL_INFO);
    return res;
}

bool test_led_mono_blink(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(LED_MONO, LOG_LEVEL_DEBUG);
    set_log_level(GPIO, LOG_LEVEL_DEBUG);
    bool res = true;
    uint32_t led_num = 0;
    uint32_t cnt = led_mono_get_cnt();
    for(led_num = 1; led_num <= cnt; led_num++) {
        EXPECT_TRUE(led_mono_blink(led_num, 50));
        EXPECT_TRUE(wait_in_loop_ms(1000));
    }
    set_log_level(LED_MONO, LOG_LEVEL_INFO);
    set_log_level(GPIO, LOG_LEVEL_INFO);
    return res;
}

bool test_led_mono_pwm(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(LED_MONO, LOG_LEVEL_DEBUG);
    set_log_level(GPIO, LOG_LEVEL_DEBUG);
    bool res = true;
    uint32_t led_num = 0;
    uint32_t cnt = led_mono_get_cnt();
    for(led_num = 1; led_num <= cnt; led_num++) {
        EXPECT_TRUE(led_mono_pwm(led_num, 2, 50));
        EXPECT_TRUE(wait_in_loop_ms(2000));
    }
    set_log_level(LED_MONO, LOG_LEVEL_INFO);
    set_log_level(GPIO, LOG_LEVEL_INFO);
    return res;
}

bool test_led_mono_const(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    ASSERT_GR(0, LED_MONO_POLL_PERIOD_US);
    return true;
}

bool test_led_mono_types(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    ASSERT_EQ(1, sizeof(Pad_t));
    ASSERT_EQ(1, sizeof(GpioLogicLevel_t));
    ASSERT_EQ(1, sizeof(LedMode_t));
    return true;
}
