#include "super_cycle_diag.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#include "data_utils.h"
#include "log.h"
#include "super_cycle.h"

#ifdef HAS_FLOAT_DIAG
#include "float_diag.h"
#endif

#ifdef HAS_WRITER
#include "writer_config.h"
#endif

#ifdef HAS_TABLE_UTILS
#include "table_utils.h"
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

bool super_cycle_diag(void) {
    bool res = true;

    static const table_col_t cols[] = {
        {5, "num"},       {12, "Calls"}, {5, "init"},   {10, "Calls/s"},
#ifdef HAS_DEBUG
        {12, "MinUs"},    {9, "CurUs"},  {10, "MaxUs"}, {9, "AvrUs"},
#endif
        {12, "RunTimeS"}, {7, "Err"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint32_t i = 0;
    uint32_t cnt = super_cycle_get_cnt();
    for(i = 0; i <= cnt; i++) {
        SuperCycleHandle_t* Node = SuperCycleGetNode(i);
        if(Node) {
            uint64_t run_time_us = super_cycle_run_time_us(i);
            uint32_t up_time_ms = time_get_ms32();
            uint32_t duration_avr_us = 0;
            float up_time_s = USEC_2_SEC(run_time_us);
            if(Node->spin_cnt) {
                duration_avr_us = (uint32_t)(run_time_us / Node->spin_cnt);
            }

            char temp_str[120] = {0};
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, i);
            snprintf(temp_str, sizeof(temp_str), "%s %10u " TSEP, temp_str, Node->spin_cnt);
            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, OnOffToStr(Node->init));

            if(up_time_ms) {
                snprintf(temp_str, sizeof(temp_str), "%s %8u " TSEP, temp_str, Node->spin_cnt * 1000 / up_time_ms);
            }
#ifdef HAS_DEBUG
            snprintf(temp_str, sizeof(temp_str), "%s %10u " TSEP, temp_str, (unsigned int)Node->duration_us.min);
            snprintf(temp_str, sizeof(temp_str), "%s %7u " TSEP, temp_str, (unsigned int)Node->duration_us.cur);
            snprintf(temp_str, sizeof(temp_str), "%s %8u " TSEP, temp_str, (unsigned int)Node->duration_us.max);
#endif
            snprintf(temp_str, sizeof(temp_str), "%s %7u " TSEP, temp_str, duration_avr_us);
#ifdef HAS_FLOAT_DIAG
            snprintf(temp_str, sizeof(temp_str), "%s %10s " TSEP, temp_str, FloatToStr(up_time_s, 2));
#endif
            snprintf(temp_str, sizeof(temp_str), "%s %5u " TSEP, temp_str, Node->error);

            cli_printf("%s" CRLF, temp_str);
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
