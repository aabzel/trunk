#include "fir_int_config.h"

#include "data_utils.h"
#include "fir_int_types.h"

static const double Bconfigs[]={0.166, 0.166, 0.166, 0.166, 0.166, 0.166};

const FirIntConfig_t FirConfig[] = {
    {.num=1,  .valid = true, .size=ARRAY_SIZE(Bconfigs), .b=Bconfigs, .name="UWB_Dist",},
};

static double StaticX1[6]={0};
static double StaticB1[6]={0};

FirIntHandle_t FirInstance[]={
    {.num=1, .valid=true, .init=false, .x=StaticX1, .b=StaticB1, },
};

uint32_t fir_get_cnt(void){
    uint8_t cnt=0;
    cnt = ARRAY_SIZE(FirConfig);
    return cnt;
}

