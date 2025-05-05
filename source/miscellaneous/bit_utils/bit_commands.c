#include "bit_commands.h"

#include "bit_diag.h"
#include "convert.h"
#include "log.h"

bool bit_diff_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t val_a = 0;
    uint32_t val_b = 0;
    if(2 <= argc) {
        res = try_str2uint32(argv[0], &val_a);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr adc %s", argv[0]);
        }
        res = try_str2uint32(argv[1], &val_b);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr adc %s", argv[0]);
        }
    }

    if(res) {
        res = bit_diff(val_a, val_b);
        log_res(SYS, res, "BitDiff");
    } else {
        LOG_ERROR(SYS, "Usage: bd regA regB");
    }

    return res;
}
