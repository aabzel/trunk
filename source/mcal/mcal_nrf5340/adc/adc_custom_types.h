#ifndef ADC_NRF_TYPES_H
#define ADC_NRF_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifdef HAS_ADC_CUSTOM
#include "adc_custom_const.h"
#endif

#include "adc_types.h"
#include "gpio_types.h"

#ifdef NRFX_SAADC_ENABLED
#include "nrfx_saadc.h"
#endif

typedef struct {
    AdcChannel_t adc_channel;
    nrf_saadc_input_t adc_channel_nrf;
    Pad_t pad;
    bool valid;
} AdcChannelStaticInfo_t;

typedef struct {
    uint8_t resolution;
    nrf_saadc_resolution_t resolution_nrf;
} AdcResolutionInfo_t;

typedef struct {
    double gain;
    nrf_saadc_gain_t gain_nrf;
} AdcGainInfo_t;

typedef struct {
    double volt;
    nrf_saadc_reference_t ref_nrf;
} AdcRefInfo_t;

#ifdef __cplusplus
}
#endif

#endif /* ADC_NRF_TYPES_H  */
