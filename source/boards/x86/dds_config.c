#include "dds_config.h"

#include <stddef.h>

#include "time_mcal.h"
#include "data_utils.h"

#define DDS_SLOC_AMP 50.0
static SampleType_t SampleArray[DDS_MAX_SAMPLE_ARRAY] = {0};

#define WAV_FREQ_HZ 3333.0

#define DDS_CONFIG_CHIRP                                     \
    {                                                        \
        .m_seq_num = 1,                                      \
        .num = DDS_NUM_CHIRP,                                \
        .dds_mode = DDS_MODE_CHIRP,                          \
        .sample_array = SampleArray ,                        \
        .sample_cnt = ARRAY_SIZE(SampleArray),               \
        .total_sample_cnt = ARRAY_SIZE(SampleArray) ,        \
        .signal_diration_s = MSEC_2_SEC(50),                 \
        .amplitude = 1000,                                   \
        .sample_per_second = 48000,                          \
        .sample_bitness = 16,                                \
        .player =  DDS_PLAYER_CSV_FILE,                      \
        .duty_cycle = 50.0,                                  \
        .frame_pattern = CHANNEL_MONO,                       \
        .frequency = 450.0,                                  \
        .frequency2 = 10000.0,                               \
        .name = "Chirp",                                     \
        .offset = 0,                                         \
        .phase_ms = 0.0,                                     \
        .valid = true,                                       \
    },

const DdsConfig_t DdsConfig[] = {
        DDS_CONFIG_CHIRP
    {
        .num = DDS_NUM_SIN,
        .frame_pattern = CHANNEL_BOTH,
        .m_seq_num = 1,
        .sample_bitness = 16,
        .name = "TestTone",
        .dds_mode = DDS_MODE_SIN,
        .player =  DDS_PLAYER_WAV_FILE,
        .sample_per_second = 96000,
        .signal_diration_s = 5.0f,
        .frequency = 1000.0,
        .amplitude = 1000,
        .total_sample_cnt = ARRAY_SIZE(SampleArray) ,
        .sample_array = SampleArray ,
        .sample_cnt = ARRAY_SIZE(SampleArray),
        .duty_cycle = 50.0,
        .offset = 0,
        .phase_ms = 0.0,
        .valid = true,
    },
#ifdef HAS_LED
    {
        .sample_array = SampleArray ,
        .sample_cnt = ARRAY_SIZE(SampleArray),
        .total_sample_cnt = ARRAY_SIZE(SampleArray) ,
        .signal_diration_s = MSEC_2_SEC(10),
        .num = DDS_NUM_GREEN_LED,
        .m_seq_num = 1,
        .amplitude = 1.0,
        .dds_mode = DDS_MODE_PWM,
        .sample_bitness = 16,
        .sample_per_second = 48000,
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
        .sample_cnt = ARRAY_SIZE(SampleArray),
        .total_sample_cnt = ARRAY_SIZE(SampleArray) ,
        .num = DDS_NUM_RED_LED,
        .amplitude = 1.0,
        .m_seq_num = 1,
        .dds_mode = DDS_MODE_PWM,
        .sample_bitness = 16,
        .signal_diration_s = MSEC_2_SEC(10),
        .sample_per_second = 48000,
        .frame_pattern = CHANNEL_BOTH,
        .player =  DDS_PLAYER_CSV_FILE,
        .duty_cycle = 50.0,
        .frequency = 2.0,
        .name = "LedR",
        .offset = 0,
        .phase_ms = 0.0,
        .valid = true,
    },
#endif
    {
        .sample_array = SampleArray ,
        .sample_cnt = ARRAY_SIZE(SampleArray),
        .total_sample_cnt = ARRAY_SIZE(SampleArray) ,
        .num = DDS_NUM_DFT_TEST,
        .amplitude = 1.0,
        .m_seq_num = 1,
        .sample_bitness = 16,
        .sample_per_second = 48000,
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
        .sample_cnt = ARRAY_SIZE(SampleArray),
        .total_sample_cnt = ARRAY_SIZE(SampleArray) ,
        .num = DDS_NUM_MODULATOR,
        .amplitude = 100.0,
        .m_seq_num = 1,
        .sample_bitness = 16,
        .dds_mode = DDS_MODE_SIN,
        .player =  DDS_PLAYER_CSV_FILE,
        .signal_diration_s = MSEC_2_SEC(10),
        .duty_cycle = 50.0,
        .frame_pattern = CHANNEL_BOTH,
        .sample_per_second = 48000,
        .frequency = 200.0,
        .name = "DFT_test",
        .offset = 0,
        .phase_ms = 0.0,
        .valid = true,
    },
    {
        .sample_array = SampleArray ,
        .sample_cnt = ARRAY_SIZE(SampleArray),
        .total_sample_cnt = ARRAY_SIZE(SampleArray) ,
        .num = DDS_NUM_FFT_TEST,
        .amplitude = 1.0,
        .sample_bitness = 16,
        .m_seq_num = 1,
        .player =  DDS_PLAYER_CSV_FILE,
        .sample_per_second = 48000,
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
        .num = DDS_NUM_WAV_CH1,
        .sample_array = SampleArray ,
        .m_seq_num = 1,
        .sample_cnt = ARRAY_SIZE(SampleArray),
        .total_sample_cnt = ARRAY_SIZE(SampleArray) ,
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
        .num = DDS_NUM_WAV_CH2,
        .sample_per_second = 96000,
        .sample_array = SampleArray ,
        .sample_cnt = ARRAY_SIZE(SampleArray),
        .total_sample_cnt = ARRAY_SIZE(SampleArray) ,
        .amplitude = DDS_SLOC_AMP,
        .sample_bitness = 16,
        .m_seq_num = 1,
        .player =  DDS_PLAYER_WAV_FILE,
        .dds_mode = DDS_MODE_SIN,
        .signal_diration_s = MSEC_2_SEC(10),
        .duty_cycle = 50.0,
        .frame_pattern = CHANNEL_BOTH,
        .frequency = WAV_FREQ_HZ,
        .name = "WAV2",
        .offset = 0,
        .phase_ms = USEC_2_MSEC(64.0),
        .valid = true,
    },

};

DdsHandle_t DdsInstance[] = {
    {
        .num = DDS_NUM_SIN,
        .valid = true,
    },
#ifdef HAS_LED
    {
        .num = DDS_NUM_GREEN_LED,
        .valid = true,
    },
    {
        .num = DDS_NUM_RED_LED,
        .valid = true,
    },
#endif
    {
        .num = DDS_NUM_DFT_TEST,
        .valid = true,
    },
    {
        .num = DDS_NUM_MODULATOR,
        .valid = true,
    },
    {
        .num = DDS_NUM_FFT_TEST,
        .valid = true,
    },
    {
        .num = DDS_NUM_CHIRP,
        .valid = true,
    },
    {
        .num = DDS_NUM_WAV_CH1,
        .valid = true,
    },
    {
        .num = DDS_NUM_WAV_CH2,
        .valid = true,
    },
};

COMPONENT_GET_CNT(Dds, dds)

