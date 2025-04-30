#include "test_dw1000_gpio.h"

#include "dw1000_gpio.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "unit_test_check.h"

bool test_dw1000_gpio_types(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    EXPECT_EQ(1, sizeof(Dw1000GpioNum_t));
    EXPECT_EQ(4, sizeof(Dw1000RegGpioDirRead_t));
    EXPECT_EQ(9, DW1000_GPIO_CNT);
    return res;
}

bool test_dw1000_gpio_pins(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(DW1000_GPIO, LOG_LEVEL_DEBUG);

    EXPECT_EQ(15, Dw1000GpioNum2pin(DW1000_GPIO_0));
    EXPECT_EQ(14, Dw1000GpioNum2pin(DW1000_GPIO_1));
    EXPECT_EQ(13, Dw1000GpioNum2pin(DW1000_GPIO_2));
    EXPECT_EQ(12, Dw1000GpioNum2pin(DW1000_GPIO_3));
    EXPECT_EQ(11, Dw1000GpioNum2pin(DW1000_GPIO_4));
    EXPECT_EQ(10, Dw1000GpioNum2pin(DW1000_GPIO_5));
    EXPECT_EQ(9, Dw1000GpioNum2pin(DW1000_GPIO_6));
    EXPECT_EQ(4, Dw1000GpioNum2pin(DW1000_GPIO_7));
    EXPECT_EQ(22, Dw1000GpioNum2pin(DW1000_GPIO_8));

    set_log_level(DW1000_GPIO, LOG_LEVEL_INFO);
    return res;
}

static bool test_dw1000_gpio_logic_level(Dw1000GpioNum_t pad_num, GpioLogicLevel_t des_logic_level) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    GpioLogicLevel_t cur_logic_level = GPIO_LVL_UNDEF;
    bool res = true;

    ASSERT_TRUE(dw1000_gpio_set_mode(pad_num, GPIO_MODE_GPIO));
    wait_ms(50);
    ASSERT_TRUE(dw1000_gpio_set_dir(pad_num, GPIO_DIR_OUT));
    wait_ms(50);
    ASSERT_TRUE(dw1000_gpio_set_logic_level(pad_num, des_logic_level));

    wait_ms(400);

    cur_logic_level = dw1000_gpio_get_logic_level(pad_num);

    EXPECT_EQ(des_logic_level, cur_logic_level);

    if(res) {
        LOG_INFO(TEST, "Set Pad:%u to %u OK!", pad_num, des_logic_level);
    } else {
        LOG_ERROR(TEST, "Set Pad:%u to %u Err!", pad_num, des_logic_level);
    }

    return res;
}

bool test_dw1000_gpio_pin(Dw1000GpioNum_t pad_num) {
    LOG_WARNING(TEST, CRLF "Gpio %u...", pad_num);
    bool res = true;

    GpioState_t GpioOriginTotalState = dw1000_gpio_get_state(pad_num);
    EXPECT_TRUE(dw1000_gpio_set_dir(pad_num, GPIO_DIR_OUT));

    EXPECT_TRUE(test_dw1000_gpio_logic_level(pad_num, GPIO_LVL_HI));
    EXPECT_TRUE(test_dw1000_gpio_logic_level(pad_num, GPIO_LVL_LOW));

    ASSERT_TRUE(dw1000_gpio_set_state(pad_num, &GpioOriginTotalState));
    if(res) {
        LOG_INFO(TEST, "Wire  Pad:%u Ok!", pad_num);
    } else {
        LOG_ERROR(TEST, "Wire  Pad:%u Err!", pad_num);
    }
    return res;
}

