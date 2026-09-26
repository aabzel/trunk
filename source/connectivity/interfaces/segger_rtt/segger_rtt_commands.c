#include "segger_rtt_commands.h"

#include "convert.h"
#include "log.h"
#include "segger_rtt_mcal.h"

bool segger_rtt_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SEGGER_RTT, res, "Num");
    }

    if(res) {
        res = segger_rtt_write(num, argv[1]);
        log_info_res(SEGGER_RTT, res, "write");

    } else {
        LOG_ERROR(SEGGER_RTT, "Usage: srw N Str");
    }

    return res;
}

bool segger_rtt_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SEGGER_RTT, res, "Num");
    }

    if(res) {
        res = segger_rtt_diag_one(num);
        log_info_res(SEGGER_RTT, res, "Diag");

        res = segger_rtt_diag();
        log_info_res(SEGGER_RTT, res, "Diag");
    } else {
        LOG_ERROR(SEGGER_RTT, "Usage: fdat");
    }

    return res;
}

bool segger_rtt_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SEGGER_RTT, res, "Num");
    }

    if(0 == argc) {
        res = segger_rtt_mcal_init();
        log_info_res(SEGGER_RTT, res, "Init");
    }
    return res;
}
