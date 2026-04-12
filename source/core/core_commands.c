#include "core_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "boot_driver.h"
#include "common_diag.h"
#include "convert.h"
#include "core_diag.h"
#include "core_driver.h"
#include "data_utils.h"
#include "flash_config.h"
#include "log.h"
#include "str_utils.h"
//#include "sys_config.h"
#include "table_utils.h"

#ifdef HAS_LOG_UTILS
#include "log_utils.h"
#endif

#ifdef HAS_STREAM
#include "debug_info.h"
#endif

#ifdef HAS_ARRAY
#include "array.h"
#endif
/*
 cao 0x20000000
 */
bool core_address_offset_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t address = 0;
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &address);
    }

    if(res) {
        LOG_INFO(CORE, "Addr:0x%x", address);
        uint32_t offset_size = cortex_offset_size_get(address);
        LOG_INFO(CORE, "Addr:0x%x,Size:%u=%u", address, offset_size, BYTES_2_KBYTES_U(offset_size));
    }
    return res;
}

bool core_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    res = core_diag();
    if(res) {
    } else {
        LOG_ERROR(CORE, "Usage: cd");
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
        LOG_ERROR(CORE, "Usage: reboot");
    }
    return res;
}

static bool core_test_stack(uint32_t stack_top_addr, uint32_t stack_size) {
    bool res = false;
    uint32_t max_depth;
    for(max_depth = 0;; max_depth++) {
        res = try_recursion(stack_top_addr, max_depth, &stack_size);
        if(res) {
            cli_printf("\rDepth:%u,calls:%u,byteOk!", max_depth, stack_size);
        } else {
            LOG_ERROR(CORE, "error");
        }
    }
    return res;
}

bool cmd_try_stack(int32_t argc, char* argv[]) {
    bool res = false;

    uint32_t stack_top_addr = boot_stack_top_addr_get(0);
    cli_printf("TopStackAddr:0x%08X" CRLF, stack_top_addr);

    uint32_t max_depth = 0;
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &max_depth);
    }

#ifdef HAS_CORE_EXT
#if 0
    uint16_t real_size = 0;
    uint32_t cur_stack_use = top_stack_val - ((uint32_t)&real_size);
    cli_printf("curStackUsage: %u byte" CRLF, cur_stack_use);
    cli_printf("remStack: %d byte" CRLF, EXPECT_STACK_SIZE - cur_stack_use);

    uint32_t busy = 0;
    uint32_t max_cont_patt = 0;
    res = array_max_cont((uint8_t*)top_stack_val - EXPECT_STACK_SIZE - 1, EXPECT_STACK_SIZE, 0, &max_cont_patt);
    busy = EXPECT_STACK_SIZE - max_cont_patt;
    if(res) {
        cli_printf("maxFree:%d byte" CRLF, max_cont_patt);
        cli_printf("maxBusy:%d byte" CRLF, busy);
        cli_printf("maxUsage:%s %%" CRLF, FloatToStr(busy,3) );
    }
#endif
    uint32_t stack_size = 0;
    if(0 == argc) {
#ifdef HAS_DEBUG
        // parse_stack();
#endif
        res = core_test_stack(stack_top_addr, stack_size);
    }

    if(res) {
        res = try_recursion(stack_top_addr, max_depth, &stack_size);
        if(res) {
            LOG_INFO(CORE, "depth:%u,StackSize:%u,byte Ok!", max_depth, stack_size);
        } else {
            LOG_ERROR(CORE, "error");
        }
    } else {
        LOG_ERROR(CORE, "Usage: tstk depth");
    }
#endif
    return res;
}

bool core_exeption_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t out_val = 0;
    res = core_exeption(210, &out_val);
    LOG_INFO(CORE, "out_val:%u", out_val);
    return res;
}

bool core_check_address_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t address = 0;
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &address);
        log_info_res(CORE, res, "address");
    }

    if(res) {
        volatile const char* p_address = (char*)address;
        res = core_check_address(p_address);
        if(res) {
            LOG_INFO(CORE, "Addr:0x%08p->%s", p_address, YesNoToStr(res));
        } else {
            LOG_ERROR(CORE, "Addr:0x%08p->%s", p_address, YesNoToStr(res));
        }
    } else {
        LOG_ERROR(CORE, "Usage: ca address");
    }
    return res;
}

bool stack_print_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t core = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &core);
        log_info_res(CORE, res, "Core");
    }

    if(res) {
        res = core_stack_print(core);
        log_info_res(CORE, res, "StackPrint");
    } else {
        LOG_ERROR(CORE, "Usage: stkp CoreNum");
    }
    return res;
}
