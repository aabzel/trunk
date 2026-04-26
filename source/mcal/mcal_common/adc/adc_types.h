#ifndef ADC_MCAL_TYPES_H
#define ADC_MCAL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "adc_const.h"
#include "lib_iqueue.h"
#include "gpio_types.h"
#include "mcal_const.h"

#ifdef HAS_ADC_CUSTOM
#include "adc_custom_types.h"
#else
#define ADC_CUSTOM_VARIABLES
#endif

#define ADC_COMMON_VARIABLES                                              \
    uint8_t num;                                                          \
    char * name ;                                                         \
    uint16_t * RxSamples;                                                 \
    MoveMode_t move_mode;                                                 \
    uint8_t irq_priority;                                                 \
    uint32_t RxSamplesCnt;                                                \
    uint16_t * SampleFifoMem;                                             \
    uint32_t SampleFifoMemCnt;                                            \
    AdcExternalTriggerSource_t trigger_source;                            \
    bool valid;                                                           \
    float v_ref_voltage;                                                  \
    AdcResolution_t resolution; /*12bit */

typedef struct {
    ADC_COMMON_VARIABLES
} AdcConfig_t;

#define ADC_ISR_VARIABLES                                                                                              \
    volatile uint32_t it_cnt;                                                                                          \
    volatile bool overflow;                                                                                            \
    volatile bool it;                                                                                                  \
    volatile bool preempt_chan_conv_end;                                                                               \
    volatile bool data_valid;                                                                                          \
    volatile bool level_out_window_done;                                                                                          \
    volatile bool preempt_chan_conv_start;                                                                             \
    volatile bool ready;                                                                                               \
    volatile bool is_idle;                                                                                             \
    volatile bool half_cplt_done;                                                                                       \
    volatile bool error_done;                                                                                       \
    volatile bool chan_conv_end;                                                                                       \
    volatile bool conv_done;                                                                                           \
    volatile bool conversion_start;                                                                                    \
    volatile bool vmor;                                                                                                \
    volatile bool fetch_done; /*sample extracted*/                                                                     \
    volatile uint32_t overflow_cnt;                                                                                    \
    volatile uint32_t half_cplt_done_cnt;                                                                                   \
    volatile uint32_t vmor_flag_cnt;                                                                                   \
    volatile uint32_t preempt_chan_conv_end_cnt;                                                                       \
    volatile uint32_t preempt_chan_conv_start_cnt;                                                                     \
    volatile uint32_t conversion_start_cnt;                                                                            \
    volatile uint32_t level_out_window_done_cnt;                                                                            \
    volatile uint32_t error_done_cnt;                                                                            \
    volatile uint32_t ready_cnt;                                                                                       \
    volatile uint32_t chan_conv_end_cnt;

typedef struct {
    ADC_COMMON_VARIABLES
    ADC_ISR_VARIABLES
    ADC_CUSTOM_VARIABLES

    uint32_t channel_cur;
    uint8_t cur_channel_node;
    bool init_done;
    uint32_t code;
    iqueue_t iQueue;
    uint32_t max_code; /*code at Vref*/
    uint32_t err_cnt;
    uint32_t spin_cnt;
    uint32_t read_cnt;
} AdcHandle_t;

#ifdef __cplusplus
}
#endif

#endif /* ADC_MCAL_TYPES_H  */
