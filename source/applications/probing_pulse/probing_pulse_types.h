#ifndef PROBING_PULSE_TYPES_H
#define PROBING_PULSE_TYPES_H

#include "std_includes.h"
#include "probing_pulse_const.h"

#ifdef HAS_PROBING_PULSE_CUSTOM
#include "probing_pulse_custom_types.h"
#else
#define PROBING_PULSE_CUSTOM_VARIABLES
#endif

#define PROBING_PULSE_COMMON_VARIABLES            \
    char* name;                                   \
    char* sonar_signal_wav_name;                  \
    ProbingPulseType_t zonding_impulse_type;      \
    uint8_t num;                                  \
    uint32_t periods_per_chip;      \
    float amplitude;                \
    float frequency1;  /*carrier_frequency_hz*/     \
    float frequency2;               \
    float signal_duration_s; /* zonding signal duration in [s] */  \
    bool valid;



typedef struct {
    PROBING_PULSE_COMMON_VARIABLES
}ProbingPulseConfig_t;

typedef struct {
    PROBING_PULSE_COMMON_VARIABLES
    bool init;
    uint32_t tx_cnt;
}ProbingPulseHandle_t;


#endif /* PROBING_PULSE_TYPES_H */
