#include "iir_config.h"

#include "data_utils.h"
#include "iir_types.h"

#define IIR_MAX_ORDER 8

#define IIR1_ORDER 7

///------------------------------------------------

static IirSample_t StaticX1[IIR_MAX_ORDER] = {0};
static IirSample_t StaticY1[IIR_MAX_ORDER] = {0};
// ok
static IirSample_t StaticFeedForward1[] = {0.00000000816384086451, 0.00000002449152259353, 0.00000002449152259353,
                                           0.00000000816384086451};

static IirSample_t StaticFeedBack1[] = {1.00000000000000000000, -2.99715048309490010000, 2.99430502461701350000,
                                        -0.99715453863406001000};
///------------------------------------------------

static IirSample_t StaticX2[7] = {0};
static IirSample_t StaticY2[7] = {0};

static IirSample_t StaticFeedForwardB2[] = {0.00000000001785336951, 0.00000000008926684755, 0.00000000017853369510,
                                            0.00000000017853369510, 0.00000000008926684755, 0.00000000001785336951};

static IirSample_t StaticFeedBackA2[] = {1.00000000000000000000,  -4.94580510978888640000, 9.78458861225242060000,
                                         -9.67891547624729400000, 4.78728571419223670000,  -0.94715373983704532000};

///------------------------------------------------

static IirSample_t StaticX3[7] = {0};
static IirSample_t StaticY3[7] = {0};

static IirSample_t StaticFeedForward3[] = {0.00000000001785336951, 0.00000000008926684755, 0.00000000017853369510,
                                           0.00000000017853369510, 0.00000000008926684755, 0.00000000001785336951};

static IirSample_t StaticFeedBack3[] = {1.00000000000000000000,  -4.94580510978888640000, 9.78458861225242060000,
                                        -9.67891547624729400000, 4.78728571419223670000,  -0.94715373983704532000};

///------------------------------------------------

static IirSample_t StaticX4[IIR_MAX_ORDER] = {0};
static IirSample_t StaticY4[IIR_MAX_ORDER] = {0};

static IirSample_t StaticFeedForward4[] = {0.0002, 0.0000};

// first ignored
static IirSample_t StaticFeedBack4[] = {-0.0000, -0.9998};

///------------------------------------------------
static IirSample_t StaticX5[4] = {0};
static IirSample_t StaticY5[4] = {0};

static IirSample_t StaticForward5[] = {0.00000000816384086451, 0.00000002449152259353, 0.00000002449152259353,
                                       0.00000000816384086451};

static IirSample_t StaticFeedBackA5[] = {1.00000000000000000000, -2.99715048309490010000, 2.99430502461701350000,
                                         -0.99715453863406001000};
///------------------------------------------------

static IirSample_t StaticX6[4] = {0};
static IirSample_t StaticY6[4] = {0};

static IirSample_t StaticFeedForward6[] = {0.00000000816384086451, 0.00000002449152259353, 0.00000002449152259353,
                                           0.00000000816384086451};

static IirSample_t StaticFeedBack6[] = {1.00000000000000000000, -2.99715048309490010000, 2.99430502461701350000,
                                        -0.99715453863406001000};
///------------------------------------------------

static IirSample_t StaticX7[4] = {0};
static IirSample_t StaticY7[4] = {0};

static IirSample_t StaticFeedForward7[] = {8.663387e-4, 1.732678e-3, 8.663387e-4};

static IirSample_t StaticFeedBack7[] = {0.0, -1.919129, 0.9225943};

