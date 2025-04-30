#include "test_adc.h"

#include <string.h>

#include "adc_drv.h"
#include "sys_config.h"
#include "unit_test_check.h"

bool test_adc_types(void) {
    LOG_INFO(LG_ADC, "%s()", __FUNCTION__);
    set_log_level(LG_ADC, LOG_LEVEL_DEBUG);
    bool res = true;
    EXPECT_EQ(1, sizeof(AdcNum_t));
    EXPECT_EQ(1, sizeof(AdcResolution_t));
    EXPECT_EQ(1, sizeof(AdcChannel_t));
    set_log_level(LG_ADC, LOG_LEVEL_INFO);
    return res;
}

bool test_adc_board_id(void) {
    LOG_INFO(LG_ADC, "%s()", __FUNCTION__);
    bool res = true;
#ifdef HAS_BOARD_ID
    double volt_id = 0.0;
    EXPECT_TRUE(adc_pad_read_voltage(BoardConfig.volt_id_pad, &volt_id));
    LOG_INFO(SYS, "VoltId: [%f] Volts", volt_id);
    // EXPECT_GR(BoardConfig.volt_id, volt_id);
    // EXPECT_GR(volt_id, BoardConfig.volt_id);

    volt_id = adc_pad_read_voltage_short(BoardConfig.volt_id_pad);
    LOG_INFO(SYS, "VoltId: [%f] Volts", volt_id);
    EXPECT_TRUE(is_double_equal_absolute(volt_id, BoardConfig.volt_id, 0.1));
#endif

    return res;
}

bool test_adc_read_one(AdcNum_t adc_num, AdcChannel_t chan_num, double exp_voltage) {
    LOG_INFO(LG_ADC, "Test ADC%u CH%u Exp %f V", adc_num, chan_num, exp_voltage);
    set_log_level(LG_ADC, LOG_LEVEL_DEBUG);
    bool res = true;
    double read_voltage = 100.0;
    ASSERT_TRUE(adc_channel_read_voltage(adc_num, chan_num, &read_voltage));
    LOG_INFO(LG_ADC, "Read %f V", read_voltage);
    ASSERT_TRUE(is_double_equal_absolute(exp_voltage, read_voltage, ADC_MEASURE_ACCURACY_VOLTS));
    set_log_level(LG_ADC, LOG_LEVEL_INFO);
    return res;
}

#ifdef HAS_ADC1
bool test_adc1_read(void) {
    LOG_INFO(LG_ADC, "%s()", __FUNCTION__);
    bool res = true;
#ifdef ADC_CHAN_WITH_3V
    set_log_level(LG_ADC, LOG_LEVEL_DEBUG);
    double read_voltage = 100.0;
    EXPECT_TRUE(adc_channel_read_voltage(ADC_1, ADC_CHAN_WITH_3V, &read_voltage));
    LOG_INFO(LG_ADC, "Read %f V", read_voltage);
#else
    res = true;
#endif
    set_log_level(LG_ADC, LOG_LEVEL_INFO);
    return res;
}

bool test_adc1_read_0v(void) {
    LOG_INFO(LG_ADC, "%s()", __FUNCTION__);
    bool res = true;
#ifdef ADC_CHAN_WITH_0V
    EXPECT_TRUE(test_adc_read_one(ADC_1, ADC_CHAN_WITH_0V, 0.0));
#else
    res = true;
#endif
    set_log_level(LG_ADC, LOG_LEVEL_INFO);
    return res;
}

bool test_adc1_read_3v(void) {
    LOG_INFO(LG_ADC, "%s()", __FUNCTION__);
    bool res = true;
#ifdef ADC_CHAN_WITH_3V
    EXPECT_TRUE(test_adc_read_one(ADC_1, ADC_CHAN_WITH_3V, 3.0));
#else
    res = true;
#endif
    set_log_level(LG_ADC, LOG_LEVEL_INFO);
    return res;
}

bool test_adc1_read_1_5v(void) {
    LOG_INFO(LG_ADC, "%s()", __FUNCTION__);
    bool res = true;
#ifdef ADC_CHAN_WITH_1_5V
    EXPECT_TRUE(test_adc_read_one(ADC_1, ADC_CHAN_WITH_1_5V, 1.5));
#else
    res = true;
#endif
    set_log_level(LG_ADC, LOG_LEVEL_INFO);
    return res;
}
#endif /*HAS_ADC1*/

#ifdef HAS_ADC2
bool test_adc2_read(void) {
    LOG_INFO(LG_ADC, "%s()", __FUNCTION__);
    bool res = true;
    set_log_level(LG_ADC, LOG_LEVEL_DEBUG);
    set_log_level(LG_ADC, LOG_LEVEL_INFO);
    return res;
}
#endif /*HAS_ADC2*/

#ifdef HAS_ADC3
bool test_adc3_read(void) {
    LOG_INFO(LG_ADC, "%s()", __FUNCTION__);
    bool res = true;
    set_log_level(LG_ADC, LOG_LEVEL_DEBUG);
    set_log_level(LG_ADC, LOG_LEVEL_INFO);
    return res;
}
#endif /*HAS_ADC3*/
