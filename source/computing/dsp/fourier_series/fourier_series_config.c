#include "fourier_series_config.h"

#ifndef HAS_FOURIER_SERIES
#error "Add HAS_FOURIER_SERIES"
#endif /*HAS_FOURIER_SERIES*/

#include "data_utils.h"
#include "fourier_series_types.h"

const FourierSeriesConfig_t FourierSeriesConfig[] = {
   {.num=1,
    .file_name="SD",
    .valid=true
   },
};

FourierSeriesHandle_t FourierSeriesItem[] = {
    {
     .num=1,
     .valid=true
    },
};

uint32_t fourier_series_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(FourierSeriesItem);
    cnt2 = ARRAY_SIZE(FourierSeriesConfig);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
}
