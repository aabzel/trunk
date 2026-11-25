#include "can_enhanced_fifo_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "array_diag.h"
#include "can_custom.h"
#include "can_custom_diag.h"
#include "can_enhanced_fifo.h"
#include "can_mcal.h"
#include "common_diag.h"
#include "convert.h"
#include "debug_info.h"
#include "log.h"

bool can_diag_enhanced_fifo_parse_command(int32_t argc, char* argv[]) {
    uint8_t num = 0;
    bool res = false;

    if(0 <= argc) {
        num = 0;
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "Num");
    }

    if(res) {
        res = can_diag_enhanced_fifo_parse(num);
        log_res(CAN, res, "EnhFiFoRegionParse");

    } else {
        LOG_ERROR(CAN, "Usage cdefp Num");
    }

    return res;
}

bool can_diag_enhanced_fifo_mem_command(int32_t argc, char* argv[]) {
    uint8_t num = 0;
    uint32_t size = 0;
    bool res = false;

    if(0 <= argc) {
        num = 0;
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &size);
        log_res(CAN, res, "Size");
    }

    if(res) {
        res = can_diag_enhanced_fifo_region(num, size);
        log_res(CAN, res, "EnhFiFoRegion");
    } else {
        LOG_ERROR(CAN, "Usage cdefm Num");
    }

    return res;
}

/*
 cdef 1
 */
bool can_diag_enhanced_fifo_filter_command(int32_t argc, char* argv[]) {
    uint8_t num = 0;
    bool res = false;

    if(0 <= argc) {
        num = 0;
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "Num");
    }

    if(res) {
        res = can_diag_enhanced_rx_fifo_filter(num);
        log_res(CAN, res, "EnhRxFiFoFilters");
        res = can_diag_enhanced_rx_fifo_filter_std(num);
        res = can_diag_enhanced_rx_fifo_filter_ext(num);
    } else {
        LOG_ERROR(CAN, "Usage cdefm Num");
    }

    return res;
}

/*
 csic 1 0xA
 */
bool can_std_id_check_command(int32_t argc, char* argv[]) {
    bool res = false;

    uint8_t num = 0;
    uint32_t can_id = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "CanNum");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &can_id);
        log_res(CAN, res, "Id");
    }

    if(res) {
        switch(argc) {
        case 1: {
            res = can_std_id_check_all(num);
            log_res(CAN, res, "StdIdCheck");
        } break;
        case 2: {

            res = can_enhanced_id_check_std(num, can_id);
            log_res(CAN, res, "StdIdCheck");

        } break;
        default: {

        } break;
        }

    } else {
        LOG_ERROR(CAN, "Usage: csic N Id");
    }
    return res;
}

bool can_ext_id_check_command(int32_t argc, char* argv[]) {
    bool res = false;

    uint8_t num = 0;
    uint32_t can_id = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "CanNum");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &can_id);
        log_res(CAN, res, "Id");
    }

    if(res) {
        switch(argc) {
        case 1: {
            res = can_ext_id_check_all(num);
            log_res(CAN, res, "ExtIdCheck");
        } break;
        case 2: {
            res = can_enhanced_id_check_ext(num, can_id);
            log_res(CAN, res, "ExtIdCheck");

        } break;
        default: {

        } break;
        }

    } else {
        LOG_ERROR(CAN, "Usage: ceic N Id");
    }
    return res;
}

static CanFilterIdAccess_t can_id_access_token_to_cmd(const char cmd) {
    CanFilterIdAccess_t access = CAN_FILTER_ID_ACCESS_UNDEF;
    switch(cmd) {
    case 'a':
        access = CAN_FILTER_ID_ACCESS_ALLOW;
        break;
    case 'b':
        access = CAN_FILTER_ID_ACCESS_BAN;
        break;
    default:
        break;
    }
    return access;
}

bool can_filter_ctrl_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint32_t can_id = 0;
    char cmd = '?';

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "CanNum");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &can_id);
        log_res(CAN, res, "Id");
    }

    if(3 <= argc) {
        cmd = argv[2][0];
    }

    if(res) {
        CanFilterIdAccess_t accsess_cmd = can_id_access_token_to_cmd(cmd);
        res = can_filter_ctrl(num, can_id, accsess_cmd);
        log_res(CAN, res, "AccessCmd");
    } else {
        LOG_ERROR(CAN, "Usage: cfc N Id access");
    }

    return res;
}
