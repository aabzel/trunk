#ifndef ADC_MCAL_TYPES_H
#define ADC_MCAL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifdef HAS_NRF
#include "nrf_saadc.h"
#include "nrfx_saadc.h"
#endif /*HAS_NRF*/

#include "adc_const.h"
#ifdef USE_HAL_DRIVER
#include "stm32f4xx_hal.h"
#endif

#ifdef HAS_ADC_CUSTOM
#include "adc_custom_types.h"
#endif

#include "gpio_types.h"

typedef struct {
    uint8_t num;
    bool valid;
    AdcResolution_t resolution; /*12bit */
    uint8_t irq_priority;
    double v_ref_voltage;
} AdcConfig_t;

#define ADC_CHANNEL_COMMON_VARIABLES   \
    AdcNum_t num;              \
    bool valid;                \
    Pad_t pad;                 \
    AdcChannel_t channel;

typedef struct {
    ADC_CHANNEL_COMMON_VARIABLES
    char* name;
} AdcChannelConfig_t;

typedef struct {
    ADC_CHANNEL_COMMON_VARIABLES
    double volts;
    double gained_ref_voltage;
    double code_to_volt_factor;
    int32_t code;
    uint32_t read_cnt;
    uint32_t err_cnt;
} AdcChannelHandle_t;

typedef struct  {
    uint8_t num;
    bool valid;
    bool init_done;
    volatile int32_t code;
    volatile bool conv_done;
    uint32_t it_cnt;
    uint32_t err_cnt;
    uint32_t read_cnt;
    uint32_t ref_code;
    uint32_t code_at_vref;
    double v_ref_voltage;
#ifdef HAS_ADC_NRF53
    nrf_saadc_value_t samples[SAADC_CH_NUM];
    nrf_saadc_oversample_t oversampling;
    nrfx_saadc_channel_t ch_cfgs[SAADC_CH_NUM];
    nrfx_saadc_event_handler_t event_handler;
#endif /*HAS_NRF53*/

#ifdef USE_HAL_DRIVER
    ADC_HandleTypeDef adc_h;
#endif /*USE_HAL_DRIVER*/

} AdcHandle_t;

#ifdef __cplusplus
}
#endif

#endif /* ADC_MCAL_TYPES_H  */
