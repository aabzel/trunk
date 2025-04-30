#include "cryp_config.h"


#include "data_utils.h"

const CrypConfig_t CrypConfigLut[] = {
    {
    	.num=CRYP_SW_NUM, 
    	.algo=CRYP_ALGO_AES_CBC, 
    	.name="AES256", 
    	.valid=true, 
    	.key_size=CRYP_KEY_256_BIT, 
    	.algo_impl=ALG_IMPL_SW,
    },
};

CrypHandle_t CrypItem[]={
    {
    .num = CRYP_SW_NUM, 
    .valid=true, 
    .algo_impl=ALG_IMPL_SW,
    },
};

uint32_t cryp_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(CrypItem); 
    cnt2 = ARRAY_SIZE(CrypConfigLut);
    if(cnt1==cnt2) {
        cnt = cnt1;
    }
    return cnt;
} 
