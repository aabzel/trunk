#include "phase_detector_config.h"

#include "data_utils.h"

const PhaseDetectorConfig_t PhaseDetectorConfig[] = {
   {
    .num = 1,
    .quadrature_mixer_num = 2,
    .filter_order = 800,
    .speed_of_sound_m_per_s = 331.0,
    .signal_frequency_hz = 700.0,
    .cut_off_frequency_hz = 5.0,
    .sample_freq_hz = 44100,
    .valid = true,
   },
};

PhaseDetectorHandle_t PhaseDetectorInstance[]={
     {.num = 1, .valid = true,},
};

uint32_t phase_detector_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(PhaseDetectorInstance);
    cnt2 = ARRAY_SIZE(PhaseDetectorConfig);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
}
