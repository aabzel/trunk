#ifndef TEST_I2C_H
#define TEST_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"

#ifndef HAS_TEST_I2C
//#error "It is needed HAS_TEST_I2C option for that component"
#endif

bool test_i2c_types(void);

#ifdef HAS_I2C1
bool test_i2c1_read(void);
bool test_i2c1_write(void);

#define TEST_SUIT_I2C1 {"i2c1_write", test_i2c1_write}, {"i2c1_read", test_i2c1_read},
#else
#define TEST_SUIT_I2C1
#endif

#ifdef HAS_I2C2
bool test_i2c2_read(void);
bool test_i2c2_write(void);
bool test_i2c2_write_string(void);

#define TEST_SUIT_I2C2                                                                                                \
    {"i2c2_write", test_i2c2_write}, {"i2c2_write_string", test_i2c2_write_string}, {"i2c2_read", test_i2c2_read},
#else
#define TEST_SUIT_I2C2
#endif

#ifdef HAS_I2C3
bool test_i2c3_read(void);
bool test_i2c3_write(void);

#define TEST_SUIT_I2C3 {"i2c3_write", test_i2c3_write}, {"i2c3_read", test_i2c3_read},
#else
#define TEST_SUIT_I2C3
#endif

#ifdef HAS_I2C4
bool test_i2c4_read(void);
bool test_i2c4_write(void);

#define TEST_SUIT_I2C4 {"i2c4_write", test_i2c4_write}, {"i2c4_read", test_i2c4_read},
#else
#define TEST_SUIT_I2C4
#endif

#ifdef HAS_I2C5
bool test_i2c5_read(void);
bool test_i2c5_write(void);

#define TEST_SUIT_I2C5 {"i2c5_write", test_i2c5_write}, {"i2c3_read", test_i2c5_read},
#else
#define TEST_SUIT_I2C5
#endif

#define TEST_SUIT_I2C                                                                                                 \
    {"i2c_types", test_i2c_types}, \
    TEST_SUIT_I2C1                                                                                                    \
    TEST_SUIT_I2C2                                                                                                    \
    TEST_SUIT_I2C3 \
    TEST_SUIT_I2C4 \
    TEST_SUIT_I2C5

#ifdef __cplusplus
}
#endif

#endif /* TEST_I2C_H */
