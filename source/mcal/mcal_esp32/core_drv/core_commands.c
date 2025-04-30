#include "core_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "array.h"
#include "base_cmd.h"
#include "boot_cfg.h"
#include "convert.h"
#include "core_driver.h"
#include "core_utils.h"
#include "ctype.h"
#include "data_utils.h"
#include "debug_info.h"
#include "diag_page_nums.h"
#include "diag_report.h"
#include "io_utils.h"
#include "log.h"
#include "ostream.h"
#include "str_utils.h"
#include "sys_tick.h"
#include "table_utils.h"

// extern void intDefaultHandler(void);
extern int main(void);
bool core_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        uint32_t clock = 0;
        // is cache enabled
        /* Obtain the number of the currently executing interrupt. */
        // io_printf("R0: 0x%08x" CRLF, R0);
        uint64_t ble_mac = 0;
        io_printf("main: 0x%08p" CRLF, main);
        print_sys_info();

        res = true;
    } else {
        LOG_ERROR(SYS, "Usage: cd");
    }
    return res;
}

bool vector_table_command(int32_t argc, char* argv[]) {
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

bool cmd_soft_reboot(int32_t argc, char* argv[]) {
    (void)(argv);
    bool res = false;
    if(0 == argc) {
        res = true;
        LOG_INFO(SYS, "Reboot device");
        res = reboot();
    } else {
        LOG_ERROR(SYS, "Usage: reboot");
    }
    return res;
}

#define EXPECT_STACK_SIZE (4096 * 10)
bool cmd_try_stack(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t max_depth = 0;
    uint32_t busy = 0;
    uint32_t stack_size = 0;
    uint16_t real_size = 0;
    uint32_t top_stack_val = *((uint32_t*)(APP_START_ADDRESS));
    uint32_t cur_stack_use = top_stack_val - ((uint32_t)&real_size);
    io_printf("curStackUsage: %u byte" CRLF, cur_stack_use);
    io_printf("remStack: %d byte" CRLF, EXPECT_STACK_SIZE - cur_stack_use);

    uint32_t max_cont_patt = 0;
    res = array_max_cont((uint8_t*)top_stack_val - EXPECT_STACK_SIZE, EXPECT_STACK_SIZE, 0, &max_cont_patt);
    busy = EXPECT_STACK_SIZE - max_cont_patt;
    if(res) {
        io_printf("max free: %d byte" CRLF, max_cont_patt);
        io_printf("max busy: %d byte" CRLF, busy);
        io_printf("max usage: %5.1f %%" CRLF, ((float)100 * busy) / ((float)EXPECT_STACK_SIZE));
    }
    if(0 == argc) {
#ifdef HAS_DEBUG
        parse_stack();
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
    return res;
}
