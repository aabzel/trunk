#include "test_gpio.h"

#include <string.h>

#include "gpio_mcal.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "sys_config.h"
#include "time_mcal.h"
#include "unit_test_check.h"
#ifdef HAS_GPIO_CUSTOM_DIAG
#include "gpio_custom_diag.h"
#endif

static bool test_gpio_pull_one(Pad_t Pad) {
    LOG_WARNING(TEST, CRLF "GpioPull %s=%s", GpioPadToStr(Pad), GpioPad2WireName(Pad));
    bool res = true;
    GpioPullMode_t origin_pull = 0;
    origin_pull = gpio_pull_get(Pad);

    EXPECT_TRUE(test_gpio_pull_mode(Pad, GPIO__PULL_AIR));
    EXPECT_TRUE(test_gpio_pull_mode(Pad, GPIO__PULL_UP));
    EXPECT_TRUE(test_gpio_pull_mode(Pad, GPIO__PULL_DOWN));

    ASSERT_TRUE(gpio_pull_set(Pad, origin_pull));
    if(res) {
        LOG_INFO(TEST, "PullWire  Pad:%s %s Ok!", GpioPadToStr(Pad), GpioPad2WireName(Pad));
    } else {
        LOG_ERROR(TEST, "PullWire  Pad:%s %s Err!", GpioPadToStr(Pad), GpioPad2WireName(Pad));
    }
    return res;
}

static bool test_gpio_pin_lev(Pad_t Pad, uint8_t des_logic_level) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    uint8_t cur_logic_level = 0xFF;
    bool res = true;
    ASSERT_TRUE(gpio_logic_level_set(Pad, des_logic_level));
    wait_ms(100);

    ASSERT_TRUE(gpio_get_state(Pad, &cur_logic_level));
    EXPECT_EQ(des_logic_level, cur_logic_level);

    if(res) {
        LOG_INFO(TEST, "Set Pad:%s %s to %u OK!", GpioPadToStr(Pad), GpioPad2WireName(Pad), des_logic_level);
    } else {
        LOG_ERROR(TEST, "Set Pad:%s %s to %u Err!", GpioPadToStr(Pad), GpioPad2WireName(Pad), des_logic_level);
    }

    return res;
}

bool test_gpio_pull_mode(Pad_t Pad, GpioPullMode_t des_pull) {
    LOG_WARNING(TEST, "PullSet,Pad:%s,%s->%s", GpioPadToStr(Pad), GpioPad2WireName(Pad), GpioPullToStr(des_pull));
    uint8_t cur_pull = 0xFF;
    bool res = true;
    ASSERT_TRUE(gpio_pull_set(Pad, des_pull));
    time_delay_ms(200);

    cur_pull = gpio_pull_get(Pad);
    EXPECT_EQ(des_pull, cur_pull);

    if(res) {
        LOG_INFO(TEST, "PullSet Pad:%s %s to %s OK!", GpioPadToStr(Pad), GpioPad2WireName(Pad),
                 GpioPullToStr(des_pull));
    } else {
        LOG_ERROR(TEST, "PullSet Pad:%s %s to %s Err!", GpioPadToStr(Pad), GpioPad2WireName(Pad),
                  GpioPullToStr(des_pull));
    }

    return res;
}

bool test_gpio_pin(Pad_t Pad) {
    LOG_WARNING(TEST, CRLF "Gpio %s=%s...", GpioPadToStr(Pad), GpioPad2WireName(Pad));
    bool res = true;
    uint8_t origin_logic_level = 0;
    ASSERT_TRUE(gpio_get_state(Pad, &origin_logic_level));

    EXPECT_TRUE(test_gpio_pin_lev(Pad, 0));
    EXPECT_TRUE(test_gpio_pin_lev(Pad, 1));

    ASSERT_TRUE(gpio_logic_level_set(Pad, origin_logic_level));
    if(res) {
        LOG_INFO(TEST, "Wire,Pad:%s,%s,Ok!", GpioPadToStr(Pad), GpioPad2WireName(Pad));
    } else {
        LOG_ERROR(TEST, "Wire,Pad:%s,%s,Err!", GpioPadToStr(Pad), GpioPad2WireName(Pad));
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
                EXPECT_TRUE(test_gpio_pin(GpioConfig[i].Pad));
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
                EXPECT_TRUE(test_gpio_pull_one(GpioConfig[i].Pad));
            }
        }
    }

    return res;
}
