#include "test_dwm3000.h"

#include <string.h>

#include "dwm3000_diag.h"
#include "dwm3000_drv.h"
#include "dwm3000_registers.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "unit_test_check.h"

bool test_dwm3000_types(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    EXPECT_EQ(1, sizeof(Dwm3000Header_t));
    EXPECT_EQ(2, sizeof(Dwm3000SubAddrHeader_t));
    EXPECT_EQ(2, sizeof(Dwm3000RegChanCtrl_t));
    EXPECT_EQ(4, sizeof(Dwm3000DevId_t));
    EXPECT_EQ(4, sizeof(Dwm3000RegSysState_t));
    EXPECT_EQ(4, sizeof(Dwm3000RegSecCtrl_t));
    EXPECT_EQ(6, sizeof(TxFctrl_t));
    EXPECT_EQ(6, sizeof(Dwm3000RegSysEnable_t));
    EXPECT_EQ(6, sizeof(Dwm3000RegSysStatus_t));
    return res;
}

bool test_dwm3000_connected(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(dwm3000_is_connected());
    return true;
}

bool test_dwm3000_read(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint8_t rx_byte = 0;
    ASSERT_TRUE(dwm3000_read(0, &rx_byte));
    ASSERT_EQ(0x02, rx_byte);
    return true;
}

bool test_dwm3000_read_offset(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(dwm3000_read_offset(0, 0, 4, Dwm3000Instance.buff));
    return true;
}

static bool test_dwm3000_gpio_pin_lev(Dwm3GpioNum_t pad_num, GpioLogicLevel_t des_logic_level) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    GpioLogicLevel_t cur_logic_level = GPIO_LVL_UNDEF;
    bool res = true;
    ASSERT_TRUE(dwm3000_gpio_set(pad_num, des_logic_level));
    wait_ms(200);

    cur_logic_level = dwm3000_gpio_get(pad_num);
    EXPECT_EQ(des_logic_level, cur_logic_level);

    if(res) {
        LOG_INFO(TEST, "Set Pad:%u to %u OK!", pad_num, des_logic_level);
    } else {
        LOG_ERROR(TEST, "Set Pad:%u to %u Err!", pad_num, des_logic_level);
    }

    return res;
}

bool test_dwm3000_gpio_pin(Dwm3GpioNum_t pad_num) {
    LOG_WARNING(TEST, CRLF "Gpio %u...", pad_num);
    bool res = true;

    GpioState_t GpioOriginTotalState = dwm3000_gpio_state_get(pad_num);
    EXPECT_TRUE(dwm3000_gpio_dir_set(pad_num, GPIO_DIR_OUT));

    EXPECT_TRUE(test_dwm3000_gpio_pin_lev(pad_num, GPIO_LVL_LOW));
    EXPECT_TRUE(test_dwm3000_gpio_pin_lev(pad_num, GPIO_LVL_HI));

    ASSERT_TRUE(dwm3000_gpio_state_set(pad_num, &GpioOriginTotalState));
    if(res) {
        LOG_INFO(TEST, "Wire  Pad:%u Ok!", pad_num);
    } else {
        LOG_ERROR(TEST, "Wire  Pad:%u Err!", pad_num);
    }
    return res;
}

bool test_dwm3000_gpio_set(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;

    EXPECT_TRUE(test_dwm3000_gpio_pin(GPIO_2));
    EXPECT_TRUE(test_dwm3000_gpio_pin(GPIO_3));

    return res;
}
