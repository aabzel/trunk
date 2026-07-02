#include "test_i2c.h"

#include <string.h>

#include "i2c_mcal.h"
#include "sys_config.h"
#include "unit_test_check.h"

bool test_i2c_types(void) {
    return true;
}

#ifdef HAS_I2C2
bool test_i2c2_write(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    return false;
}

bool test_i2c2_read(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    return false;
}
#endif

#ifdef HAS_I2C1

bool test_i2c1_write(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    return false;
}

bool test_i2c1_read(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    return false;
}
#endif


#ifdef HAS_I2C3
bool test_i2c3_write(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    return false;
}
bool test_i2c3_read(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    return false;
}
#endif

