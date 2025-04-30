#include "super_cycle_diag.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#include "data_utils.h"
#include "log.h"
#include "log_utils.h"
#include "super_cycle.h"
#include "table_utils.h"
#include "time_mcal.h"
#include "writer_config.h"

bool super_cycle_diag(void) {
    bool res = true;

    uint64_t run_time_us = super_cycle_run_time_us();
    uint64_t duration_avr_us = run_time_us / SuperCycle.spin_cnt;

    static const table_col_t cols[] = {
        {5, "init"},   {10, "Calls/s"}, {7, "Err"},
#ifdef HAS_DEBUG
        {12, "MinUs"}, {9, "CurUs"},    {10, "MaxUs"}, {9, "AvrUs"},
#endif
        {12, "Calls"},
    };
    uint32_t up_time_ms = time_get_ms32();

    char temp_str[120] = {0};
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    strcpy(temp_str, TSEP);
    snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, OnOff2Str(SuperCycle.init));

    if(up_time_ms) {
        snprintf(temp_str, sizeof(temp_str), "%s %8u " TSEP, temp_str, SuperCycle.spin_cnt * 1000 / up_time_ms);
    }
    snprintf(temp_str, sizeof(temp_str), "%s %5u " TSEP, temp_str, SuperCycle.error);
#ifdef HAS_DEBUG
    snprintf(temp_str, sizeof(temp_str), "%s %10u " TSEP, temp_str, (unsigned int)SuperCycle.duration_us.min);
    snprintf(temp_str, sizeof(temp_str), "%s %7u " TSEP, temp_str, (unsigned int)SuperCycle.duration_us.cur);
    snprintf(temp_str, sizeof(temp_str), "%s %8u " TSEP, temp_str, (unsigned int)SuperCycle.duration_us.max);
#endif
    snprintf(temp_str, sizeof(temp_str), "%s %7llu " TSEP, temp_str, duration_avr_us);
    snprintf(temp_str, sizeof(temp_str), "%s %10u " TSEP, temp_str, SuperCycle.spin_cnt);
    cli_printf("%s" CRLF, temp_str);
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    LOG_INFO(SUPER_CYCLE, "RunTime: %u us", run_time_us);
    return res;
}
