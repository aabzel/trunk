#include "quadrature_mixer_config.h"

#include "data_utils.h"

const QuadratureMixerConfig_t QuadratureMixerConfig[] = {
    {
        .num = 1,
        .filter_type = DSP_FILTER_TYPE_IIR,
        .filter_num = {2, 3},
        .filter_order = 400,
        .sample_rate_hz = 1000,
        .cut_off_freq_hz = 200,
        .name = "BpskDecode",
        .valid = true,
    },
};

QuadratureMixerHandle_t QuadratureMixerInstance[] = {
    { .num = 1, .valid = true, },
};

COMPONENT_GET_CNT(QuadratureMixer, quadrature_mixer)

