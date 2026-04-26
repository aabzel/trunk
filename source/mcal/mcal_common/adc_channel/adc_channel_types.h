#ifndef ADC_CHANNEL_MCAL_TYPES_H
#define ADC_CHANNEL_MCAL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "adc_channel_const.h"
#include "adc_const.h"
#include "gpio_types.h"

#ifdef HAS_ADC_CHANNEL_CUSTOM
#include "adc_channel_custom_types.h"
#else
#define ADC_CHANNEL_CUSTOM_VARIABLES
#endif

#define ADC_CHANNEL_COMMON_VARIABLES                       \
    uint8_t num;                                           \
    AdcNum_t adc_num; /*ADC number*/                       \
    AdcChannel_t channel;                                  \
    uint8_t sequence;                                      \
    float scale; /*   1.0/volt_div   */                    \
    bool valid;                                            \
    Pad_t Pad;                                             \
    char* name;

typedef struct {
    ADC_CHANNEL_COMMON_VARIABLES
} AdcChannelConfig_t;

typedef struct {
    ADC_CHANNEL_COMMON_VARIABLES
    ADC_CHANNEL_CUSTOM_VARIABLES
    float voltage;
    float voltage_real;
    bool new_val;
    bool is_reading;
    uint32_t code;
    uint32_t read_cnt;
    uint32_t err_cnt;
    uint32_t spin_cnt;
    bool init_done;
} AdcChannelHandle_t;


#ifdef __cplusplus
}
#endif

#endif /* ADC_MCAL_TYPES_H  */
