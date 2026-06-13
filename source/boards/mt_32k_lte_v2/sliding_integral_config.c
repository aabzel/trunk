#include "sliding_integral_config.h"

#include "data_utils.h"
#include "sliding_integral_types.h"

#define IQ_LPF_LEN 26 //26  8- e 30
static int32_t StaticX1[IQ_LPF_LEN] = {0};
static int32_t StaticX2[IQ_LPF_LEN] = {0};
static int32_t StaticX3[5] = {0};

const SlidingIntegralConfig_t SlidingIntegralConfig[] = {
    {
        .num = 1,
        .valid = true,
        .sample_rate_hz = 1000,
        .max_size = ARRAY_SIZE(StaticX1), /*filter Order M */
        .size = ARRAY_SIZE(StaticX1),     /*filter Order M */
        .name = "I",
        .x = StaticX1,
    },

    {
        .num = 2,
        .valid = true,
        .sample_rate_hz = 1000,
        .max_size = ARRAY_SIZE(StaticX2), /*filter Order M */
        .size = ARRAY_SIZE(StaticX2),     /*filter Order M */
        .x = StaticX2,
        .name = "Q",
    },

    {
        .num = 3,
        .valid = true,
        .sample_rate_hz = 1000,
        .max_size = ARRAY_SIZE(StaticX3), /*filter Order M */
        .size = ARRAY_SIZE(StaticX3),     /*filter Order M */
        .x = StaticX3,
        .name = "ForTest",
    },

};

SlidingIntegralHandle_t SlidingIntegralInstance[] = {
    { .num = 1, .valid = true,  },
    { .num = 2, .valid = true,  },
    { .num = 3, .valid = true,  },
};

COMPONENT_GET_CNT(SlidingIntegral, sliding_integral)
