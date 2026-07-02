#ifndef TEST_I2C_FSM_H
#define TEST_I2C_FSM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "test_hw_dep_check.h"

#ifndef HAS_TEST_I2C_FSM
//#error "It is needed HAS_TEST_I2C_FSM option for that component"
#endif

bool test_i2c_fsm_write_byte_one(uint8_t num,
                                 uint8_t chip_addr,
                                 uint8_t reg_addr,
                                 uint8_t reg_value );

#ifdef HAS_I2C1
bool test_i2c_fsm1_check_asic_ack(void);
bool test_i2c_fsm1_check_asic_nak(void);
bool test_i2c_fsm1_read(void);
bool test_i2c_fsm1_read_byte(void);
bool test_i2c_fsm1_write_byte(void);

#define TEST_SUIT_I2C_FSM1                                              \
    {"i2c_fsm1_check_asic_ack", test_i2c_fsm1_check_asic_ack},    \
    {"i2c_fsm1_check_asic_nak", test_i2c_fsm1_check_asic_nak},    \
    {"i2c_fsm1_read_byte", test_i2c_fsm1_read_byte},                    \
    {"i2c_fsm1_write_byte", test_i2c_fsm1_write_byte},                    \
    {"i2c_fsm1_read", test_i2c_fsm1_read},

#else
#define TEST_SUIT_I2C_FSM1
#endif

#ifdef HAS_I2C2
bool test_i2c_fsm2_read(void);
bool test_i2c_fsm2_empty(void);
bool test_i2c_fsm2_read_word(void);
bool test_i2c_fsm2_check_asic_ack(void);
bool test_i2c_fsm2_check_asic_nak(void);
bool test_i2c_fsm2_write_word(void);

#define TEST_SUIT_I2C_FSM2                           \
    {"i2c_fsm2_empty", test_i2c_fsm2_empty},    \
    {"i2c_fsm2_check_asic_ack", test_i2c_fsm2_check_asic_ack},    \
    {"i2c_fsm2_check_asic_nak", test_i2c_fsm2_check_asic_nak},    \
    {"i2c_fsm2_write_word", test_i2c_fsm2_write_word},    \
    {"i2c_fsm2_read_word", test_i2c_fsm2_read_word}, \
    {"i2c_fsm2_read", test_i2c_fsm2_read},
#else
#define TEST_SUIT_I2C_FSM2
#endif

#ifdef HAS_I2C3
bool test_i2c_fsm3_read(void);
bool test_i2c_fsm3_write(void);

#define TEST_SUIT_I2C_FSM3 {"i2c_fsm3_write", test_i2c_fsm3_write}, {"i2c_fsm3_read", test_i2c_fsm3_read},
#else
#define TEST_SUIT_I2C_FSM3
#endif

#ifdef HAS_I2C4
bool test_i2c4_read(void);
bool test_i2c4_write(void);

#define TEST_SUIT_I2C_FSM4 {"i2c_fsm4_write", test_i2c4_write}, {"i2c_fsm4_read", test_i2c4_read},
#else
#define TEST_SUIT_I2C_FSM4
#endif


#define TEST_SUIT_I2C_FSM                                                                                                 \
    TEST_SUIT_I2C_FSM1                                                                                                    \
    TEST_SUIT_I2C_FSM2                                                                                                    \
    TEST_SUIT_I2C_FSM3                  \
    TEST_SUIT_I2C_FSM4

#ifdef __cplusplus
}
#endif

#endif /* TEST_I2C_FSM_H */
