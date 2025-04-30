#include "local_oscillator_config.h"

#include "common_const.h"
#include "data_utils.h"

const LocalOscillatorConfig_t LocalOscillatorConfig[] = {
    { .num = 5, .valid = true, .frequency_hz = 4092000 , .adc_sample_rate_hz = 16368000 , .phase_deg =  0, .name = "PRN20", },
    { .num = 7, .valid = true, .frequency_hz = 4092000 , .adc_sample_rate_hz = 16368000 , .phase_deg =  0, .name = "PRN20", },
    { .num = 8, .valid = true, .frequency_hz = 4092000 , .adc_sample_rate_hz = 16368000 , .phase_deg =  0, .name = "PRN20", },
    { .num = 9, .valid = true, .frequency_hz = 4092000 , .adc_sample_rate_hz = 16368000 , .phase_deg =  0, .name = "PRN20", },
    { .num = 13, .valid = true, .frequency_hz = 4092000 , .adc_sample_rate_hz = 16368000 , .phase_deg =  0, .name = "PRN13", },
    { .num = 14, .valid = true, .frequency_hz = 4092000 , .adc_sample_rate_hz = 16368000 , .phase_deg =  0, .name = "PRN14", },
    { .num = 20, .valid = true, .frequency_hz = 4092000 , .adc_sample_rate_hz = 16368000 , .phase_deg =  0, .name = "PRN20", },
    { .num = 27, .valid = true, .frequency_hz = 4092000 , .adc_sample_rate_hz = 16368000 , .phase_deg =  0, .name = "PRN20", },
    { .num = 28, .valid = true, .frequency_hz = 4092000 , .adc_sample_rate_hz = 16368000 , .phase_deg =  0, .name = "PRN20", },
    { .num = 30, .valid = true, .frequency_hz = 4092000 , .adc_sample_rate_hz = 16368000 , .phase_deg =  0, .name = "PRN20", },
};

LocalOscillatorHandle_t LocalOscillatorInstance[] = {
    { .num = 5, .valid = true, },
    { .num = 7, .valid = true, },
    { .num = 8, .valid = true, },
    { .num = 9, .valid = true, },
    { .num = 13, .valid = true, },
    { .num = 14, .valid = true, },
    { .num = 20, .valid = true, },
    { .num = 27, .valid = true, },
    { .num = 28, .valid = true, },
    { .num = 30, .valid = true, },
};

uint32_t local_oscillator_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(LocalOscillatorInstance);
    cnt2 = ARRAY_SIZE(LocalOscillatorConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
