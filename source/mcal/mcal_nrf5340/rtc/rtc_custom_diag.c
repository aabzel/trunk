#include "rtc_custom_diag.h"

#include <stdio.h>
#include <string.h>

#include "log.h"
#include "rtc_const.h"
#include "rtc_custom_drv.h"
#include "table_utils.h"
#include "time_diag.h"
#include "time_mcal.h"
#include "utils_math.h"
#include "writer_config.h"

bool RtcStaticInfoDiag(const RtcStaticInfo_t* const StaticInfo) {
    bool res = false;
    if(StaticInfo) {
        LOG_INFO(LG_RTC, "Num %u", StaticInfo->num);
        LOG_INFO(LG_RTC, "HandlerAddr 0x%p", StaticInfo->event_handler);
        LOG_INFO(LG_RTC, "CcChannelCnt %u", StaticInfo->handle.cc_channel_count);
        LOG_INFO(LG_RTC, "InstanceId %u", StaticInfo->handle.instance_id);
        LOG_INFO(LG_RTC, "IrqId %u", StaticInfo->handle.irq);
        LOG_INFO(LG_RTC, "BaseAddr 0x%p", StaticInfo->handle.p_reg);
        res = true;
    }
    return res;
}

bool rtc_diag_low_level(void) {
    bool res = false;
    uint32_t i = 0;
    uint32_t cnt = RTC_COUNT;
    char line[150];
    static const table_col_t cols[] = {
        {3, "Num"},
        {12, "Base"},
        {11, "Counter"},
        {12, "Prescaler"},
        {12, "MaxTicks"},
        {12, "ISR"},
        {12, "TickPerMs"},
        {12, "OverflowS"},
        {12, "OverflowDays"},
#if 0
        {12, "compare1"},
        {12, "compare2"},
        {12, "compare3"},
        {12, "compare4"},
#endif
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    // uint32_t captere_compare[4] = {0};
    for(i = 0; i < cnt; i++) {
        RtcStaticInfo_t* InfoNode = RtcGetStaticNode(i);
        if(InfoNode) {
            uint32_t counter = nrfx_rtc_counter_get(&InfoNode->handle);
            uint32_t prescaler = nrf_rtc_prescaler_get(InfoNode->handle.p_reg);
            uint32_t max_ticks = nrfx_rtc_max_ticks_get(&InfoNode->handle);
            double tick_time_s = ((double)prescaler) * ((double)RTC_TICK_PERIOD_S);
            double overflow_s = ((double)int_pow(2, InfoNode->counter_bit)) * tick_time_s;

            // struct tm TimeDuration;
            // memset(&TimeDuration,0,sizeof(struct tm ));
            // res= time_sec_to_time((uint32_t) overflow_s, &TimeDuration);
#if 0
            captere_compare[0] = nrf_rtc_cc_get(InfoNode->handle.p_reg, 0);
            captere_compare[1] = nrf_rtc_cc_get(InfoNode->handle.p_reg, 1);
            captere_compare[2] = nrf_rtc_cc_get(InfoNode->handle.p_reg, 2);
            captere_compare[3] = nrf_rtc_cc_get(InfoNode->handle.p_reg, 3);
#endif
            strcpy(line, TSEP);
            snprintf(line, sizeof(line), "%s %1u " TSEP, line, i);
            snprintf(line, sizeof(line), "%s %p " TSEP, line, InfoNode->handle.p_reg);
            snprintf(line, sizeof(line), "%s %9u " TSEP, line, counter);
            snprintf(line, sizeof(line), "%s %10u " TSEP, line, prescaler);
            snprintf(line, sizeof(line), "%s 0x%08x " TSEP, line, max_ticks);
            snprintf(line, sizeof(line), "%s %10p " TSEP, line, InfoNode->event_handler);
            snprintf(line, sizeof(line), "%s %10u " TSEP, line, SEC_2_MSEC(tick_time_s));
            snprintf(line, sizeof(line), "%s %10.1f " TSEP, line, overflow_s);
            snprintf(line, sizeof(line), "%s %10.3f " TSEP, line, SEC_2_DAYS(overflow_s));
            // snprintf(line, sizeof(line), "%s %s " TSEP, line, TimeDate2StrShort(&TimeDuration));
#if 0
            snprintf(line, sizeof(line), "%s 0x%08x " TSEP, line, captere_compare[0]);
            snprintf(line, sizeof(line), "%s 0x%08x " TSEP, line, captere_compare[1]);
            snprintf(line, sizeof(line), "%s 0x%08x " TSEP, line, captere_compare[2]);
            snprintf(line, sizeof(line), "%s 0x%08x " TSEP, line, captere_compare[3]);
#endif
            cli_printf("%s" CRLF, line);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
