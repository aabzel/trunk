#include "mco_commands.h"

#include "convert.h"
#include "log.h"
#include "mco_diag.h"
#include "mco_drv.h"

bool mco_config_command(int32_t argc, char* argv[]) {
    bool res = false;
    McoChannel_t ch = 0;
    FrequencySource_t freq = 0;
    uint8_t divider = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &ch);
        if(res) {
            LOG_INFO(CLK, "ParseOk MCO_%u", ch);
        } else {
            LOG_ERROR(CLK, "ParseErr %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &freq);
        if(res) {
            LOG_INFO(CLK, "ParseOk %u=%s", freq, Freq2Str(freq));
        } else {
            LOG_ERROR(CLK, "ParseErr %s", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &divider);
        if(res) {
            LOG_INFO(CLK, "ParseDiv %u Ok", divider);
        } else {
            LOG_ERROR(CLK, "ParseErr %s", argv[2]);
        }
    }

    if(res) {
        res = mco_config(ch, freq, divider);
    } else {
        LOG_ERROR(CLK, "Usage: mc Chan Freq Div");
    }
    return res;
}
