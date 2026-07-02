#include "gnss_config.h"

#include "data_utils.h"
#include "gnss_types.h"

const GnssConfig_t GnssConfig[]={
    {.num=1, .nmea_num=1, .valid=true, },
};

GnssHandle_t GnssInstance[]={
    {.num=1, .valid=true, }
};


uint32_t gnss_get_cnt(void){
    uint8_t cnt=0;
    cnt = ARRAY_SIZE(GnssConfig);
    return cnt;
}

