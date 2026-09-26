#include "bit_commands.h"

#include "bit_diag.h"
#include "bit_utils.h"
#include "convert.h"
#include "log.h"

bool bit_diff_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t val_a = 0;
    uint32_t val_b = 0;
    if(2 <= argc) {
        res = try_str2uint32(argv[0], &val_a);
        log_res(SYS, res, "A");
        res = try_str2uint32(argv[1], &val_b);
        log_res(SYS, res, "B");
    }

    if(res) {
        res = bit_diff(val_a, val_b);
        log_res(SYS, res, "BitDiff");
    } else {
        LOG_ERROR(SYS, "Usage: bid regA regB");
    }

    return res;
}

bool bit_need_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t value = 0;

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &value);
    }

    if(res) {
        uint32_t bitness = calc_bitness(value);
        LOG_INFO(SYS, "Value:%u=0b%s,MinBits:%u", value, utoa_bin32(value), bitness);

        bitness = calc_bitness_slow(value);
        LOG_INFO(SYS, "Value:%u=0b%s,Bits:%u", value, utoa_bin32(value), bitness);
    } else {
        LOG_ERROR(SYS, "Usage: bin Value");
    }

    return res;
}
