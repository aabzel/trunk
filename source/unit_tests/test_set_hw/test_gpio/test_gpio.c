#include "test_gpio.h"

#include <string.h>

#include "gpio_diag.h"
#include "gpio_mcal.h"
#include "time_mcal.h"
#ifdef HAS_GPIO_CUSTOM
#include "gpio_custom_diag.h"
#endif
#include "log.h"
#include "none_blocking_pause.h"
#include "sys_config.h"
#include "unit_test_check.h"

static bool test_gpio_pin_lev(uint8_t pad_num, uint8_t des_logic_level) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    uint8_t cur_logic_level = 0xFF;
    bool res = true;
    ASSERT_TRUE(gpio_logic_level_set(pad_num, des_logic_level));
    wait_ms(100);

    ASSERT_TRUE(gpio_get_state(pad_num, &cur_logic_level));
    EXPECT_EQ(des_logic_level, cur_logic_level);

    if(res) {
        LOG_INFO(TEST, "Set Pad:%s %s to %u OK!", GpioPad2Str(pad_num), GpioPad2WireName(pad_num), des_logic_level);
    } else {
        LOG_ERROR(TEST, "Set Pad:%s %s to %u Err!", GpioPad2Str(pad_num), GpioPad2WireName(pad_num), des_logic_level);
    }

    return res;
}

static bool test_gpio_pull_mode(uint8_t pad_num, GpioPullMode_t des_pull) {
    LOG_WARNING(TEST, "PullSet Pad:%s %s to %s", GpioPad2Str(pad_num), GpioPad2WireName(pad_num),
                GpioPull2Str(des_pull));
    uint8_t cur_pull = 0xFF;
    bool res = true;
    ASSERT_TRUE(gpio_pull_set(pad_num, des_pull));
    time_delay_ms(200);

    cur_pull = gpio_pull_get(pad_num);
    EXPECT_EQ(des_pull, cur_pull);

    if(res) {
        LOG_INFO(TEST, "PullSet Pad:%s %s to %s OK!", GpioPad2Str(pad_num), GpioPad2WireName(pad_num),
                 GpioPull2Str(des_pull));
    } else {
        LOG_ERROR(TEST, "PullSet Pad:%s %s to %s Err!", GpioPad2Str(pad_num), GpioPad2WireName(pad_num),
                  GpioPull2Str(des_pull));
    }

    return res;
}

bool test_gpio_pull_one(uint8_t pad_num) {
    LOG_WARNING(TEST, CRLF "GpioPull %s=%s...", GpioPad2Str(pad_num), GpioPad2WireName(pad_num));
    bool res = true;
    GpioPullMode_t origin_pull = 0;
    origin_pull = gpio_pull_get(pad_num);

    EXPECT_TRUE(test_gpio_pull_mode(pad_num, GPIO__PULL_AIR));
    EXPECT_TRUE(test_gpio_pull_mode(pad_num, GPIO__PULL_UP));
    EXPECT_TRUE(test_gpio_pull_mode(pad_num, GPIO__PULL_DOWN));

    ASSERT_TRUE(gpio_pull_set(pad_num, origin_pull));
    if(res) {
        LOG_INFO(TEST, "PullWire  Pad:%s %s Ok!", GpioPad2Str(pad_num), GpioPad2WireName(pad_num));
    } else {
        LOG_ERROR(TEST, "PullWire  Pad:%s %s Err!", GpioPad2Str(pad_num), GpioPad2WireName(pad_num));
    }
    return res;
}

bool test_gpio_pin(uint8_t pad_num) {
    LOG_WARNING(TEST, CRLF "Gpio %s=%s...", GpioPad2Str(pad_num), GpioPad2WireName(pad_num));
    bool res = true;
    uint8_t origin_logic_level = 0;
    ASSERT_TRUE(gpio_get_state(pad_num, &origin_logic_level));

    EXPECT_TRUE(test_gpio_pin_lev(pad_num, 0));
    EXPECT_TRUE(test_gpio_pin_lev(pad_num, 1));

    ASSERT_TRUE(gpio_logic_level_set(pad_num, origin_logic_level));
    if(res) {
        LOG_INFO(TEST, "Wire,Pad:%s,%s,Ok!", GpioPad2Str(pad_num), GpioPad2WireName(pad_num));
    } else {
        LOG_ERROR(TEST, "Wire,Pad:%s,%s,Err!", GpioPad2Str(pad_num), GpioPad2WireName(pad_num));
    }
    return res;
}

bool test_gpio_write(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    uint32_t i = 0;
    bool res = true;
    uint32_t pin_cnt = gpio_get_cnt();
    for(i = 0; i < pin_cnt; i++) {
        if(GpioConfig[i].testable) {
            if(GPIO_DIR_IN != GpioConfig[i].dir) {
                EXPECT_TRUE(test_gpio_pin(GpioConfig[i].pad.byte));
            }
        }
    }

    return res;
}

bool test_gpio_const(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    ASSERT_EQ(1, GPIO__PULL_DOWN);
    ASSERT_EQ(2, GPIO__PULL_UP);
    ASSERT_EQ(3, GPIO__PULL_AIR);
    ASSERT_EQ(4, GPIO__PULL_BOTH);
    ASSERT_EQ(5, GPIO__PULL_UNDEF);
    return true;
}

bool test_gpio_types(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    ASSERT_EQ(1, sizeof(Pad_t));
    return true;
}

bool test_gpio_pull(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    uint32_t i = 0;
    bool res = true;
    uint32_t pin_cnt = gpio_get_cnt();
    for(i = 0; i < pin_cnt; i++) {
        if(GpioConfig[i].testable) {
            if(GPIO_DIR_IN == GpioConfig[i].dir) {
                EXPECT_TRUE(test_gpio_pull_one(GpioConfig[i].pad.byte));
            }
        }
    }

    return res;
}
