#include "rtc_config.h"

#include "data_utils.h"
#include "rtc_types.h"

const RtcConfig_t RtcConfig[] = {
    {
     .name = "RTC",
     .num = 1,
     .rtc_location = RTC_LOCATION_INTERNAL,
     .valid = true,
    },
};

RtcHandle_t RtcInstance[]={
    {
     .num = 1,
     .valid = true,
    }
};



uint32_t rtc_get_cnt(void){
    uint8_t cnt=0;
    cnt = ARRAY_SIZE(RtcConfig);
    return cnt;
}

