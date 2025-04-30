#include "sw_dac_config.h"

#include <stddef.h>

#include "data_utils.h"

const SwDacConfig_t SwDacConfig[]={
    {
     .num = DAC_I2S_NUM,
     .amplitude = 200,
     .dac_mode=DAC_MODE_SIN,
     .duty_cycle = 50.0,
     .sample_per_second = 50000,
     .frequency = 5555.0,
     .name = "i2s",
     .frame_pattern = CHANNEL_BOTH,
     .sample_bitness = 16,
     .offset = 0,
     .phase_ms = 0.0,
    },
    {
     .num=DAC_GREEN_LED_NUM,
     .amplitude=1.0,
     .dac_mode=DAC_MODE_PWM,
     .sample_per_second=50000,
     .frame_pattern = CHANNEL_BOTH,
     .duty_cycle=50.0,
     .frequency=1.0,
     .name="LedG",
     .offset=0,
     .phase_ms=0.0,
    },
    {
     .num=DAC_RED_LED_NUM,
     .amplitude=1.0,
     .dac_mode=DAC_MODE_PWM,
     .sample_per_second=50000,
     .frame_pattern = CHANNEL_BOTH,
     .duty_cycle=50.0,
     .frequency=2.0,
     .name="LedR",
     .offset=0,
     .phase_ms=0.0,
    },
    {
     .num=DAC_DFT_TEST_NUM,
     .amplitude=1.0,
     .sample_per_second=50000,
     .dac_mode=DAC_MODE_SIN,
     .duty_cycle=50.0,
     .frame_pattern = CHANNEL_BOTH,
     .frequency=200.0,
     .name="DFT_test",
     .offset=0,
     .phase_ms=0.0,
    },
    {
     .num = DAC_MODULATOR_NUM,
     .amplitude = 100.0,
     .dac_mode = DAC_MODE_SIN,
     .duty_cycle = 50.0,
     .frame_pattern = CHANNEL_BOTH,
     .sample_per_second = 50000,
     .frequency=200.0,
     .name="DFT_test",
     .offset=0,
     .phase_ms=0.0,
    },
};

SwDac_t SwDacItem[]={
    {.num = DAC_I2S_NUM,       },
    {.num = DAC_GREEN_LED_NUM, },
    {.num = DAC_RED_LED_NUM,   },
    {.num = DAC_DFT_TEST_NUM,  },
    {.num = DAC_MODULATOR_NUM, },
};

uint32_t sw_dac_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(SwDacConfig);
    uint32_t cnt_ints = ARRAY_SIZE(SwDacItem);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
