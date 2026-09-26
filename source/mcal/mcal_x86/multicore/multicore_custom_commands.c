#include "multicore_custom_commands.h"

#include "convert.h"
#include "log.h"
#include "multicore_custom_diag.h"
#include "multicore_mcal.h"

bool multicore_custom_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = multicore_custom_diag();
    return res;
}

bool multicore_reset_command(int32_t argc, char* argv[]) {
    bool res = false;

    uint8_t core_num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &core_num);
        log_res(MULTICORE, res, "CoreNum");
    }

    if(res) {
        res = multicore_reset(core_num);
        log_res(MULTICORE, res, "Reset");
    } else {
        LOG_ERROR(MULTICORE, "Usage: mcr CoreNum");
    }
    return res;
}
