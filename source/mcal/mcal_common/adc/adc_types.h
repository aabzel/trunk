#ifndef ADC_MCAL_TYPES_H
#define ADC_MCAL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "adc_const.h"
#include "gpio_types.h"

#ifdef HAS_ADC_CUSTOM
#include "adc_custom_types.h"
#endif

#define ADC_CHANNEL_COMMON_VARIABLES                       \
    uint8_t num;                                           \
    AdcNum_t adc_num; /*ADC number*/                       \
    uint8_t sequence;                                      \
    float scale; /*1.0/volt_div*/                          \
    bool valid;                                            \
    Pad_t Pad;                                             \
    AdcChannel_t channel;                                  \
    char* name;

typedef struct {
    ADC_CHANNEL_COMMON_VARIABLES
} AdcChannelConfig_t;

typedef struct {
    ADC_CHANNEL_COMMON_VARIABLES
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

#define ADC_COMMON_VARIABLES                                                                                           \
    uint8_t num;                                                                                                       \
    bool valid;                                                                                                        \
    AdcResolution_t resolution; /*12bit */                                                                             \
    float v_ref_voltage;

typedef struct {
    ADC_COMMON_VARIABLES
    uint8_t irq_priority;
} AdcConfig_t;

#define ADC_ISR_VARIABLES                                                                                              \
    volatile uint32_t it_cnt;                                                                                          \
    volatile bool overflow;                                                                                            \
    volatile bool it;                                                                                                  \
    volatile bool preempt_chan_conv_end;                                                                               \
    volatile bool data_valid;                                                                                          \
    volatile bool preempt_chan_conv_start;                                                                             \
    volatile bool ready;                                                                                               \
    volatile bool is_idle;                                                                                             \
    volatile bool chan_conv_end;                                                                                       \
    volatile bool conv_done;                                                                                           \
    volatile bool conversion_start;                                                                                    \
    volatile bool vmor;                                                                                                \
    volatile bool fetch_done; /*sample extracted*/                                                                     \
    volatile uint32_t overflow_cnt;                                                                                    \
    volatile uint32_t vmor_flag_cnt;                                                                                   \
    volatile uint32_t preempt_chan_conv_end_cnt;                                                                       \
    volatile uint32_t preempt_chan_conv_start_cnt;                                                                     \
    volatile uint32_t conversion_start_cnt;                                                                            \
    volatile uint32_t ready_cnt;                                                                                       \
    volatile uint32_t chan_conv_end_cnt;

typedef struct {
    ADC_COMMON_VARIABLES
    ADC_ISR_VARIABLES
    ADC_CUSTOM_VARIABLES

    AdcChannel_t channel_cur;
    uint8_t cur_channel_node;
    bool init_done;
    uint32_t code;
    uint32_t max_code; /*code at Vref*/
    uint32_t err_cnt;
    uint32_t spin_cnt;
    uint32_t read_cnt;
} AdcHandle_t;

#ifdef __cplusplus
}
#endif

#endif /* ADC_MCAL_TYPES_H  */
