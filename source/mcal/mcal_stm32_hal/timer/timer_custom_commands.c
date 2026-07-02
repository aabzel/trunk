#include "timer_custom_commands.h"

#include "convert.h"
#include "log.h"
#include "timer_custom_diag.h"

// timer_diag_reg_fields 3

bool timer_diag_reg_fields_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(TIMER, res, "Num");
    }
    if(res) {
        res = timer_diag_reg_fields(num);
        log_res(TIMER, res, "diagRegFields");
    } else {
        LOG_ERROR(TIMER, "Usage: tdrf num");
    }

    return res;
}

bool timer_info_command(int32_t argc, char* argv[]){
    bool res = false;
    res = timer_info_diag();
    return res;

}
