#include "cryp_config.h"

#include "data_utils.h"

const CrypConfig_t CrypConfigLut[] = {
    {
    	.num=CRYP_SW_NUM, 
        .algo = CRYP_ALGO_AES_CBC, 
        .name="AES256", 
        .valid=true, 
        .key_size=CRYP_KEY_256_BIT, 
        .algo_impl=ALG_IMPL_SW,
    },
};

CrypHandle_t CrypItem[]={
    {
    	.num=CRYP_SW_NUM, 
    	.valid = true, 
    	.algo_impl=ALG_IMPL_SW,
    },
};

COMPONENT_GET_CNT(Cryp, cryp)

