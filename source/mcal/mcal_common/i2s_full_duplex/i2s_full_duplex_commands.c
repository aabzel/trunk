#include "i2s_full_duplex_commands.h"

#include "common_diag.h"
#include "convert.h"
#include "i2s_full_duplex.h"
#include "log.h"

bool i2s_full_duplex_ctrl_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    bool on_off = false;

    if(2 == argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
        }
        res = try_str2bool(argv[1], &on_off);
        if(false == res) {
        }
    }

    if(res) {
        res = i2s_full_duplex_ctrl(num, on_off);
    } else {
        LOG_ERROR(I2S, "Usage: i2sfdc Num OnOff");
    }
    return res;
}

bool i2s_full_duplex_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = i2s_full_duplex_diag();
    } else {
        LOG_ERROR(I2S, "Usage: i2sfdd");
    }
    return res;
}
