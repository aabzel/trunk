#include "test_pwm_dac.h"

#include "unit_test_check.h"

#include "adc_mcal.h"
#include "none_blocking_pause.h"
#include "pwm_dac.h"
#include "pwm_mcal.h"
#include "time_mcal.h"

#define PWM_DAC_TIME_OUT_MS 3000

bool test_pwm_dac_hash_tables(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(PWM_DAC, LOG_LEVEL_DEBUG);
    bool res = true;

    set_log_level(PWM_DAC, LOG_LEVEL_INFO);
    return res;
}

bool test_pwm_dac_types(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    set_log_level(PWM_DAC, LOG_LEVEL_DEBUG);

    set_log_level(PWM_DAC, LOG_LEVEL_INFO);
    return res;
}

static bool test_pwm_dac_one(uint8_t pwm_dac_num, double set_voltage, double exp_voltage) {
    LOG_INFO(TEST, "%s(),PWM_DAC:%u", __FUNCTION__, pwm_dac_num);
    bool res = true;
    ASSERT_TRUE(pwm_dac_voltage_set(pwm_dac_num, set_voltage));
    ASSERT_TRUE(wait_in_loop_ms(PWM_DAC_TIME_OUT_MS));
    PwmDacHandle_t* PwmDac = PwmDacGetNode(pwm_dac_num);
    ASSERT_NE(NULL, PwmDac)

    AdcChannelHandle_t* AdcChannel = AdcChannelGetNode(PwmDac->adc_channel_num);
    ASSERT_NE(NULL, AdcChannel)
    double voltage_real = AdcChannel->voltage * AdcChannel->scale;

    ASSERT_TRUE(is_double_equal_absolute(exp_voltage, voltage_real, 2.0));
    return res;
}

static bool test_pwm_dac_step_one(uint8_t pwm_dac_num, double duty_step) {
    LOG_INFO(TEST, "%s(),PWM_DAC:%u", __FUNCTION__, pwm_dac_num);
    bool res = true;
    ASSERT_TRUE(pwm_dac_step(pwm_dac_num, 10000.0, 0.0, 100.0, duty_step, 500));
    return res;
}

bool test_pwm_dac_on(void) {
    bool res = true;
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(PWM_DAC, LOG_LEVEL_DEBUG);

    uint32_t cnt = pwm_dac_get_cnt();
    uint8_t i = 0;
    for(i = 1; i <= cnt; i++) {
        LOG_INFO(TEST, "%u:", i);
        ASSERT_TRUE(test_pwm_dac_one(i, 5.0, 0.0));
    }

    set_log_level(PWM_DAC, LOG_LEVEL_INFO);
    return res;
}

bool test_pwm_dac_off(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(PWM_DAC, LOG_LEVEL_DEBUG);
    bool res = true;

    uint32_t cnt = pwm_dac_get_cnt();
    uint8_t i = 0;
    for(i = 1; i <= cnt; i++) {
        LOG_INFO(TEST, "%u:", i);
        ASSERT_TRUE(test_pwm_dac_one(i, 0.0, 11.0));
    }

    set_log_level(PWM_DAC, LOG_LEVEL_INFO);
    return res;
}

bool test_pwm_dac_step(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(PWM_DAC, LOG_LEVEL_DEBUG);
    bool res = true;

    uint32_t cnt = pwm_dac_get_cnt();
    uint8_t i = 0;
    for(i = 1; i <= cnt; i++) {
        LOG_INFO(TEST, "%u:", i);
        ASSERT_TRUE(test_pwm_dac_step_one(i, 5));
    }

    set_log_level(PWM_DAC, LOG_LEVEL_INFO);
    return res;
}
