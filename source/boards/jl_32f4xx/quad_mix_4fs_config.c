#include "quad_mix_4fs_config.h"

#include "data_utils.h"

const QuadMix4fsConfig_t QuadMix4fsConfig[] = {
    {
        .num = 1,
        .filter_num_i = 1,
        .filter_num_q = 2,
        .filter_order = 400,
        .PadOkPhase = {.port=PORT_E, .pin=0,},
        .cut_off_freq_hz = 200,
        .name = "BpskDecode",
        .valid = true,
    },
};

QuadMix4fsHandle_t QuadMix4fsInstance[] = {
    { .num = 1, .valid = true, },
};

COMPONENT_GET_CNT(QuadMix4fs, quad_mix_4fs)

