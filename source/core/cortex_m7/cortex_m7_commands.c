#include "cortex_m7_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "array.h"
#include "convert.h"
#include "core_diag.h"
#include "core_driver.h"
//#include "core_utils.h"
#include "data_utils.h"
#include "debug_info.h"
#include "flash_config.h"
//#include "cli_utils.h"
#include "cortex_m7_diag.h"
#include "cortex_m7_driver.h"
#include "log.h"
#include "str_utils.h"
#include "sys_config.h"
#include "table_utils.h"

extern int main(void);
bool cortex_m7_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        // is cache enabled
        /* Obtain the number of the currently executing interrupt. */
        // cli_printf("R0: 0x%08x" CRLF, R0);
        cli_printf("main: 0x%08p" CRLF, main);
        uint32_t top_app_stack_val = *((uint32_t*)(APP_START_ADDRESS));
        int32_t max_stack_depth = top_app_stack_val - ((int32_t)low_stack);
        LOG_WARNING(SYS, "MaxStackDepth: %d byte LowStack 0x%p", max_stack_depth, low_stack);
        print_sys_info();

        uint32_t reg = __get_CONTROL();
        parse_control_reg(reg);

        reg = __get_FAULTMASK();
        parse_faultmask_reg(reg);

        reg = __get_BASEPRI();
        parse_basepri_reg(reg);
        res = true;

        res = CortexM7_SCB_Diag(SCB);
    } else {
        LOG_ERROR(SYS, "Usage: cd");
    }
    return res;
}

bool vector_table_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t vectors_table_base = SCB->VTOR;
    if(0 == argc) {
        res = true;
    }

    if(1 == argc) {
        res = try_str2uint32(argv[0], &vectors_table_base);
        if(false == res) {
            LOG_ERROR(SYS, "Unable to extract vectors_table_base %s", argv[0]);
        }
    }

    if(res) {
        res = print_vector_table(vectors_table_base);
    } else {
        LOG_ERROR(SYS, "Usage: vt");
    }
    return res;
}

bool cortex_m7_exceptions_command(int32_t argc, char* argv[]) {
    bool on_off = true;
    bool res = false;
    if(1 == argc) {
        res = try_str2bool(argv[0], &on_off);
    }
    if(res) {
        res = cortex_m7_exceptions(on_off);
        if(res) {
            LOG_INFO(SYS, LOG_OK);
        }
    } else {
        LOG_ERROR(SYS, "Usage: cm7ex OnOff");
    }
    return res;
}

bool cortex_m7_exceptions_nmi_command(int32_t argc, char* argv[]) {
    bool on_off = true;
    bool res = false;
    if(1 == argc) {
        res = try_str2bool(argv[0], &on_off);
    }
    if(res) {
        res = cortex_m7_exceptions_nmi(on_off);
        if(res) {
            LOG_INFO(SYS, LOG_OK);
        }
    } else {
        LOG_ERROR(SYS, "Usage: cm7exn OnOff");
    }
    return res;
}