bool test_dw1000_gpio_set(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(DW1000_GPIO, LOG_LEVEL_DEBUG);
    bool res = true;

    EXPECT_TRUE(test_dw1000_gpio_pin(DW1000_GPIO_8));
    EXPECT_TRUE(test_dw1000_gpio_pin(DW1000_GPIO_7));
    EXPECT_TRUE(test_dw1000_gpio_pin(DW1000_GPIO_6));
    EXPECT_TRUE(test_dw1000_gpio_pin(DW1000_GPIO_5));
    EXPECT_TRUE(test_dw1000_gpio_pin(DW1000_GPIO_4));
    EXPECT_TRUE(test_dw1000_gpio_pin(DW1000_GPIO_3));
    EXPECT_TRUE(test_dw1000_gpio_pin(DW1000_GPIO_2));

    set_log_level(DW1000_GPIO, LOG_LEVEL_INFO);
    return res;
}

bool test_dw1000_gpio_hash_maps(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(DW1000_GPIO, LOG_LEVEL_DEBUG);
    bool res = true;

    EXPECT_EQ(GPIO_DIR_OUT, DwDir2GpioDir(DW1000_GPIO_DIR_OUT));
    EXPECT_EQ(GPIO_DIR_IN, DwDir2GpioDir(DW1000_GPIO_DIR_IN));

    EXPECT_EQ(DW1000_GPIO_DIR_OUT, GpioDir2Dw1000GpioDir(GPIO_DIR_OUT));
    EXPECT_EQ(DW1000_GPIO_DIR_IN, GpioDir2Dw1000GpioDir(GPIO_DIR_IN));

    EXPECT_EQ(0, GpioMode2Dw1000PinMode(GPIO_MODE_GPIO, DW1000_GPIO_0));
    EXPECT_EQ(0, GpioMode2Dw1000PinMode(GPIO_MODE_GPIO, DW1000_GPIO_1));
    EXPECT_EQ(0, GpioMode2Dw1000PinMode(GPIO_MODE_GPIO, DW1000_GPIO_2));
    EXPECT_EQ(0, GpioMode2Dw1000PinMode(GPIO_MODE_GPIO, DW1000_GPIO_3));
    EXPECT_EQ(0, GpioMode2Dw1000PinMode(GPIO_MODE_GPIO, DW1000_GPIO_4));
    EXPECT_EQ(0, GpioMode2Dw1000PinMode(GPIO_MODE_GPIO, DW1000_GPIO_5));
    EXPECT_EQ(0, GpioMode2Dw1000PinMode(GPIO_MODE_GPIO, DW1000_GPIO_6));
    EXPECT_EQ(1, GpioMode2Dw1000PinMode(GPIO_MODE_GPIO, DW1000_GPIO_7));
    EXPECT_EQ(1, GpioMode2Dw1000PinMode(GPIO_MODE_GPIO, DW1000_GPIO_8));

    EXPECT_EQ(1, GpioMode2Dw1000PinMode(GPIO_MODE_ALT1, DW1000_GPIO_0));
    EXPECT_EQ(1, GpioMode2Dw1000PinMode(GPIO_MODE_ALT1, DW1000_GPIO_1));
    EXPECT_EQ(1, GpioMode2Dw1000PinMode(GPIO_MODE_ALT1, DW1000_GPIO_2));
    EXPECT_EQ(1, GpioMode2Dw1000PinMode(GPIO_MODE_ALT1, DW1000_GPIO_3));
    EXPECT_EQ(1, GpioMode2Dw1000PinMode(GPIO_MODE_ALT1, DW1000_GPIO_4));
    EXPECT_EQ(1, GpioMode2Dw1000PinMode(GPIO_MODE_ALT1, DW1000_GPIO_5));
    EXPECT_EQ(1, GpioMode2Dw1000PinMode(GPIO_MODE_ALT1, DW1000_GPIO_6));
    EXPECT_EQ(0, GpioMode2Dw1000PinMode(GPIO_MODE_ALT1, DW1000_GPIO_7));
    EXPECT_EQ(0, GpioMode2Dw1000PinMode(GPIO_MODE_ALT1, DW1000_GPIO_8));

    EXPECT_EQ(GPIO_MODE_GPIO, Dw1000GpioMode2GpioMode(DW1000_PIN_MODE_GPIO, DW1000_GPIO_0));
    EXPECT_EQ(GPIO_MODE_GPIO, Dw1000GpioMode2GpioMode(DW1000_PIN_MODE_GPIO, DW1000_GPIO_1));
    EXPECT_EQ(GPIO_MODE_GPIO, Dw1000GpioMode2GpioMode(DW1000_PIN_MODE_GPIO, DW1000_GPIO_2));
    EXPECT_EQ(GPIO_MODE_GPIO, Dw1000GpioMode2GpioMode(DW1000_PIN_MODE_GPIO, DW1000_GPIO_3));
    EXPECT_EQ(GPIO_MODE_GPIO, Dw1000GpioMode2GpioMode(DW1000_PIN_MODE_GPIO, DW1000_GPIO_4));
    EXPECT_EQ(GPIO_MODE_GPIO, Dw1000GpioMode2GpioMode(DW1000_PIN_MODE_GPIO, DW1000_GPIO_5));
    EXPECT_EQ(GPIO_MODE_GPIO, Dw1000GpioMode2GpioMode(DW1000_PIN_MODE_GPIO, DW1000_GPIO_6));
    EXPECT_EQ(GPIO_MODE_GPIO, Dw1000GpioMode2GpioMode(DW1000_PIN_MODE_GPIO7, DW1000_GPIO_7));
    EXPECT_EQ(GPIO_MODE_GPIO, Dw1000GpioMode2GpioMode(DW1000_PIN_MODE_GPIO8, DW1000_GPIO_8));

    EXPECT_EQ(GPIO_MODE_ALT1, Dw1000GpioMode2GpioMode(DW1000_PIN_MODE_RXOKLED, DW1000_GPIO_0));
    EXPECT_EQ(GPIO_MODE_ALT1, Dw1000GpioMode2GpioMode(DW1000_PIN_MODE_SFDLED_OUT, DW1000_GPIO_1));
    EXPECT_EQ(GPIO_MODE_ALT1, Dw1000GpioMode2GpioMode(DW1000_PIN_MODE_RXLED_OUT, DW1000_GPIO_2));
    EXPECT_EQ(GPIO_MODE_ALT1, Dw1000GpioMode2GpioMode(DW1000_PIN_MODE_TXLED_OUT, DW1000_GPIO_3));
    EXPECT_EQ(GPIO_MODE_ALT1, Dw1000GpioMode2GpioMode(DW1000_PIN_MODE_EXTPA_OUT, DW1000_GPIO_4));
    EXPECT_EQ(GPIO_MODE_ALT1, Dw1000GpioMode2GpioMode(DW1000_PIN_MODE_EXTTXE_OUT, DW1000_GPIO_5));
    EXPECT_EQ(GPIO_MODE_ALT1, Dw1000GpioMode2GpioMode(DW1000_PIN_MODE_EXTRXE_OUT, DW1000_GPIO_6));
    EXPECT_EQ(GPIO_MODE_ALT1, Dw1000GpioMode2GpioMode(DW1000_PIN_MODE_SYNC_IN, DW1000_GPIO_7));
    EXPECT_EQ(GPIO_MODE_ALT1, Dw1000GpioMode2GpioMode(DW1000_PIN_MODE_IRQ_OUT, DW1000_GPIO_8));

    EXPECT_TRUE(dw1000_gpio_is_valid_num(DW1000_GPIO_0));
    EXPECT_TRUE(dw1000_gpio_is_valid_num(DW1000_GPIO_1));
    EXPECT_TRUE(dw1000_gpio_is_valid_num(DW1000_GPIO_2));
    EXPECT_TRUE(dw1000_gpio_is_valid_num(DW1000_GPIO_3));
    EXPECT_TRUE(dw1000_gpio_is_valid_num(DW1000_GPIO_4));
    EXPECT_TRUE(dw1000_gpio_is_valid_num(DW1000_GPIO_5));
    EXPECT_TRUE(dw1000_gpio_is_valid_num(DW1000_GPIO_6));
    EXPECT_TRUE(dw1000_gpio_is_valid_num(DW1000_GPIO_7));
    EXPECT_TRUE(dw1000_gpio_is_valid_num(DW1000_GPIO_8));
    EXPECT_FALSE(dw1000_gpio_is_valid_num(10));

    set_log_level(DW1000_GPIO, LOG_LEVEL_INFO);
    return res;
}

