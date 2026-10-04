#include "ublox_neo_6m_config.h"

#include "data_utils.h"
#include "ublox_neo_6m_types.h"

const uBloxNeo6mConfig_t uBloxNeo6mConfig[] = {
    {.num=1, .uart_num=6, .valid=true, },
};

uBloxNeo6mHandle_t uBloxNeo6mInstance[]={
    {.num=1, .valid=true, }
};

uint32_t ublox_neo_6m_get_cnt(void){
    uint8_t cnt=0;
    cnt = ARRAY_SIZE(uBloxNeo6mConfig);
    return cnt;
}

