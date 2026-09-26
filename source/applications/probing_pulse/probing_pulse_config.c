#include "probing_pulse_config.h"

#include "data_utils.h"




const ProbingPulseConfig_t ProbingPulseConfig[] = {
    {
        .num = PROBING_PULSE_NUM_MONO,
        .zonding_impulse_type = PROBING_PULSE_TYPE_MONO,
        .sonar_signal_wav_name = "Mono.wav",
        .name = "Mono",
        .valid = true,
    },

    {
        .num = PROBING_PULSE_NUM_CHIRP,
        .zonding_impulse_type = PROBING_PULSE_TYPE_CHIRP,
        .name = "Chirp",
        .sonar_signal_wav_name = "Chirp.wav",
        .valid = true,
    },

    {
        .zonding_impulse_type = PROBING_PULSE_TYPE_BAKER13,
        .num = PROBING_PULSE_NUM_BARKER,
        .sonar_signal_wav_name = "Barker.wav",
        .valid = true,
        .name = "Barker",
    },

    {
        .zonding_impulse_type = PROBING_PULSE_TYPE_M_SEQ,
        .num = PROBING_PULSE_NUM_M_SEQ,
        .valid = true,
        .sonar_signal_wav_name = "M_Seq.wav",
        .name = "M_Seq",
    },
};

ProbingPulseHandle_t ProbingPulseInstance[] = {
    {        .num = PROBING_PULSE_NUM_MONO,        .valid = true,    },
    {        .num = PROBING_PULSE_NUM_CHIRP,        .valid = true,    },
    {        .num = PROBING_PULSE_NUM_BARKER,        .valid = true,    },
    {        .num = PROBING_PULSE_NUM_M_SEQ,        .valid = true,    },

};


COMPONENT_GET_CNT(ProbingPulse, probing_pulse)


