#include "schmitt_trigger_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "schmitt_trigger.h"
#include "schmitt_trigger_config.h"
#include "schmitt_trigger_diag.h"

#include "table_utils.h"
#include "writer_config.h"

#ifndef HAS_SCHMITT_TRIGGER
#error "+HAS_SCHMITT_TRIGGER"
#endif /*HAS_SCHMITT_TRIGGER*/

#ifndef HAS_SCHMITT_TRIGGER_COMMANDS
#error "+HAS_SCHMITT_TRIGGER_COMMANDS"
#endif /*HAS_SCHMITT_TRIGGER_COMMANDS*/

bool schmitt_trigger_proc_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    double val = 0.0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SCHMITT_TRIGGER, "ParseErr Num %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2double(argv[1], &val);
        if(false == res) {
            LOG_ERROR(SCHMITT_TRIGGER, "ParseErr Val %s", argv[1]);
        }
    }

    if(res) {
        res = schmitt_trigger_proc_val(num, val);
    } else {
        LOG_ERROR(SCHMITT_TRIGGER, "Usage: st num val");
    }
    return res;
}

bool schmitt_trigger_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    double trig_val = 0.0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SCHMITT_TRIGGER, "ParseErr Num %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2double(argv[1], &trig_val);
        if(false == res) {
            LOG_ERROR(SCHMITT_TRIGGER, "ParseErr TrigVal %s", argv[1]);
        }
    }

    if(res) {
        res = schmitt_trigger_set_val(num, trig_val);
    } else {
        LOG_ERROR(SCHMITT_TRIGGER, "Usage: sts num TgVal");
    }
    return res;
}

bool schmitt_trigger_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "Num"},    {10, "Name"},      {9, "Threshold"}, {9, "Hyst"},     {9, "Val"},
        {11, "State"}, {11, "PrevState"}, {10, "UpCnt"},    {10, "DownCnt"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint32_t cnt = schmitt_trigger_get_cnt();
    uint32_t i = 0;
    for(i = 0; i <= cnt; i++) {
        const SchmittTriggerConfig_t* Config = SchmittTriggerGetConfig(i);
        if(Config) {
            SchmittTriggerHandle_t* Node = SchmittTriggerGetNode(i);
            if(Node) {
                cli_printf(TSEP);
                cli_printf(" %02u  " TSEP, Node->num);
                cli_printf(" %8s " TSEP, Config->name);
                cli_printf(" %7.3f " TSEP, Node->switching_value);
                cli_printf(" %7.3f " TSEP, Node->hysteresis);
                cli_printf(" %7.3f " TSEP, Node->value);
                cli_printf(" %9s " TSEP, SchmittTriggerState2Str(Node->state));
                cli_printf(" %9s " TSEP, SchmittTriggerState2Str(Node->prev_state));
                cli_printf(" %8u " TSEP, Node->up_handler_cnt);
                cli_printf(" %8u " TSEP, Node->down_handler_cnt);

                cli_printf(CRLF);
                res = true;
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
