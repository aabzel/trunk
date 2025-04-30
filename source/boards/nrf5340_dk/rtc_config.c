#include "rtc_config.h"

#include "data_utils.h"
#include "rtc_const.h"


const RtcConfig_t RtcConfig[] = {
#ifdef HAS_RTC0
    {
        .num = 0,
        .valid = true,
        .name = "RTC0",
        .irq_priority = 7,
	    .prescaler = 0xFFF,
	    .prescaler_bit = 12,
	    .counter_bit = 24,
    },
#endif /*HAS_RTC0*/

#ifdef HAS_RTC1
    {
        .num = 1,
        .valid = true,
        .name = "RTC1",
        .irq_priority = 7,
	    .prescaler = 0xFFF,
	    .prescaler_bit = 12,
		.counter_bit = 24,
    },
#endif /*HAS_RTC1*/

#ifdef HAS_RTC2
    {
        .num = 2,
        .valid = true,
        .name = "RTC2",
        .irq_priority = 7,
	    .prescaler = 0xFFF,
	    .prescaler_bit = 12,
		.counter_bit = 24,
    },
#endif /*HAS_RTC2*/
};

RtcHandle_t RtcInstance[] = {
#ifdef HAS_RTC0
    {
        .num = 0,
        .valid = true,
    },
#endif /*HAS_RTC0*/

#ifdef HAS_RTC1
    {
        .num = 1,
        .valid = true,
    },
#endif /*HAS_RTC1*/

#ifdef HAS_RTC2
    {
        .num = 2,
        .valid = true,
    },
#endif /*HAS_RTC2*/
};

uint32_t rtc_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(RtcInstance);
    cnt2 = ARRAY_SIZE(RtcConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
