#include "rtc_config.h"

#include "data_utils.h"
#include "rtc_types.h"

const RtcConfig_t RtcConfig[] = {
    { .name = "RTC", .num = 1, .rtc_location = RTC_LOCATION_EXTERNAL, .valid = true,    },
 // { .name = "RTC", .num = 1, .rtc_location = RTC_LOCATION_INTERNAL, .valid = true,    },
};

RtcHandle_t RtcInstance[] = {
    { .num = 1, .valid = true, },
//  { .num = 2, .valid = true, }
};

COMPONENT_GET_CNT(Rtc, rtc)


