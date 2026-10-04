#include "rtc_config.h"

#include "data_utils.h"
#include "rtc_types.h"

const RtcConfig_t RtcConfig[] = {
    {
      .num = 1,
      .irq_priority = 7,
      .name = "RTC",
      .rtc_location = RTC_LOCATION_INTERNAL,
      .ref_clock = RTC_32K_CLOCK_EXTERAL,
      .format = RTC_FORMAT_24H,
      .valid = true,
    },
};

RtcHandle_t RtcInstance[] = {
    { .num = 1, .valid = true, },
};

COMPONENT_GET_CNT(Rtc, rtc)


