#include "test_led_rgb.h"

#include <string.h>

#include "clock.h"
#include "led_rgb_diag.h"
#include "led_rgb_drv.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "unit_test_check.h"

bool test_led_rgb_color_one(uint8_t led_num, Color_t set_color) {
    LOG_INFO(LED_RGB, "%u TestColor %u=%s", led_num, set_color, Color2Str(set_color));
    bool res = true;

    Color_t orig_color = led_rgb_get_color(led_num);

    ASSERT_TRUE(led_rgb_set_color(led_num, set_color));
    ASSERT_TRUE(wait_ms(GPIO_TRANSITION_PROCESS_TIMEOUT_MS));

    Color_t get_color = led_rgb_get_color(led_num);

    ASSERT_EQ(set_color, get_color);

    ASSERT_TRUE(led_rgb_set_color(led_num, orig_color));
    return res;
}

bool test_led_rgb_colors_one(uint8_t led_num) {
    LOG_INFO(LED_RGB, "Test %u", led_num);
    uint32_t color_cnt = led_rgb_get_color_cnt();
    uint32_t i = 0;
    bool res = true;
    for(i = 0; i < color_cnt; i++) {
        EXPECT_TRUE(test_led_rgb_color_one(led_num, LedRgbInfoLUT[i].color));
    }
    return res;
}

bool test_led_rgb_color_set(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(LED_RGB, LOG_LEVEL_DEBUG);
    set_log_level(GPIO, LOG_LEVEL_DEBUG);
    bool res = true;
    uint32_t led_num = 0;
    uint32_t cnt = led_rgb_get_cnt();
    for(led_num = 1; led_num <= cnt; led_num++) {
        EXPECT_TRUE(test_led_rgb_colors_one(led_num));
    }
    set_log_level(LED_RGB, LOG_LEVEL_INFO);
    set_log_level(GPIO, LOG_LEVEL_INFO);
    return res;
}

bool test_led_rgb_const(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    ASSERT_EQ(0, COLOR_BLACK);
    ASSERT_EQ(4, COLOR_RED);
    ASSERT_EQ(2, COLOR_GREEN);
    ASSERT_EQ(1, COLOR_BLUE);
    ASSERT_EQ(5, COLOR_PURPLE);
    ASSERT_EQ(6, COLOR_YELLOW);
    ASSERT_EQ(3, COLOR_CYANIC);
    ASSERT_EQ(7, COLOR_WHITE);
    return true;
}

bool test_led_rgb_types(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    ASSERT_EQ(1, sizeof(LedRgbState_t));
    ASSERT_EQ(1, sizeof(Color_t));
    ASSERT_EQ(2, sizeof(LedRgbInfo_t));
    ASSERT_EQ(3, sizeof(LedRgbPads_t));
    ASSERT_EQ(1, sizeof(Pad_t));
    return true;
}
