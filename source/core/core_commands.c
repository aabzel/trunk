#include "core_commands.h"

#include <inttypes.h>
#include <stdio.h>

#ifdef HAS_ARRAY
#include "array.h"
#endif

#include "convert.h"
#include "core_diag.h"
#include "core_driver.h"
#include "data_utils.h"
#ifdef HAS_STREAM
#include "debug_info.h"
#endif

#include "flash_config.h"
#include "log.h"
#ifdef HAS_LOG_UTILS
#include "log_utils.h"
#include "ostream.h"
#endif

#include "str_utils.h"
//#include "sys_config.h"
#include "table_utils.h"

extern int main(void);
bool core_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        // is cache enabled
        cli_printf("main: 0x%08p" CRLF, main);
        uint32_t top_app_stack_val = *((uint32_t*)(APP_START_ADDRESS));
        int32_t max_stack_depth = top_app_stack_val - ((int32_t)low_stack);
        LOG_WARNING(SYS, "MaxStackDepth: %d byte LowStack 0x%p", max_stack_depth, low_stack);
        print_sys_info();
        res = true;
    } else {
        LOG_ERROR(SYS, "Usage: cd");
    }
    return res;
}

bool cmd_soft_reboot(int32_t argc, char* argv[]) {
    (void)(argv);
    bool res = false;
    if(0 == argc) {
        res = true;
    }
    if(res) {
        res = core_reboot();
    } else {
        LOG_ERROR(SYS, "Usage: reboot");
    }
    return res;
}

bool cmd_try_stack(int32_t argc, char* argv[]) {
    bool res = false;
#ifdef HAS_CORE_EXT
    uint32_t max_depth = 0;
    uint32_t busy = 0;
    uint16_t real_size = 0;
    uint32_t top_stack_val = *((uint32_t*)(APP_START_ADDRESS));
    cli_printf("TopStackVal: 0x%08x byte" CRLF, top_stack_val);
    uint32_t cur_stack_use = top_stack_val - ((uint32_t)&real_size);
    cli_printf("curStackUsage: %u byte" CRLF, cur_stack_use);
    cli_printf("remStack: %d byte" CRLF, EXPECT_STACK_SIZE - cur_stack_use);

    uint32_t max_cont_patt = 0;
    res = array_max_cont((uint8_t*)top_stack_val - EXPECT_STACK_SIZE - 1, EXPECT_STACK_SIZE, 0, &max_cont_patt);
    busy = EXPECT_STACK_SIZE - max_cont_patt;
    if(res) {
        cli_printf("max free: %d byte" CRLF, max_cont_patt);
        cli_printf("max busy: %d byte" CRLF, busy);
        cli_printf("max usage: %5.1f %%" CRLF, ((float)100 * busy) / ((float)EXPECT_STACK_SIZE));
    }
    uint32_t stack_size = 0;
    if(0 == argc) {
#ifdef HAS_DEBUG
        // parse_stack();
#endif

        for(max_depth = 0;; max_depth++) {
            res = try_recursion(max_depth, &stack_size);
            if(false == res) {
                LOG_ERROR(SYS, "error");
            } else {
                LOG_INFO(SYS, "depth %u calls %u byte Ok!", max_depth, stack_size);
            }
        }
    }

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &max_depth);
    }

    if(res) {
        res = try_recursion(max_depth, &stack_size);
        if(false == res) {
            LOG_ERROR(SYS, "error");
        } else {
            LOG_INFO(SYS, "depth %u calls %u byte Ok!", max_depth, stack_size);
        }
    } else {
        LOG_ERROR(SYS, "Usage: tstk depth");
    }
#endif
    return res;
}

bool core_exeption_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t out_val = 0;
    res = core_exeption(210, &out_val);
    LOG_INFO(SYS, "out_val:%u", out_val);
    return res;
}
