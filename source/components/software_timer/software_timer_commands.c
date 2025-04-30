#include "software_timer_commands.h"

#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "software_timer.h"
#include "software_timer_diag.h"
#include "software_timer_types.h"
#include "sw_timer_config.h"
#include "table_utils.h"
#include "time_mcal.h"
#include "writer_config.h"

bool sw_timer_set_handler_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t tim_num = 0;
    uint32_t address = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &tim_num);
        if(false == res) {
            LOG_ERROR(SW_TIMER, "ParseErr TimNum %s", argv[0]);
        }
    }
    if(2 <= argc) {
        res = try_str2uint32(argv[1], &address);
        if(false == res) {
            LOG_ERROR(SW_TIMER, "ParseErr address %s", argv[1]);
        }
    }
    if(res) {
        res = sw_timer_set_handler(tim_num, address);
    }
    return res;
}

bool sw_timer_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "Num"}, {5, "En"},   {10, "cnt"},     {10, "period"}, {10, "phase"}, {8, "fill"},
        {6, "dir"}, {8, "mode"}, {12, "handler"}, {7, "CbCnt"},   {5, "err"},    {15, "name"},

    };
    uint8_t sw_tim_num = 0;
    // float period_max = 0.0f;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    double fill = 0.0;
    uint32_t cnt = software_timer_get_cnt();
    for(sw_tim_num = 0; sw_tim_num <= cnt; sw_tim_num++) {
        const SoftwareTimerConfig_t* ConfNode = SwTimerGetConfigNode(sw_tim_num);
        SoftwareTimer_t* Node = SwTimerGetNode(sw_tim_num);
        if(Node && ConfNode) {
            fill = (double)100 * Node->cnt / Node->period_ms;
            cli_printf(TSEP);
            cli_printf(" %02u  " TSEP, sw_tim_num);
            cli_printf(" %3s " TSEP, OnOff2Str(Node->on_off));
            cli_printf(" %8u " TSEP, Node->cnt);
            cli_printf(" %8u " TSEP, Node->period_ms);
            cli_printf(" %8u " TSEP, Node->phase_ms);
            cli_printf(" %6.2f " TSEP, fill);
            cli_printf(" %04s " TSEP, SwTimDir2Str(Node->dir));
            cli_printf(" %04s " TSEP, SwTimMode2Str(Node->mode));
            cli_printf(" 0x%08x " TSEP, (uint32_t)Node->handler);
            cli_printf(" %5u " TSEP, Node->handler_cnt);
            cli_printf(" %03u " TSEP, Node->err_cnt);
            cli_printf(" %6s  " TSEP, ConfNode->name);
            cli_printf(CRLF);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool sw_timer_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t tim_num = 0;
    bool on_off = true;
    uint32_t period_ms = 0;
    uint32_t phase_ms = 0;
    uint8_t dir = SW_TIMER_CNT_DIR_UNDEF;
    uint8_t mode = SW_TIMER_MODE_UNDEF;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &tim_num);
        if(false == res) {
            LOG_ERROR(SW_TIMER, "ParseErr TimNum %s", argv[0]);
        }
    }
    if(2 <= argc) {
        res = try_str2uint32(argv[1], &period_ms);
        if(false == res) {
            LOG_ERROR(SW_TIMER, "ParseErr Period %s", argv[1]);
        }
    }
    if(3 <= argc) {
        res = try_str2uint8(argv[2], &mode);
        if(false == res) {
            LOG_ERROR(SW_TIMER, "ParseErr Mode %s", argv[2]);
        }
    }
    if(4 <= argc) {
        res = try_str2uint8(argv[3], &dir);
        if(false == res) {
            LOG_ERROR(SW_TIMER, "ParseErr Dir %s", argv[3]);
        }
    }
    if(5 <= argc) {
        res = try_str2uint32(argv[4], &phase_ms);
        if(false == res) {
            LOG_ERROR(SW_TIMER, "ParseErr phase %s", argv[4]);
        }
    }
    if(6 <= argc) {
        res = try_str2bool(argv[5], &on_off);
        if(false == res) {
            LOG_ERROR(SW_TIMER, "ParseErr OnOff %s", argv[5]);
        }
    }

    if(res) {
        res = sw_timer_ctrl(tim_num, period_ms, phase_ms, (SwTimerMode_t)mode, (SwTimerCntDir_t)dir, on_off);
        if(res) {
            LOG_INFO(SW_TIMER, "SetOk");
        } else {
            LOG_ERROR(SW_TIMER, "SetErr");
        }
    } else {
        LOG_ERROR(SW_TIMER, "Usage: sts num period mode dir phase on");
    }
    return res;
}

bool sw_timer_timer_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t period_s = 0;
    if(1 == argc) {
        period_s = time_duration_parse(argv[0]);
        res = true;
    }

    if(period_s) {
        res = true;
    } else {
        res = false;
    }

    if(res) {
        res = false;
        LOG_INFO(SW_TIMER, "SetTimer %u sec", period_s);
        res = sw_timer_add_new(period_s);
        if(res) {
            LOG_INFO(SW_TIMER, "SetOk");
        } else {
            LOG_ERROR(SW_TIMER, "SetErr");
        }
    } else {
        LOG_ERROR(SW_TIMER, "Usage: timer TimeStr");
    }
    return res;
}
