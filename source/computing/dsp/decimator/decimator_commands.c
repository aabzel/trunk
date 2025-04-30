#include "decimator_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "decimator.h"
#include "decimator_config.h"
#include "decimator_diag.h"

#include "table_utils.h"
#include "writer_config.h"

#ifndef HAS_DECIMATOR
#error "+HAS_DECIMATOR"
#endif /*HAS_DECIMATOR*/

#ifndef HAS_DECIMATOR_COMMANDS
#error "+HAS_DECIMATOR_COMMANDS"
#endif /*HAS_DECIMATOR_COMMANDS*/

bool decimator_proc_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    int8_t val = 0.0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(DECIMATOR, "ParseErr Num %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2int8(argv[1], &val);
        if(false == res) {
            LOG_ERROR(DECIMATOR, "ParseErr Val %s", argv[1]);
        }
    }

    if(res) {
    	int8_t sample_out = 0xEE;
        res = decimator_proc_val(num, val, &sample_out);
        LOG_INFO(DECIMATOR, "N:%u,IN:%u,OUT:%u",num, val, sample_out);
    } else {
        LOG_ERROR(DECIMATOR, "Usage: dep num val");
    }
    return res;
}


bool decimator_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "Num"},    {10, "Name"},      {9, "Threshold"}, {9, "Hyst"},     {9, "Val"},
        {11, "State"}, {11, "PrevState"}, {10, "UpCnt"},    {10, "DownCnt"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint32_t cnt = decimator_get_cnt();
    uint32_t i = 0;
    for(i = 0; i <= cnt; i++) {
        const DecimatorConfig_t* Config = DecimatorGetConfig(i);
        if(Config) {
            DecimatorHandle_t* Node = DecimatorGetNode(i);
            if(Node) {
                cli_printf(TSEP);
                cli_printf(" %02u  " TSEP, Node->num);
                cli_printf(" %8s " TSEP, Config->name);
                cli_printf(" %9s " TSEP, DecimatorStateToStr(Node->state));
                cli_printf(" %9s " TSEP, DecimatorStateToStr(Node->prev_state));

                cli_printf(CRLF);
                res = true;
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
