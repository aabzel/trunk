#include "sonar_config.h"

#include <stddef.h>

#include "data_utils.h"
#include "dds_config.h"
#include "physics_const.h"

#ifdef HAS_CORRELATOR_S16
#include "correlator_s16_config.h"
#endif


const SonarConfig_t SonarConfig[] = {
    {
        .num = SONAR_NUM_CHIRP,
#ifdef HAS_CORRELATOR_S16
        .correlator_num = CORRELATOR_S16_MUN_CHIRP_CORRELATION,
#endif
        .dds_num = DDS_NUM_CHIRP,
        .v_sound_m_pes_sec = V_SOUND_M_PES_SEC,
        /*  probing_signal.wav  */
       // .sonar_signal_wav_name = "TxSignal.wav",
        // .sonar_signal_wav_name = "Rec_CHIRP_1000_10000_dt30_A30000.wav",
        // .sonar_signal_wav_name = "Zon_CHIRP_1000_10000_dt70_A400.wav",
        .correlation_file_name = "convolution.csv",
        .signal_duration_s = MSEC_2_SEC(39),
        .amplitude = 400,
#ifdef HAS_SONAR_CORRELATION
        .calc_correlation = true,
#endif
        .periods_per_chip = 6,
        .loopback_audio_num = 1,
        .frequency1 = 2000,
        .frequency2 = 10000,
        .valid = true,
    },
};

SonarHandle_t SonarInstance[] = {
    { .num = SONAR_NUM_CHIRP, .valid = true, },
};

COMPONENT_GET_CNT(Sonar, sonar)
