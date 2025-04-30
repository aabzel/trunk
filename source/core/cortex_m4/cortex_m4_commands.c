#include "cortex_m4_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "array.h"
#include "convert.h"
#include "core_diag.h"
#include "cortex_m4_driver.h"
#include "data_utils.h"
#include "debug_info.h"
#include "flash_config.h"
#ifdef HAS_CMSIS
#include "cmsis_gcc.h"
#endif
#include "log.h"
#include "microcontroller_const.h"
#include "str_utils.h"
#include "table_utils.h"

extern int main(void);

uint8_t* cm_4_low_stack = (uint8_t*)RAM_END;

bool cortex_m4_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        // is cache enabled
        /* Obtain the number of the currently executing interrupt. */
        // cli_printf("R0: 0x%08x" CRLF, R0);
        cli_printf("main:0x%08p" CRLF, main);
        uint32_t top_app_stack_val = *((uint32_t*)(APP_START_ADDRESS));
        int32_t max_stack_depth = top_app_stack_val - ((int32_t)cm_4_low_stack);
        LOG_WARNING(SYS, "MaxStackDepth: %d byte LowStack 0x%p", max_stack_depth, cm_4_low_stack);
        print_sys_info();

#ifdef HAS_CORTEX_M4_DIAG
        res = CortexM4ScbDiag(SCB);
        uint32_t reg = __get_CONTROL();
        parse_control_reg(reg);

      //  reg = __get_FAULTMASK();
      //  parse_faultmask_reg(reg);

      //  reg = __get_BASEPRI();
       // parse_basepri_reg(reg);
        res = true;
#endif
    } else {
        LOG_ERROR(SYS, "Usage: cd");
    }
    return res;
}

bool cortex_m4_vector_table_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t vectors_table_base = 0x20004e00;
    if(0 == argc) {
        print_vector_table(vectors_table_base);
        res = true;
    } else if(1 == argc) {
        res = true;
        res = try_str2uint32(argv[0], &vectors_table_base);
        if(false == res) {
            LOG_ERROR(SYS, "Unable to extract vectors_table_base %s", argv[0]);
        }

        if(true == res) {
            print_vector_table(vectors_table_base);
        }
    } else {
        LOG_ERROR(SYS, "Usage: cd ");
    }
    return res;
}

bool cortex_m4_exceptions_command(int32_t argc, char* argv[]) {
    bool on_off = true;
    bool res = false;
    if(1 == argc) {
        res = try_str2bool(argv[0], &on_off);
    }
    if(res) {
        res = cortex_m4_exceptions(on_off);
        if(res) {
            LOG_INFO(SYS, LOG_OK);
        }
    } else {
        LOG_ERROR(SYS, "Usage: cm4ex OnOff");
    }
    return res;
}

bool cortex_m4_coproc_access_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t coprocessors = 0;
    uint8_t access = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &coprocessors);
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &access);
    }

    if(res) {
        switch(argc) {
        case 0: {
            for(coprocessors = 0; coprocessors <= 16; coprocessors++) {
                access = 0;
                res = cortex_m4_coproc_access_get(coprocessors, (CoProcAccess_t*)&access);
                if(res) {
                    LOG_INFO(SYS, "Get,CP:%u,Access:%u=%s", coprocessors, access, CortecM4CoProcAccessToStr(access));
                }
            }
        } break;
        case 1: {
            res = cortex_m4_coproc_access_get(coprocessors, (CoProcAccess_t*)&access);
            LOG_INFO(SYS, "Get,CP:%u,Access:%u=%s", coprocessors, access, CortecM4CoProcAccessToStr(access));
        } break;
        case 2: {
            LOG_INFO(SYS, "Set,CP:%u,Access:%u=%s", coprocessors, access, CortecM4CoProcAccessToStr(access));
            res = cortex_m4_coproc_access_set(coprocessors, (CoProcAccess_t)access);

        } break;
        default: {
        } break;
        } // switch(argc)
    } else {
        LOG_ERROR(SYS, "Usage: cm4cop CP Access");
    }
    return res;
}

bool cortex_m4_exceptions_nmi_command(int32_t argc, char* argv[]) {
    bool on_off = true;
    bool res = false;
    if(1 == argc) {
        res = try_str2bool(argv[0], &on_off);
    }
    if(res) {
        res = cortex_m4_exceptions_nmi(on_off);
        if(res) {
            LOG_INFO(SYS, LOG_OK);
        }
    } else {
        LOG_ERROR(SYS, "Usage: cm4exn OnOff");
    }
    return res;
}

bool cortex_m4_breakpoints_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint32_t breakpoint_addr = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &breakpoint_addr);
    }

    if(res) {
        switch(argc) {
        case 0: {
            res = cortex_m4_breakpoints();
        } break;
        case 2: {
            res = cortex_m4_breakpoint_set(num, breakpoint_addr);
        } break;
        default: {
            res = false;
        } break;
        }
    } else {
        LOG_ERROR(SYS, "Usage: cm4br BreakPointAddr");
    }
    return res;
}
