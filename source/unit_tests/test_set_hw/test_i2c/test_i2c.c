#include "test_i2c.h"

#include <string.h>

#include "i2c_mcal.h"
#include "gpio_mcal.h"
#include "sys_config.h"
#include "unit_test_check.h"

bool test_i2c_types(void) {
    return true;
}

bool test_i2c_pad(const Pad_t Pad) {
    LOG_INFO(TEST, "%s() Pad:%s", __FUNCTION__,GpioPadToStr(Pad));
    bool res = true;
    ASSERT_TRUE( gpio_is_valid_pad(Pad)  );
    ASSERT_TRUE( gpio_init_input(Pad)   );
    ASSERT_EQ( GPIO_LVL_HI, gpio_get_state_short(Pad)   );
    ASSERT_TRUE( gpio_init_pad(Pad)   );
    return res;
}

bool test_i2c_idle(uint8_t num) {
    LOG_INFO(TEST, "%s()", __FUNCTION__,num);
    bool res = true;
    I2cHandle_t* Node = I2cGetNode(num);
    ASSERT_NE(NULL, Node);
    ASSERT_TRUE(  test_i2c_pad(Node->PadScl));
    ASSERT_TRUE(  test_i2c_pad(Node->PadSda));
    return res;
}


#ifdef HAS_I2C1

bool test_i2c1_idle(void){
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    ASSERT_TRUE( test_i2c_idle(1));
    return true;
}

bool test_i2c1_write(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    return false;
}

bool test_i2c1_read(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    return false;
}
#endif




#ifdef HAS_I2C2
bool test_i2c2_write(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    return false;
}

bool test_i2c2_read(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    return false;
}

bool test_i2c2_idle(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    ASSERT_TRUE( test_i2c_idle(2));
    return true;
}

#endif


#ifdef HAS_I2C3

bool test_i2c3_idle(void){
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    ASSERT_TRUE( test_i2c_idle(3));
    return true;
}

bool test_i2c3_write(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    return false;
}

bool test_i2c3_read(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    return false;
}

#endif

