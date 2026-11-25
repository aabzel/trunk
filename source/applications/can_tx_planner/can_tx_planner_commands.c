#include "can_tx_planner_commands.h"

#include "can_commands.h"
#include "can_rx_hist_diag.h"
#include "can_tx_planner_mcal.h"
#include "convert.h"
#include "log.h"

/* ctpd 1 */
bool can_tx_planner_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t can_num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &can_num);
        // log_info_res(CAN_TX_PLANNER, res, "CanNum");
        // log_info_res(CAN_TX_PLANNER, res, "Diag");
    }

    if(res) {
        switch(argc) {
        case 1: {
            can_rx_hist_diag_one(can_num);
            res = can_tx_planner_diag_one(can_num);

        } break;
        case 0: {
            res = can_tx_planner_diag();
            log_info_res(CAN_TX_PLANNER, res, "Diag");

        } break;
        default: {

        } break;
        }
    } else {
        LOG_ERROR(CAN_TX_PLANNER, "Usage: ctpd canNum");
    }

    return res;
}

bool can_tx_planner_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(CAN_TX_PLANNER, res, "Num");
    }

    if(0 == argc) {
        res = can_tx_planner_mcal_init();
        log_info_res(CAN_TX_PLANNER, res, "Init");
    }
    return res;
}

/*
ctpsp 1 10
 * */
bool can_tx_planner_set_period_command(int32_t argc, char* argv[]) {
    bool res = false;
    LOG_INFO(CAN, "argc:%u", argc);
    uint8_t num = 0;
    uint32_t period_ms = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(CAN_TX_PLANNER, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &period_ms);
        log_info_res(CAN_TX_PLANNER, res, "TxPeriodMs");
    }

    if(res) {
        res = can_tx_planner_set_period(num, period_ms);
        log_info_res(CAN_TX_PLANNER, res, "SetPeriod");
    } else {
        LOG_ERROR(CAN_TX_PLANNER, "Usage: ctpsp N TxPeriod");
    }
    return res;
}

/*
can_tx_planner_set 1 1 3000  1 0xc2 2 0x12345678 ;ctpd
can_tx_planner_set 1 0 5000  1 0xc2 2 0x123456 ; ctpd
can_tx_planner_set 1 1 5000  1 0xc2 2 0x123456 ; ctpd
can_tx_planner_set 2 0 5000  1 0xc2 2 0x556644;ctpd
  */
bool can_tx_planner_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    LOG_INFO(CAN, "argc:%u", argc);
    uint8_t num = 0;
    uint32_t period_ms = 0;
    CanMessage_t Message = {0};
    bool en = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(CAN_TX_PLANNER, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2bool(argv[1], &en);
        log_info_res(CAN_TX_PLANNER, res, "en");
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &period_ms);
        log_info_res(CAN_TX_PLANNER, res, "TxPeriodMs");
    }

    if(7 <= argc) {
        res = can_parse_mesg(argc, argv, 3, &Message);
        log_info_res(CAN_TX_PLANNER, res, "TxMessage");
    }

    if(res) {
        res = can_tx_planner_set(num, en, period_ms, &Message);
        log_info_res(CAN_TX_PLANNER, res, "Set");
    } else {
        LOG_ERROR(CAN_TX_PLANNER, "Usage: ctps N En TxPeriod Mesg");
    }
    return res;
}
