#ifndef TEST_ADC_H
#define TEST_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"
#include "adc_types.h"

#define ADC_MEASURE_ACCURACY_VOLTS (0.3)

#ifndef HAS_TEST_ADC
#error "It is needed HAS_TEST_ADC option for that component"
#endif

bool test_adc_read_one(AdcNum_t adc_num, AdcChannel_t chan_num, double exp_voltage);
bool test_adc_types(void);
bool test_adc_board_id(void);

#ifdef HAS_ADC1
bool test_adc1_read(void);
bool test_adc1_read_0v(void);
bool test_adc1_read_3v(void);
bool test_adc1_read_1_5v(void);

#define TEST_SUIT_ADC1                                        \
    {"adc1_read", test_adc1_read},                            \
    {"adc1_read_0v", test_adc1_read_0v},                      \
    {"adc1_read_3v", test_adc1_read_3v},                  \
    {"adc1_read_1_5v", test_adc1_read_1_5v},
#else
#define TEST_SUIT_ADC1
#endif

#ifdef HAS_ADC2
bool test_adc2_read(void);


#define TEST_SUIT_ADC2 \
  {"adc2_read", test_adc2_read},

#else
#define TEST_SUIT_ADC2
#endif

#ifdef HAS_ADC3
bool test_adc3_read(void);

#define TEST_SUIT_ADC3  {"adc3_read", test_adc3_read},
#else
#define TEST_SUIT_ADC3
#endif


#define TEST_SUIT_ADC                   \
    {"adc_types", test_adc_types},      \
    {"adc_board_id", test_adc_board_id},      \
    TEST_SUIT_ADC1                      \
    TEST_SUIT_ADC2                      \
    TEST_SUIT_ADC3

#ifdef __cplusplus
}
#endif

#endif /* TEST_ADC_H */
