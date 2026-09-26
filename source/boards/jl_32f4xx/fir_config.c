#include "fir_config.h"

#include "data_utils.h"
#include "fir_types.h"

#define FIR_TEST_SIZE 10

static FirSample_t StaticX1[FIR_TEST_SIZE]={0};
static FirSample_t StaticB1[FIR_TEST_SIZE]={0};

static FirSample_t StaticX2[FIR_TEST_SIZE]={0};
static FirSample_t StaticB2[FIR_TEST_SIZE]={0};

#ifdef HAS_SONAR
#define FIR_ORDER_SONAR 2900
static FirSample_t StaticXSonar[FIR_ORDER_SONAR] = {0};
static FirSample_t StaticBsonar[FIR_ORDER_SONAR] = {0};
#endif

const FirConfig_t FirConfig[] = {

#ifdef HAS_SONAR
    {
        .mode = FIR_MODE_CORRELATION,
        .num = FIR_MUN_CHIRP_CORRELATION,
        .valid = true,
        .cut_off_freq_hz = 10,
        .sample_rate_hz = 48000.0,
        .max_size = ARRAY_SIZE(StaticBsonar), /*filter Order M */
        .size =  ARRAY_SIZE(StaticBsonar),              /*filter Order M */
        .name = "Chirp",
        .file_name_in = "in.csv",
        .file_name_out = "out.csv",
        .x = StaticXSonar,
        .b = StaticBsonar,
    },
#endif

    {
     .num = FIR_MUN_TEST1,
     .valid = true,
     .cut_off_freq_hz = 2000,
     .sample_rate_hz = 48000.0,
     .max_size = ARRAY_SIZE(StaticB1), /*filter Order M */
     .size = ARRAY_SIZE(StaticB1), /*filter Order M */
     .name = "TestFIR1",
     .x=StaticX1,
     .b=StaticB1,
    },

    {
     .num = FIR_MUN_TEST2,
     .valid = true,
     .cut_off_freq_hz = 3000,
     .sample_rate_hz = 48000.0,
     .max_size = ARRAY_SIZE(StaticB2), /*filter Order M */
     .size = ARRAY_SIZE(StaticB2), /*filter Order M */
     .name = "TestFIR2",
     .x=StaticX2,
     .b=StaticB2,
    },

};


FirHandle_t FirInstance[]={
#ifdef HAS_SONAR
    {.num = FIR_MUN_CHIRP_CORRELATION, .valid = true, .init = false, },
#endif

    {.num = FIR_MUN_TEST1, .valid = true, .init = false, },
    {.num = FIR_MUN_TEST2, .valid = true, .init = false,  },
};

COMPONENT_GET_CNT(Fir, fir)

