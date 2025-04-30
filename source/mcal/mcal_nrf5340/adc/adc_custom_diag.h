#ifndef ADC_NRF_DIAG_H
#define ADC_NRF_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "nrf_saadc.h"

bool adc_custom_diag(const char* const keyWord1, const char* const keyWord2);
const char* NrfResolution2Str(nrf_saadc_resolution_t code);
const char* NrfInput2Str(nrf_saadc_input_t code);
const char* NrfOversample2Str(nrf_saadc_oversample_t code);
const char* NrfResistor2Str(nrf_saadc_resistor_t code);
const char* NrfGain2Str(nrf_saadc_gain_t code);
const char* NrfRef2Str(nrf_saadc_reference_t code);
const char* NrfTAck2Str(nrf_saadc_acqtime_t code);
const char* NrfMode2Str(nrf_saadc_mode_t code);
const char* NrfBurst2Str(nrf_saadc_burst_t code);

#endif /* ADC_NRF_DIAG_H  */
