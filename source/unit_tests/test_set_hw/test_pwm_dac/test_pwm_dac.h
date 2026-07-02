#ifndef TEST_PWM_DAC_H
#define TEST_PWM_DAC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "test_hw_dep_check.h"

#ifndef HAS_TEST_PWM_DAC
#error "+HAS_PWM_DAC_TESTS"
#endif

bool test_pwm_dac_off(void);
bool test_pwm_dac_on(void);
bool test_pwm_dac_step(void);
bool test_pwm_dac_types(void);
bool test_pwm_dac_hash_tables(void);

#define TEST_SUIT_PWM_DAC    \
    {"pwm_dac_types", test_pwm_dac_types},                             \
    {"pwm_dac_hash_tables", test_pwm_dac_hash_tables},                \
    {"pwm_dac_step", test_pwm_dac_step},          \
    {"pwm_dac_off", test_pwm_dac_off},          \
    {"pwm_dac_on", test_pwm_dac_on},            \

#ifdef __cplusplus
}
#endif

#endif /* TEST_PWM_DAC_H */
