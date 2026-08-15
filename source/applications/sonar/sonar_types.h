#ifndef NOR_SONAR_TYPES_H
#define NOR_SONAR_TYPES_H

#include "std_includes.h"
#include "data_types.h"
#include "sonar_const.h"

#ifdef HAS_PROBING_PULSE
#include "probing_pulse_const.h"
#endif

typedef struct {
    float signal_duration_s; /* zonding signal duration in [s] */
    float frequency1; /*carrier_frequency_hz*/
    float frequency2;
    float amplitude;
} SonarChirpParam_t;

typedef struct {
    //int64_t abs_correlation;
    int64_t positive_correlation;
    int64_t negative_correlation;
    uint32_t sample ;
    float up_time_s;
    float correlation_positive_log;
    float correlation_negative_log;
    int64_t correlation;
    float dist_m;
} SonarCorrelationInfo_t;


//    char* sonar_signal_wav_name;
//    float chirp_duration_s;

#ifdef HAS_PROBING_PULSE
#define PROBING_PULSE_VARIABLES                   \
    ProbingPulseType_t zonding_impulse_type;
#else
#define PROBING_PULSE_VARIABLES
#endif


#define SONAR_COMMON_VARIABLES      \
    uint8_t m_seq_num;              \
    PROBING_PULSE_VARIABLES         \
    uint8_t num;                    \
    bool calc_correlation;          \
    uint32_t periods_per_chip;      \
    uint8_t loopback_audio_num;     \
    uint8_t correlator_num;         \
    char* correlation_file_name;    \
    float v_sound_m_pes_sec;        \
    float signal_duration_s; /* zonding signal duration in [s] */  \
    float amplitude;                \
    float frequency1;  /*carrier_frequency_hz*/     \
    float frequency2;               \
    uint8_t dds_num;                \
    bool valid;

typedef struct {
    SONAR_COMMON_VARIABLES
} SonarConfig_t;

typedef struct {
    SONAR_COMMON_VARIABLES
    bool init;
    char reflected_radar_signal_wav[80];
    char sonar_signal_wav[80];
    char correlation_file[80];
    SonarState_t state;
    uint32_t next_play;
    uint32_t start_ms;
    uint32_t conv_sn;
    uint32_t play_cnt;
    uint32_t chirp_sn;
} SonarHandle_t;

#endif /* NOR_SONAR_TYPES_H */
