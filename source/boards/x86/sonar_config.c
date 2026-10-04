#include "sonar_config.h"

#include <stddef.h>

#include "data_utils.h"
#include "dds_config.h"
#include "correlator_s16_config.h"

SonarSrcDataInfo_t SonarSrcData[SONAR_MAX_REC_TO_ACCUM] = {
    { .valid = true, .echoRecord = "Rx_1_UT6307us.wav",  .txPulse = "RefChirpTD20msFs4345Fe7655A2kSF48k.wav", .num = 1,  .position = { .x=0, .y=0,}, },
    { .valid = true, .echoRecord = "Rx_2_UT11654us.wav", .txPulse = "RefChirpTD20msFs4345Fe7655A2kSF48k.wav", .num = 2,  .position = { .x=0, .y=0,}, },
    { .valid = true, .echoRecord = "Rx_3_UT17001us.wav", .txPulse = "RefChirpTD20msFs4345Fe7655A2kSF48k.wav", .num = 3,  .position = { .x=0, .y=0,}, },
    { .valid = true, .echoRecord = "Rx_4_UT22346us.wav", .txPulse = "RefChirpTD20msFs4345Fe7655A2kSF48k.wav", .num = 4,  .position = { .x=0, .y=0,}, },
    { .valid = true, .echoRecord = "Rx_5_UT27695us.wav", .txPulse = "RefChirpTD20msFs4345Fe7655A2kSF48k.wav", .num = 5,  .position = { .x=0, .y=0,}, },
    { .valid = true, .echoRecord = "Rx_6_UT33044usGood.wav", .txPulse = "RefChirpTD20msFs4345Fe7655A2kSF48k.wav", .num = 6,  .position = { .x=0, .y=0,}, },
    { .valid = true, .echoRecord = "Rx_7_UT38393us.wav", .txPulse = "RefChirpTD20msFs4345Fe7655A2kSF48k.wav", .num = 7,  .position = { .x=0, .y=0,}, },
    { .valid = true, .echoRecord = "Rx_8_UT48776us.wav", .txPulse = "RefChirpTD20msFs4345Fe7655A2kSF48k.wav", .num = 8,  .position = { .x=0, .y=0,}, },
};


const SonarConfig_t SonarConfig[] = {
    {
        .zonding_impulse_type = PROBING_PULSE_TYPE_M_SEQ,
        .dds_num = DDS_NUM_CHIRP,
        .num = SONAR_NUM_CHIRP,
        .correlator_num = CORRELATOR_S16_MUN_CHIRP_CORRELATION,
        //.sonar_signal_wav_name = "sonar_signal.wav",
        .correlation_file_name = "correlation.csv",
        .signal_duration_s = MSEC_2_SEC(39),
        .periods_per_chip = 6,
        .amplitude = 400,
        .tx_phase_s = 0.05,
        .tx_duration_s = 1.7,
        .loopback_audio_num = 1,
        .v_sound_m_pes_sec = 331,
        .frequency1 = 450,
        .frequency2 = 10000,
        .calc_correlation = false,
        .valid = true,
    },
};

#if 0
uint32_t sonar_src_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(SonarSrcData);
    return cnt;
}
#endif

SonarHandle_t SonarInstance[] = {
    { .num = SONAR_NUM_CHIRP, .valid = true, },
};

COMPONENT_GET_CNT(Sonar, sonar)
