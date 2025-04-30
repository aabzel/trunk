#include "scan_config.h"

#include "data_utils.h"

const ScanConfig_t ScanConfig[] = {
   {.num=1,
		   .threshold = 23.0,
		   .timeout_s = 0.3,
		   .valid = true,
		   .sample_freq_hz = 44100,
		   .name = "ConvLog",
    },
};



ScanHandle_t ScanInstance[] = {
     {.num=1, .valid=true,},
};

uint32_t scan_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(ScanInstance);
    cnt2 = ARRAY_SIZE(ScanConfig);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
}
