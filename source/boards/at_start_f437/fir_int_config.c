#include "fir_int_config.h"

#include "data_utils.h"
#include "fir_int_types.h"

#define FIR_ORDER 20

static FirIntSample_t StaticX1[FIR_ORDER]={0};
static FirIntSample_t StaticA1numerator[FIR_ORDER]={0};
static float StaticA1[FIR_ORDER]={0};

static FirIntSample_t StaticX2[FIR_ORDER]={0};
static FirIntSample_t StaticA2numerator[FIR_ORDER]={0};
static float StaticA2[FIR_ORDER]={0};

const FirIntConfig_t FirIntConfig[] = {
    {
     .num = 1,
     .valid = true,
     .cut_off_freq_hz = 1000,
     .denominator = 1000,
     .sample_rate_hz = 48000.0,
     .max_size = FIR_ORDER, /*filter Order M */
     .size = 7, /*filter Order M */
     .name = "VoiceChanger",
    		.x=StaticX1,
    		.a_real=StaticA1,
    		.a_numerator=StaticA1numerator,
    },

    {
     .num = 2,
     .valid = true,
     .cut_off_freq_hz = 3000,
     .denominator = 1000,
     .sample_rate_hz = 48000.0,
     .max_size = FIR_ORDER, /*filter Order M */
     .size = 14, /*filter Order M */
     .name = "VoiceChanger",
    		.x=StaticX2,
    		.a_real=StaticA2,
    		.a_numerator=StaticA2numerator,
    },
};

FirIntHandle_t FirIntInstance[]={
    {.num=1, .valid=true, .init=false,    },
    {.num=2, .valid=true, .init=false,    },
};

uint32_t fir_int_get_cnt(void){
    uint8_t cnt=0;
    cnt = ARRAY_SIZE(FirIntConfig);
    return cnt;
}

