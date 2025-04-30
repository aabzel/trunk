#include "ds_twr_commands.h"

#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#include "convert.h"
#include "debug_info.h"
#include "ds_twr.h"
#include "ds_twr_initiator.h"
#ifdef HAS_DS_TWR_DIAG
#include "ds_twr_diag.h"
#endif
#include "log.h"

bool ds_twr_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = DsTwrDiagNode(&DsTwrItem);
    }
    return res;
}

bool ds_twr_start_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = ds_twr_start(&DsTwrItem);
    }
    return res;
}

bool ds_twr_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = ds_twr_init_one(&DsTwrConfig, &DsTwrItem);
    }
    return res;
}

bool ds_twr_send_poll_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = ds_twr_send_poll(&DsTwrItem);
        if(res) {
            LOG_INFO(DS_TWR, "SendPollOK");
        } else {
            LOG_ERROR(DS_TWR, "SendPollErr");
        }
    }
    return res;
}

bool ds_twr_calibrate_command(int32_t argc, char* argv[]) {
    bool res = false;
    double dist_m = 1.0;
    if(1 == argc) {
        res = try_str2double(argv[0], &dist_m);
        if(false == res) {
            LOG_ERROR(DS_TWR, "ParseErr Dist");
        }
    }

    if(res) {
        res = ds_twr_calibrate(&DsTwrItem, dist_m);
        if(res) {
            LOG_INFO(DS_TWR, "CalibrateOK");
        } else {
            LOG_ERROR(DS_TWR, "CalibrateErr");
        }
    }
    return res;
}

bool ds_twr_enable_continuous_command(int32_t argc, char* argv[]) {
    bool on_off = true;
    bool res = false;
    if(1 == argc) {
        res = try_str2bool(argv[0], &on_off);
        if(false == res) {
            LOG_ERROR(DS_TWR, "ParseErr OnOff");
        }
    }
    if(res) {
        res = ds_twr_enable_continuous(&DsTwrItem, on_off);
        if(res) {
            LOG_INFO(DS_TWR, "SetCont %s OK", OnOff2Str(on_off));
        } else {
            LOG_ERROR(DS_TWR, "EnContErr");
        }
    } else {
        LOG_ERROR(DS_TWR, "Usage dsec OnOff");
    }
    return res;
}

bool ds_twr_distances_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = DsTwrDiagDistances(DsTwrItem.IdInfo, DsTwrItem.known_nodes_cnt);
    } else {
        LOG_ERROR(DS_TWR, "Usage dst");
    }
    return res;
}
