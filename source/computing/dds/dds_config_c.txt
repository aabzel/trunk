#include "dds_config.h"

#include <stddef.h>

#include "time_mcal.h"
#include "data_utils.h"


#define DDS_SLOC_AMP 50.0
static SampleType_t SampleArray[DDS_MAX_SAMPLE_ARRAY] = {0};
#define WAV_FREQ_HZ 3333.0
const DdsConfig_t DdsConfig[] = {
    {
        .num = DDS_CHIRP_NUM,
        .sample_array = SampleArray ,
        .array_size = ARRAY_SIZE(SampleArray),
        .signal_diration_s = MSEC_2_SEC(30),
        .amplitude = 30000,
        .sample_per_second = 44100,
        .sample_bitness = 16,
        .dds_mode = DDS_MODE_CHIRP,
        .player =  DDS_PLAYER_CSV_FILE,
        .duty_cycle = 50.0,
        .frame_pattern = CHANNEL_MONO,
        .frequency = 450.0,
        .frequency2 = 10000.0,
        .name = "Chirp",
        .offset = 0,
        .phase_ms = 0.0,
        .valid = true,
    },
    {
        .sample_array = SampleArray ,
        .array_size = ARRAY_SIZE(SampleArray),
        .num = DDS_I2S_NUM,
        .amplitude = 200,
        .signal_diration_s = MSEC_2_SEC(10),
        .dds_mode = DDS_MODE_SIN,
        .duty_cycle = 50.0,
        .sample_per_second = 50000,
        .frequency = 5555.0,
        .name = "i2s",
        .frame_pattern = CHANNEL_BOTH,
        .sample_bitness = 16,
        .player =  DDS_PLAYER_CSV_FILE,
        .offset = 0,
        .phase_ms = 0.0,
        .valid = true,
    },
    {
        .sample_array = SampleArray ,
        .array_size = ARRAY_SIZE(SampleArray),
        .signal_diration_s = MSEC_2_SEC(10),
        .num = DDS_GREEN_LED_NUM,
        .amplitude = 1.0,
        .dds_mode = DDS_MODE_PWM,
        .sample_bitness = 16,
        .sample_per_second = 50000,
        .player =  DDS_PLAYER_CSV_FILE,
        .frame_pattern = CHANNEL_BOTH,
        .duty_cycle = 50.0,
        .frequency = 1.0,
        .name = "LedG",
        .offset = 0,
        .phase_ms = 0.0,
        .valid = true,
    },
    {
        .sample_array = SampleArray ,
        .array_size = ARRAY_SIZE(SampleArray),
        .num = DDS_RED_LED_NUM,
        .amplitude = 1.0,
        .dds_mode = DDS_MODE_PWM,
        .sample_bitness = 16,
        .signal_diration_s = MSEC_2_SEC(10),
        .sample_per_second = 50000,
        .frame_pattern = CHANNEL_BOTH,
        .player =  DDS_PLAYER_CSV_FILE,
        .duty_cycle = 50.0,
        .frequency = 2.0,
        .name = "LedR",
        .offset = 0,
        .phase_ms = 0.0,
        .valid = true,
    },
    {
        .sample_array = SampleArray ,
        .array_size = ARRAY_SIZE(SampleArray),
        .num = DDS_DFT_TEST_NUM,
        .amplitude = 1.0,
        .sample_bitness = 16,
        .sample_per_second = 50000,
        .signal_diration_s = MSEC_2_SEC(10),
        .dds_mode = DDS_MODE_SIN,
        .player =  DDS_PLAYER_CSV_FILE,
        .duty_cycle = 50.0,
        .frame_pattern = CHANNEL_BOTH,
        .frequency = 200.0,
        .name = "DFT_test",
        .offset = 0,
        .phase_ms = 0.0,
        .valid = true,
    },
    {
        .sample_array = SampleArray ,
        .array_size = ARRAY_SIZE(SampleArray),
        .num = DDS_MODULATOR_NUM,
        .amplitude = 100.0,
        .sample_bitness = 16,
        .dds_mode = DDS_MODE_SIN,
        .player =  DDS_PLAYER_CSV_FILE,
        .signal_diration_s = MSEC_2_SEC(10),
        .duty_cycle = 50.0,
        .frame_pattern = CHANNEL_BOTH,
        .sample_per_second = 50000,
        .frequency = 200.0,
        .name = "DFT_test",
        .offset = 0,
        .phase_ms = 0.0,
        .valid = true,
    },
    {
        .sample_array = SampleArray ,
        .array_size = ARRAY_SIZE(SampleArray),
        .num = DDS_FFT_TEST_NUM,
        .amplitude = 1.0,
        .sample_bitness = 16,
        .player =  DDS_PLAYER_CSV_FILE,
        .sample_per_second = 50000,
        .dds_mode = DDS_MODE_SIN,
        .signal_diration_s = MSEC_2_SEC(10),
        .duty_cycle = 50.0,
        .frame_pattern = CHANNEL_BOTH,
        .frequency = 200.0,
        .name = "DFT_test",
        .offset = 0,
        .phase_ms = 0.0,
        .valid = true,
    },



    {
        .num = DDS_WAV_CH1,
        .sample_array = SampleArray ,
        .array_size = ARRAY_SIZE(SampleArray),
        .amplitude = DDS_SLOC_AMP,
        .sample_bitness = 16,
        .player =  DDS_PLAYER_WAV_FILE,
        .sample_per_second = 96000,
        .dds_mode = DDS_MODE_SIN,
        .signal_diration_s = MSEC_2_SEC(10),
        .duty_cycle = 50.0,
        .frame_pattern = CHANNEL_MONO,
        .frequency = WAV_FREQ_HZ,
        .name = "WAV1",
        .offset = 0,
        .phase_ms = 0.0,
        .valid = true,
    },

    {
        .num = DDS_WAV_CH2,
        .sample_array = SampleArray ,
        .array_size = ARRAY_SIZE(SampleArray),
        .amplitude = DDS_SLOC_AMP,
        .sample_bitness = 16,
        .player =  DDS_PLAYER_WAV_FILE,
        .sample_per_second = 96000,
        .dds_mode = DDS_MODE_SIN,
        .signal_diration_s = MSEC_2_SEC(10),
        .duty_cycle = 50.0,
        .frame_pattern = CHANNEL_MONO,
        .frequency = WAV_FREQ_HZ,
        .name = "WAV2",
        .offset = 0,
        .phase_ms = USEC_2_MSEC(64.0),
        .valid = true,
    },

};

DdsHandle_t DdsInstance[] = {
    {
        .num = DDS_I2S_NUM,
        .valid = true,
    },
    {
        .num = DDS_GREEN_LED_NUM,
        .valid = true,
    },
    {
        .num = DDS_RED_LED_NUM,
        .valid = true,
    },
    {
        .num = DDS_DFT_TEST_NUM,
        .valid = true,
    },
    {
        .num = DDS_MODULATOR_NUM,
        .valid = true,
    },
    {
        .num = DDS_FFT_TEST_NUM,
        .valid = true,
    },
    {
        .num = DDS_CHIRP_NUM,
        .valid = true,
    },
    {
        .num = DDS_WAV_CH1,
        .valid = true,
    },
    {
        .num = DDS_WAV_CH2,
        .valid = true,
    },
};

uint32_t dds_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(DdsConfig);
    uint32_t cnt_ints = ARRAY_SIZE(DdsInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
