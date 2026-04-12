#include "sw_component_commands.h"

#include "convert.h"
#include "log.h"
#include "sw_component.h"

bool sw_component_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = sw_component_reg_map();
    log_info_res(SW_COMPONENT,res,"Reg");
    return res;
}

bool sw_component_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }
    if(res) {
        res = sw_component_diag();
        log_info_res(SW_COMPONENT,res,"Diag");
    } else {
        LOG_ERROR(SW_COMPONENT, "Usage: fdat");
    }

    return res;
}

bool sw_component_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = sw_component_mcal_init();
        log_info_res(SW_COMPONENT,res,"Init");
    }
    return res;
}
