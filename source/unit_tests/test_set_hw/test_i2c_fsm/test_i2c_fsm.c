#include "test_i2c_fsm.h"

#include <string.h>

#include "i2c_fsm.h"
#include "log.h"
#include "unit_test_check.h"

bool test_i2c_fsm_write_byte_one(uint8_t num, uint8_t chip_addr, uint8_t reg_addr, uint8_t reg_value) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    uint8_t read_value = 0;
    ASSERT_TRUE(i2c_fsm_write_byte(num, chip_addr, reg_addr, reg_value));
    ASSERT_TRUE(i2c_fsm_read_byte(num, chip_addr, reg_addr, &read_value));
    LOG_INFO(TEST, "Write:0x%02x,Read:0x%02x", reg_value, read_value);
    ASSERT_EQ(reg_value, read_value);
    return true;
}

#ifdef HAS_I2C1

bool test_i2c_fsm1_check_asic_ack(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    ASSERT_TRUE(i2c_fsm_check_addr(1, 0x19));
    return true;
}

bool test_i2c_fsm1_check_asic_nak(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    ASSERT_FALSE(i2c_fsm_check_addr(1, 0x11));
    return true;
}

bool test_i2c_fsm1_read(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    return true;
}

bool test_i2c_fsm1_write_byte(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);

    ASSERT_TRUE(test_i2c_fsm_write_byte_one(1, 0x19, 0x26, 0x55));
    ASSERT_TRUE(test_i2c_fsm_write_byte_one(1, 0x19, 0x26, 0xaa));
    return true;
}

bool test_i2c_fsm1_read_byte(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    uint8_t value = 0;
    ASSERT_TRUE(i2c_fsm_read_byte(1, 0x19, 0x0F, &value));
    ASSERT_EQ(0x33, value);
    return true;
}
#endif /*HAS_I2C1*/

#ifdef HAS_I2C2

bool test_i2c_fsm2_empty(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    ASSERT_TRUE(i2c_fsm_empty(2));
    return true;
}

bool test_i2c_fsm2_check_asic_ack(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    ASSERT_TRUE(i2c_fsm_check_addr(2, 0x1A));
    return true;
}

bool test_i2c_fsm2_check_asic_nak(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    ASSERT_FALSE(i2c_fsm_check_addr(2, 0x11));
    return true;
}

bool test_i2c_fsm2_write_word(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    U16_bit_t un16;
    un16.u8[0] = 0x0F << 1;
    un16.u8[1] = 0x5a;
    ASSERT_TRUE(i2c_fsm_write_word(2, 0x1A, un16.u16));
    return true;
}

bool test_i2c_fsm2_read_word(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    uint16_t word = 0;
    ASSERT_TRUE(i2c_fsm_read_word(2, 0x1A, 0x3f << 1, &word));
    LOG_INFO(TEST, "Word:0x%04x", word);
    ASSERT_EQ(0x1A00, word);
    return true;
}

bool test_i2c_fsm2_read(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    return true;
}
#endif /*HAS_I2C2*/

#ifdef HAS_I2C3
bool test_i2c_fsm3_write(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    return false;
}
bool test_i2c_fsm3_read(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    return false;
}
#endif /*HAS_I2C3*/
