#include "ir_receiver_commands.h"

#include "convert.h"
#include "ir_receiver_mcal.h"
#include "log.h"

bool ir_receiver_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }
    if(res) {
        res = ir_receiver_diag();
    } else {
        LOG_ERROR(IR_RECEIVER, "Usage: ird");
    }

    return res;
}

bool ir_receiver_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = ir_receiver_mcal_init();
        log_res(IR_RECEIVER, res, "Init");
    }
    return res;
}
