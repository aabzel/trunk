#include "rtc_diag.h"

#include <stdio.h>
#include <string.h>

#ifdef HAS_CALENDAR
#include "calendar.h"
#endif
#include "common_diag.h"
#include "log.h"
#include "rtc_mcal.h"
#include "table_utils.h"
#include "time_diag.h"
#include "writer_config.h"

bool RtcDiagConfig(const RtcConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(LG_RTC, "Config: Name: %s", Config->name);
        LOG_INFO(LG_RTC, "IrqPri %u", Config->irq_priority);
        res = true;
    }
    return res;
}

const char* RtcConfigToStr(const RtcConfig_t* const Config) {
    static char line[150]={0};
    if(Config) {
        strcpy(line, "");
        snprintf(line, sizeof(line), "%sN:%1u," TSEP, line, Config->num);
        snprintf(line, sizeof(line), "%sType:%u," TSEP, line, Config->rtc_location);
        snprintf(line, sizeof(line), "%sRef:%u," TSEP, line, Config->ref_clock);
        snprintf(line, sizeof(line), "%sFormat:%u," TSEP, line, Config->format);
        snprintf(line, sizeof(line), "%sPri:%u," TSEP, line, Config->irq_priority);
        snprintf(line, sizeof(line), "%sName:%s" TSEP, line, Config->name);
    }
    return line;
}


bool rtc_diag(void) {
    bool res = false;
    char line[150]={0};
    LOG_INFO(LG_RTC, "CompileDate:[%s]", __DATE__);
    LOG_INFO(LG_RTC, "CompileTime:[%s]", __TIME__);
    LOG_INFO(LG_RTC, "CompileTimeStamp:[%s]", __TIMESTAMP__);

    static const table_col_t cols[] = {
        {3, "Num"},    {12, "Sec"},  {10, "Time"}, {12, "Date"},  {5, "En"},
        {12, "ItCnt"}, {7, "Start"}, {7, "Stop"},  {12, "Error"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint16_t cnt = rtc_get_cnt();
    uint8_t i = 0;
    for(i = 0; i <= cnt; i++) {
        RtcHandle_t* Node = RtcGetNode(i);
        if(Node) {
            //SecondsToTimeDate(Node->raw_sec, &Node->TimeDate);
            res = rtc_get(i, &Node->TimeDate);
            strcpy(line, TSEP);
            snprintf(line, sizeof(line), "%s %1u " TSEP, line, Node->num);
            snprintf(line, sizeof(line), "%s %10u " TSEP, line, Node->raw_sec);
            snprintf(line, sizeof(line), "%s %8s " TSEP, line, Time2StrShort(&Node->TimeDate));
            snprintf(line, sizeof(line), "%s %10s " TSEP, line, Date2StrShort(&Node->TimeDate));
            snprintf(line, sizeof(line), "%s %3s " TSEP, line, OnOff2Str(Node->init_done));
            snprintf(line, sizeof(line), "%s %10u " TSEP, line, Node->int_cnt);
            snprintf(line, sizeof(line), "%s %10u " TSEP, line, Node->error_cnt);
            cli_printf("%s" CRLF, line);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
