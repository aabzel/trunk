#include "manchester_decode_config.h"

#include "data_utils.h"

const ManchesterDecodeConfig_t ManchesterDecodeConfig[] = {
    {
        .num = 1,
        .valid = true,
        .name = "MANCHESTER_DECODE1",
    },

    {
        .num = 2,
        .valid = true,
        .name = "MANCHESTER_DECODE2",
    },
};

ManchesterDecodeHandle_t ManchesterDecodeInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
    {
        .num = 2,
        .valid = true,
    },

};

COMPONENT_GET_CNT(ManchesterDecode, manchester_decode)