static bool test_dw1000_gpio_set_get_cross(Dw1000GpioNum_t gpio_pin_setter, Dw1000GpioNum_t gpio_pin_getter,
                                           GpioLogicLevel_t set_logic_level) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    GpioState_t GpioOriginTotalStateSetter = dw1000_gpio_get_state(gpio_pin_setter);
    GpioState_t GpioOriginTotalStateGetter = dw1000_gpio_get_state(gpio_pin_getter);

    EXPECT_TRUE(dw1000_gpio_set_dir(gpio_pin_getter, GPIO_DIR_IN));
    EXPECT_TRUE(dw1000_gpio_set_dir(gpio_pin_setter, GPIO_DIR_OUT));

    EXPECT_TRUE(dw1000_gpio_set_logic_level(gpio_pin_setter, set_logic_level));

    GpioLogicLevel_t read_logic_level = dw1000_gpio_get_logic_level(gpio_pin_getter);

    EXPECT_EQ(read_logic_level, set_logic_level);

    ASSERT_TRUE(dw1000_gpio_set_state(gpio_pin_setter, &GpioOriginTotalStateSetter));
    ASSERT_TRUE(dw1000_gpio_set_state(gpio_pin_getter, &GpioOriginTotalStateGetter));

    return res;
}

/*Connect by jumper GPIO2 with GPIO3*/
bool test_dw1000_gpio_cross(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(DW1000_GPIO, LOG_LEVEL_DEBUG);
    bool res = true;

    EXPECT_TRUE(test_dw1000_gpio_set_get_cross(DW1000_GPIO_3, DW1000_GPIO_2, GPIO_LVL_LOW));
    EXPECT_TRUE(test_dw1000_gpio_set_get_cross(DW1000_GPIO_3, DW1000_GPIO_2, GPIO_LVL_HI));

    EXPECT_TRUE(test_dw1000_gpio_set_get_cross(DW1000_GPIO_2, DW1000_GPIO_3, GPIO_LVL_LOW));
    EXPECT_TRUE(test_dw1000_gpio_set_get_cross(DW1000_GPIO_2, DW1000_GPIO_3, GPIO_LVL_HI));

    set_log_level(DW1000_GPIO, LOG_LEVEL_INFO);
    return res;
}

