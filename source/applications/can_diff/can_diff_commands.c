#include "can_diff_commands.h"

#include "can_diff_mcal.h"
#include "convert.h"
#include "log.h"

bool can_diff_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(CAN_DIFF, res, "Num");
    }

    if(res) {
        switch(argc) {
        case 0: {
            res = can_diff_diag();
            log_info_res(CAN_DIFF, res, "Diag");

        } break;
        case 1: {
            res = can_diff_diag_one(num);
            log_info_res(CAN_DIFF, res, "Diag");

        } break;
        default:
            break;
        }

    } else {
        LOG_ERROR(CAN_DIFF, "Usage: cdd Num");
    }

    return res;
}

bool can_diff_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 == argc) {
        res = can_diff_mcal_init();
        log_info_res(CAN_DIFF, res, "Init");
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(CAN_DIFF, res, "Num");
    }

    if(!res) {
        LOG_ERROR(CAN_DIFF, "Usage: cdi Num");
    }
    return res;
}

bool can_diff_watch_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t can_num = 0;
    uint8_t id_type = 0;
    uint32_t can_id = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(CAN_DIFF, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &can_num);
        log_info_res(CAN_DIFF, res, "CanNum");
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &can_id);
        log_info_res(CAN_DIFF, res, "CanId");
    }

    if(4 <= argc) {
        res = try_str2uint8(argv[3], &id_type);
        log_info_res(CAN_DIFF, res, "IdType");
    }

    if(res) {
        res = can_diff_watch(num, can_num, can_id, id_type);
        log_info_res(CAN_DIFF, res, "Watch");
    } else {
        LOG_ERROR(CAN_DIFF, "Usage: cdw Num CanNum CanId idType");
    }
    return res;
}
