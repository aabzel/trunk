#include "can_rx_hist_commands.h"

#include "can_rx_hist_mcal.h"
#include "convert.h"
#include "log.h"

#ifdef HAS_CAN_TX_PLANNER
#include "can_tx_planner_diag.h"
#endif

bool can_rx_hist_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(CAN_RX_HIST, res, "Num");
    }

    if(res) {
        switch(argc) {
        case 0: {
            res = can_rx_hist_diag();
            log_info_res(CAN_RX_HIST, res, "Diag");
        } break;
        case 1: {
            res = can_rx_hist_diag_one(num);
            log_info_res(CAN_RX_HIST, res, "Diag");
        } break;
        default:
            res = false;
            break;
        }

    } else {
        LOG_ERROR(CAN_RX_HIST, "Usage: crhd CanNum");
    }

    return res;
}

bool can_rx_hist_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(CAN_RX_HIST, res, "Num");
    }

    if(0 == argc) {
        res = can_rx_hist_mcal_init();
        log_info_res(CAN_RX_HIST, res, "Init");
    }
    return res;
}

bool can_traffx_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t can_num = 0;

    if(0 <= argc) {
        res = true;
        can_num = 1;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &can_num);
        log_info_res(CAN_RX_HIST, res, "Num");
    }

    if(res) {
        res = can_rx_hist_diag_one(can_num);
#ifdef HAS_CAN_TX_PLANNER
        res = can_tx_planner_diag_one(can_num);
#endif
    } else {
        LOG_ERROR(CAN_RX_HIST, "Usage: ctd CanNum");
    }

    return res;
}
