#include "quadrature_mixer_config.h"

#include "data_utils.h"
#include "quadrature_mixer_const.h"


const QuadratureMixerConfig_t QuadratureMixerConfig[] = {
    {
        .num = 1,
        .filter_type = DSP_FILTER_TYPE_FIR,
        .filter_num = {2, 3},
        .filter_order = 400,
        .sample_rate_hz = 44100,
        .cut_off_freq_hz = 100,
        .valid = true,
        .name = "BPSK",
    },

    {
        .num = 2,
        .filter_type = DSP_FILTER_TYPE_IIR,
        .filter_num = {5, 6},
        .filter_order = 400,
        .sample_rate_hz = 44100,
        .cut_off_freq_hz = 10,
        .valid = true,
        .name = "PhaseRange",
    },
};

QuadratureMixerHandle_t QuadratureMixerInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
    {
        .num = 2,
        .valid = true,
    },
};

COMPONENT_GET_CNT(QuadratureMixer, quadrature_mixer)

