#include "bit_fifo_commands.h"

#include "convert.h"
#include "log.h"
#include "bit_fifo_mcal.h"


bool bit_fifo_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(BIT_FIFO, res, "Num");
    }

    if(res) {
        res = bit_fifo_diag_one(num);
        log_info_res(BIT_FIFO, res, "Diag");

        res = bit_fifo_diag();
        log_info_res(BIT_FIFO, res, "Diag");
    } else {
        LOG_ERROR(BIT_FIFO, "Usage: fdat");
    }

    return res;
}

bool bit_fifo_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(BIT_FIFO, res, "Num");
    }

    if(0 == argc) {
        res = bit_fifo_mcal_init();
        log_info_res(BIT_FIFO, res, "Init");
    }
    return res;
}
