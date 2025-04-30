#include "cryp_config.h"


#include "data_utils.h"

static const uint8_t InitVector[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

const CrypConfig_t CrypConfigLut[] = {
    {.num=CRYP_HW_NUM, .algo=CRYP_ALGO_AES_CBC, .name="AES256", .valid=true,
     .init_vector=InitVector, .key_size=CRYP_KEY_256_BIT, .algo_impl=ALG_IMPL_HW,},

    {.num=CRYP_SW_NUM, .algo=CRYP_ALGO_AES_CBC, .name="AES256", .valid=true,
     .init_vector=InitVector,  .key_size=CRYP_KEY_256_BIT, .algo_impl=ALG_IMPL_SW,},
};

CrypHandle_t CrypItem[]={
    {.num=CRYP_HW_NUM, .valid=true, .algo_impl=ALG_IMPL_HW,},
    {.num=CRYP_SW_NUM, .valid=true, .algo_impl=ALG_IMPL_SW,},
};

uint32_t cryp_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(CrypItem); 
    cnt2 = ARRAY_SIZE(CrypConfigLut);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
} 
