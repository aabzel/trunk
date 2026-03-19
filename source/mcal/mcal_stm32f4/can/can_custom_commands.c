#include "can_custom_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "array_diag.h"
#include "can_core.h"
#include "can_mcal.h"
#include "common_diag.h"
#include "convert.h"
#include "debug_info.h"
#include "log.h"

bool can_diag_custom_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = can_diag_custom();
        log_res(CAN, res, "DiagCustom");
    } else {
        LOG_ERROR(CAN, "Usage cdc");
    }

    return res;
}

bool can_interrupt_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    bool on_off = false;

    if(0 <= argc) {
        res = true;
        num = 0;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2bool(argv[1], &on_off);
        log_res(CAN, res, "En");
    }

    if(res) {
        res = can_interrupt_ctrl(num, on_off);
        log_res(CAN, res, "IntCtrl");

    } else {
        LOG_ERROR(CAN, "Usage cani Num OnOff");
    }

    return res;
}

/*
 csm 0 1 0x55 0x55AA

 ll can debug;  csm 0 15 0x55 0x55AA

 ll can debug;  csm 0 5 0x55 0x55AA

 ll can debug;  csm 0 3 0x5A 0x55AA1122
 csm 0 13 0x5A 0x55AA1122
 csm 0 13 0x05 0x55AA1122
  */
bool can_send_custom_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t array_len = 0;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
        num = 0;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "CanNum");
    }

    if(res) {
        if(array_len <= 8) {
        }
    } else {
        LOG_ERROR(CAN, "Usage: csm instance mb Id hex_string");
    }
    return res;
}

bool can_diag_tx_mailbox_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = can_diag_tx_mailbox();
        log_res(CAN, res, "DiagTxMailBox");
    } else {
        LOG_ERROR(CAN, "Usage: cdtm instance");
    }
    return res;
}

bool can_diag_filters_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
        num = 1;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "CanNum");
    }

    if(res) {
        res = can_diag_filters(num);
        log_res(CAN, res, "DiagFilters");
    } else {
        LOG_ERROR(CAN, "Usage: cdf Num");
    }
    return res;
}