bool test_dw1000_gpio_set_multiple(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(DW1000_GPIO, LOG_LEVEL_DEBUG);
    bool res = true;
    GpioState_t GpioOriginTotalState2 = dw1000_gpio_get_state(DW1000_GPIO_2);
    GpioState_t GpioOriginTotalState3 = dw1000_gpio_get_state(DW1000_GPIO_3);

    EXPECT_TRUE(dw1000_gpio_set_logic_level(DW1000_GPIO_2, GPIO_LVL_HI));
    EXPECT_TRUE(dw1000_gpio_set_logic_level(DW1000_GPIO_3, GPIO_LVL_HI));

    EXPECT_EQ(GPIO_LVL_HI, dw1000_gpio_get_logic_level(DW1000_GPIO_2));
    EXPECT_EQ(GPIO_LVL_HI, dw1000_gpio_get_logic_level(DW1000_GPIO_3));

    ASSERT_TRUE(dw1000_gpio_set_state(DW1000_GPIO_2, &GpioOriginTotalState2));
    ASSERT_TRUE(dw1000_gpio_set_state(DW1000_GPIO_3, &GpioOriginTotalState3));

    set_log_level(DW1000_GPIO, LOG_LEVEL_INFO);
    return res;
}

/*GPIO0 must be connected to GND*/
bool test_dw1000_gpio_read_0v(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(DW1000_GPIO, LOG_LEVEL_DEBUG);
    bool res = true;

    ASSERT_TRUE(dw1000_gpio_set_mode(DW1000_GPIO_0, GPIO_MODE_GPIO));
    EXPECT_TRUE(dw1000_gpio_set_dir(DW1000_GPIO_0, GPIO_DIR_IN));
    EXPECT_EQ(GPIO_LVL_LOW, dw1000_gpio_get_logic_level(DW1000_GPIO_0));

    set_log_level(DW1000_GPIO, LOG_LEVEL_INFO);
    return res;
}

