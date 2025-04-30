#include "test_ltr390.h"

#include "array.h"
#include "debug_info.h"
#include "i2c_mcal.h"
#include "log.h"
#include "ltr390_drv.h"
#include "unit_test_check.h"

bool test_ltr390_types(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    ASSERT_EQ(1, sizeof(Ltr390RegGeneral_t));
    ASSERT_EQ(1, sizeof(Ltr390Reg_t));

    uint8_t adr_u8 = 0x0d;
    ASSERT_EQ(0x000d, RegAddr2Word(&adr_u8, 1));
    return true;
}

bool test_ltr390_connect(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE(ltr390_is_connected(LTR390_TEST_INSTANCE));
    return res;
}

bool test_ltr390_reg_read(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    uint8_t value = 0;
    bool res = false;
    res = ltr390_register_read(LTR390_TEST_INSTANCE, LTR390_REG_ADDR_PART_ID, &value);
    ASSERT_TRUE(res);
    LOG_INFO(TEST, "0x%02x", value);
    return true;
}

bool test_ltr390_reg_write(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);

    ASSERT_TRUE(ltr390_register_write(LTR390_TEST_INSTANCE, LTR390_REG_ADDR_GAIN, 0x01));
    ASSERT_TRUE(ltr390_register_write(LTR390_TEST_INSTANCE, LTR390_REG_ADDR_GAIN, 0x00));
    return true;
}
