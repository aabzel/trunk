#include "sw_component_commands.h"

#include "convert.h"
#include "log.h"
#include "sw_component_mcal.h"

bool sw_component_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SW_COMPONENT, res, "Num");
    }

    if(res) {
        res = sw_component_raw_reg_diag(num);
        log_info_res(SW_COMPONENT, res, "RegMap");
    } else {
        LOG_ERROR(SW_COMPONENT, "Usage: sw_componentrr num");
    }
    return res;
}

bool sw_component_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SW_COMPONENT, res, "Num");
    }

    if(res) {
        res = sw_component_diag_one(num);
        log_info_res(SW_COMPONENT, res, "Diag");

        res = sw_component_diag();
        log_info_res(SW_COMPONENT, res, "Diag");
    } else {
        LOG_ERROR(SW_COMPONENT, "Usage: fdat");
    }

    return res;
}

bool sw_component_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SW_COMPONENT, res, "Num");
    }

    if(0 == argc) {
        res = sw_component_mcal_init();
        log_info_res(SW_COMPONENT, res, "Init");
    }
    return res;
}
