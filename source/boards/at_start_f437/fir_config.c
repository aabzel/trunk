#include "fir_config.h"

#include "data_utils.h"
#include "fir_types.h"

#define FIR_ORDER 40
static FirSample_t StaticX1[FIR_ORDER]={0};
static FirSample_t StaticA1[FIR_ORDER]={0};

static FirSample_t StaticX2[FIR_ORDER]={0};
static FirSample_t StaticA2[FIR_ORDER]={0};

const FirConfig_t FirConfig[] = {
    {
     .num = 1,
     .valid = true,
     .cut_off_freq_hz = 2000,
     .sample_rate_hz = 48000.0,
     .max_size = FIR_ORDER, /*filter Order M */
     .size = 7, /*filter Order M */
     .name = "TestFIR1",
     .x=StaticX1,
     .b=StaticA1,
    },

    {
     .num = 2,
     .valid = true,
     .cut_off_freq_hz = 3000,
     .sample_rate_hz = 48000.0,
     .max_size = FIR_ORDER, /*filter Order M */
     .size = 14, /*filter Order M */
     .name = "TestFIR2",
     .x=StaticX2,
     .b=StaticA2,
    },

};


FirHandle_t FirInstance[]={
    {.num=1, .valid=true, .init=false, },
    {.num=2, .valid=true, .init=false,  },

};

uint32_t fir_get_cnt(void){
    uint8_t cnt=0;
    cnt = ARRAY_SIZE(FirConfig);
    return cnt;
}