/*GPIO0 must be connected to 3.3V*/
bool test_dw1000_gpio_read_3v(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(DW1000_GPIO, LOG_LEVEL_DEBUG);
    bool res = true;

    ASSERT_TRUE(dw1000_gpio_set_mode(DW1000_GPIO_1, GPIO_MODE_GPIO));
    EXPECT_TRUE(dw1000_gpio_set_dir(DW1000_GPIO_1, GPIO_DIR_IN));
    EXPECT_EQ(GPIO_LVL_HI, dw1000_gpio_get_logic_level(DW1000_GPIO_1));

    set_log_level(DW1000_GPIO, LOG_LEVEL_INFO);
    return res;
}

static bool test_dw1000_gpio_dir_one(Dw1000GpioNum_t pad_num, GpioDir_t des_dir) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    GpioDir_t cur_dir = GPIO_DIR_UNDEF;
    bool res = true;

    ASSERT_TRUE(dw1000_gpio_set_mode(pad_num, GPIO_MODE_GPIO));

    ASSERT_TRUE(dw1000_gpio_set_dir(pad_num, des_dir));

    wait_ms(400);

    cur_dir = dw1000_gpio_get_dir(pad_num);

    EXPECT_EQ(des_dir, cur_dir);

    if(res) {
        LOG_INFO(TEST, "SetDir Pad:%u to %u OK!", pad_num, des_dir);
    } else {
        LOG_ERROR(TEST, "SetDir Pad:%u to %u Err!", pad_num, des_dir);
    }

    return res;
}

static bool test_dw1000_gpio_dir(Dw1000GpioNum_t pad_num) {
    LOG_WARNING(TEST, CRLF "Gpio%u Dir...", pad_num);
    bool res = true;

    GpioState_t GpioOriginTotalState = dw1000_gpio_get_state(pad_num);

    EXPECT_TRUE(test_dw1000_gpio_dir_one(pad_num, GPIO_DIR_OUT));
    EXPECT_TRUE(test_dw1000_gpio_dir_one(pad_num, GPIO_DIR_IN));

    ASSERT_TRUE(dw1000_gpio_set_state(pad_num, &GpioOriginTotalState));
    if(res) {
        LOG_INFO(TEST, "Dir Pad:%u Ok!", pad_num);
    } else {
        LOG_ERROR(TEST, "Dir Pad:%u Err!", pad_num);
    }
    return res;
}

bool test_dw1000_gpio_set_dir(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(DW1000_GPIO, LOG_LEVEL_DEBUG);
    bool res = true;

    EXPECT_TRUE(test_dw1000_gpio_dir(DW1000_GPIO_8));
    EXPECT_TRUE(test_dw1000_gpio_dir(DW1000_GPIO_7));
    EXPECT_TRUE(test_dw1000_gpio_dir(DW1000_GPIO_6));
    EXPECT_TRUE(test_dw1000_gpio_dir(DW1000_GPIO_5));
    EXPECT_TRUE(test_dw1000_gpio_dir(DW1000_GPIO_4));
    EXPECT_TRUE(test_dw1000_gpio_dir(DW1000_GPIO_3));
    EXPECT_TRUE(test_dw1000_gpio_dir(DW1000_GPIO_2));

    set_log_level(DW1000_GPIO, LOG_LEVEL_INFO);
    return res;
}

bool test_dw1000_gpio_init(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(DW1000_GPIO, LOG_LEVEL_DEBUG);
    bool res = true;

    EXPECT_TRUE(dw1000_gpio_is_init());

    set_log_level(DW1000_GPIO, LOG_LEVEL_INFO);
    return res;
}