const IirConfig_t IirConfig[] = {
    {
        .num = 1,
        .valid = true,
        .cut_off_freq_hz = 2055, // Fc=0.05
        .sample_rate_hz = 41100.0,
        .max_size = ARRAY_SIZE(StaticFeedBack1), /*filter Order M */
        .size = ARRAY_SIZE(StaticFeedBack1),     /*filter Order M */
        .name = "IIR1",
        .x = StaticX1,
        .y = StaticY1,
        .a = StaticFeedBack1,
        .b = StaticFeedForward1,
    },

    {
        .num = 2,
        .valid = true,
        .cut_off_freq_hz = 200,
        .sample_rate_hz = 41100.0,
        .max_size = ARRAY_SIZE(StaticFeedBackA2), /*filter Order M */
        .size = ARRAY_SIZE(StaticFeedBackA2),     /*filter Order M */
        .name = "QM1",
        .x = StaticX2,
        .y = StaticY2,
        .a = StaticFeedBackA2,
        .b = StaticFeedForwardB2,
    },

    {
        .num = 3,
        .valid = true,
        .cut_off_freq_hz = 200,
        .sample_rate_hz = 41100.0,
        .max_size = ARRAY_SIZE(StaticFeedBack3), /*filter Order M */
        .size = ARRAY_SIZE(StaticFeedBack3),     /*filter Order M */
        .name = "QM1",
        .x = StaticX3,
        .y = StaticY3,
        .a = StaticFeedBack3,
        .b = StaticFeedForward3,
    },

    {
        .num = 4,
        .valid = true,
        .cut_off_freq_hz = 5.0,
        .sample_rate_hz = 41100.0,
        .max_size = ARRAY_SIZE(StaticFeedForward4), /*filter Order M */
        .size = ARRAY_SIZE(StaticFeedForward4),     /*filter Order M */
        .name = "CostasLoopFilter",
        .x = StaticX4,
        .y = StaticY4,
        .a = StaticFeedBack4,
        .b = StaticFeedForward4,
    },

    {
        .num = 5,
        .valid = true,
        .cut_off_freq_hz = 10,
        .sample_rate_hz = 41100.0,
        .max_size = ARRAY_SIZE(StaticFeedBackA5), /*filter Order M */
        .size = ARRAY_SIZE(StaticFeedBackA5),     /*filter Order M */
        .name = "QM2",
        .x = StaticX5,
        .y = StaticY5,
        .a = StaticFeedBackA5,
        .b = StaticForward5,
    },

    {
        .num = 6,
        .valid = true,
        .cut_off_freq_hz = 10,
        .sample_rate_hz = 41100.0,
        .max_size = ARRAY_SIZE(StaticFeedBack6), /*filter Order M */
        .size = ARRAY_SIZE(StaticFeedBack6),     /*filter Order M */
        .name = "QM2",
        .x = StaticX6,
        .y = StaticY6,
        .a = StaticFeedBack6,    // feedback
        .b = StaticFeedForward6, // forward
    },

    {
        .num = 7,
        .valid = true,
        .cut_off_freq_hz = 10,
        .sample_rate_hz = 41100.0,
        .max_size = ARRAY_SIZE(StaticFeedBack7), /*filter Order M */
        .size = ARRAY_SIZE(StaticFeedBack7),     /*filter Order M */
        .name = "Test1order",
        .x = StaticX7,
        .y = StaticY7,
        .a = StaticFeedBack7,    // feedback
        .b = StaticFeedForward7, // forward
    },
};

IirHandle_t IirInstance[] = {
    {
        .num = 1,
        .valid = true,
        .init = false,
    },
    {
        .num = 2,
        .valid = true,
        .init = false,
    },
    {
        .num = 3,
        .valid = true,
        .init = false,
    },
    {
        .num = 4,
        .valid = true,
        .init = false,
    },
    {
        .num = 5,
        .valid = true,
        .init = false,
    },
    {
        .num = 6,
        .valid = true,
        .init = false,
    },
    {
        .num = 7,
        .valid = true,
        .init = false,
    },
};

uint32_t iir_get_cnt(void) {
    uint8_t cnt = 0;
    uint8_t cnt1 = 0;
    uint8_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(IirInstance);
    cnt2 = ARRAY_SIZE(IirConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
