#include "rtc_config.h"

#include "data_utils.h"
#include "rtc_types.h"

const RtcConfig_t RtcConfig[] = {
    {
        .num = 1,
        .valid = true,
        .name = "RTC0",
        .irq_priority = 7,
        .rtc_location = RTC_LOCATION_INTERNAL,
        .ref_clock = RTC_32K_CLOCK_INTERNAL,
        .format = RTC_FORMAT_24H,
    },
 // { .name = "RTC", .num = 1, .rtc_location = RTC_LOCATION_INTERNAL, .valid = true,    },
};

RtcHandle_t RtcInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
//  { .num = 2, .valid = true, }
};

COMPONENT_GET_CNT(Rtc, rtc)
