#include "timer_custom_commands.h"

#include <inttypes.h>

#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "ostream.h"
#include "table_utils.h"
#include "timer_custom_drv.h"
#include "timer_mcal.h"
#include "writer_config.h"

static bool diag_page_timer_nrf_compare(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "Num"},  {5, "Ena"},  {3, "Ch"},   {12, "per"}, {12, "Com"},
        {12, "Cnt"}, {9, "fill"}, {12, "Psc"}, {10, "It"},  {10, "name"},
    };
    uint32_t chan = 0;
    uint32_t ccr = {0};
    uint8_t num = 0;
    // float period_max = 0.0f;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(num = 0; num <= TIMER_COUNT; num++) {
        res = true;
        bool on_off = timer_get_status(num);
        uint32_t period = timer_get_period(num);
        uint32_t prescaler = timer_get_prescaler(num);
        const TimerConfig_t* TimerConfNode = TimerGetConfig(num);
        TimerHandle_t* Node = TimerGetNode(num);
        if(TimerConfNode) {
            for(chan = 0; chan <= NRF_TIMER_CC_CHANNEL3; chan++) {
                ccr = timer_get_cc_val(num, chan);
                uint32_t counter = timer_nrf_get_counter(num, chan);
                double fill = 0.0;
                if(period) {
                    fill = 100.0 * ((double)counter) / ((double)period);
                }
                cli_printf(TSEP);
                cli_printf(" %02u  " TSEP, num);
                cli_printf(" %3s " TSEP, OnOff2Str(on_off));
                cli_printf(" %1u " TSEP, chan);
                cli_printf(" 0x%08x " TSEP, period);
                cli_printf(" 0x%08x " TSEP, ccr);
                cli_printf(" 0x%08x " TSEP, counter);
                cli_printf(" %7.2f " TSEP, fill);
                cli_printf(" %10u " TSEP, prescaler);
                cli_printf(" %10u " TSEP, Node->int_com_cnt[chan]);
                cli_printf(" %8s " TSEP, TimerConfNode->name);
                cli_printf(CRLF);
            }
            table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        }
    }
    return res;
}

bool timer_nrf_diag_compare_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = diag_page_timer_nrf_compare();
    } else {
        LOG_ERROR(TIMER, "Usage: tdc");
    }

    return res;
}
