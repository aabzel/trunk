#include "bootloader_commands.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

#include "bit_utils.h"
#include "boot_driver.h"
#include "bootloader.h"
#include "convert.h"
#include "core_driver.h"
#include "ctype.h"
#include "data_utils.h"
#include "debug_info.h"
#ifdef HAS_DEBUGGER
#include "debugger.h"
#endif
#include "flash_mcal.h"
#include "log.h"
#include "log_utils.h"
#ifdef HAS_FLASH_NVS
#include "flash_nvs_const.h"
#endif
#include "ostream.h"
#include "sys_config.h"
#include "table_utils.h"
#include "writer_config.h"

static bool bootloader_scan_app(void) {
    bool res = false;
#ifdef HAS_DEBUGGER
    uint32_t address = 0;
    uint32_t num = 1;
    (void)num;
    static const table_col_t cols[] = {{7, "No"}, {12, "address"}, {12, "stack"}, {12, "resetH"}};
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    for(address = NOR_FLASH_BASE; address < (NOR_FLASH_END - 8); address += 4) {
        uint32_t top_stack_val = 0;
        top_stack_val = read_addr_32bit(address);
        uint32_t reset_handler_addr = 0;
        reset_handler_addr = read_addr_32bit(address + 4);
        bool res1 = false;
        bool res2 = false;
        res1 = is_ram_addr(top_stack_val);
        res2 = is_flash_addr(reset_handler_addr);
        if(res1 && res2) {
            cli_printf(TSEP);
            cli_printf(" %5u " TSEP, num);
            cli_printf(" 0x%08x " TSEP, address);
            cli_printf(" 0x%08x " TSEP, top_stack_val);
            cli_printf(" 0x%08x " TSEP, reset_handler_addr);
            cli_printf(CRLF);
            num++;
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
#endif /*HAS_DEBUGGER*/
    return res;
}

#if defined(CC26XX)
static bool parse_bl_config(uint32_t reg_val) {
    uint32_t sub_val = 0;
    sub_val = extract_subval_from_32bit(reg_val, 7, 0);
    cli_printf("%sables the boot loader backdoor." CRLF, (0xC5 == sub_val) ? "en" : "dis");

    sub_val = extract_subval_from_32bit(reg_val, 15, 8);
    cli_printf("level checked at DIO%u" CRLF, sub_val);

    cli_printf("Active %s" CRLF, ((1 << 16) == (reg_val & (1 << 16))) ? "high" : "low");

    sub_val = extract_subval_from_32bit(reg_val, 31, 24);
    cli_printf("Boot loader is %sabled" CRLF, (0xC5 == sub_val) ? "en" : "dis");
    return true;
}
#endif

bool bootloader_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
#ifdef CC26XX
        uint32_t reg_val;
        reg_val = read_addr_32bit(CCFG_BASE + CCFG_O_BL_CONFIG);
        res = parse_bl_config(reg_val);
#endif
        bootloader_scan_app();
    } else {
        LOG_ERROR(BOOTLOADER, "Usage: bd");
    }
    return res;
}

bool bootloader_jump_addr_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t app_start_address = 0;
    if(1 == argc) {
        res = try_str2uint32(argv[0], &app_start_address);
        if(false == res) {
            LOG_ERROR(BOOTLOADER, "Err to spot addr", argv[0]);
        }
    } else {
        LOG_ERROR(BOOTLOADER, "Usage: jm app_start_address");
    }
    if(res) {
        res = boot_jump_to_code(app_start_address);
    }
    return res;
}

bool bootloader_erase_app_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
#ifdef CC26XX
        res = flash_erase_pages(APP_PAGE_START, APP_PAGE_START + APP_PAGE_CNT - 1);
        if(res) {
            LOG_INFO(BOOTLOADER, "Erased %u pages", APP_PAGE_CNT);
        } else {
            LOG_ERROR(BOOTLOADER, "Err app erase");
        }
#endif

    } else {
        LOG_ERROR(BOOTLOADER, "Usage: ea");
    }
    return res;
}

bool bootloader_proc_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = bootloader_proc();
        if(res) {
            LOG_ERROR(BOOTLOADER, "JumpOk!");
        } else {
            LOG_ERROR(BOOTLOADER, "JumpErr");
        }

    } else {
        LOG_ERROR(BOOTLOADER, "Usage: bp");
    }
    return res;
}

bool bootloader_launch_app_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t bootloader_cmd = BOOT_CMD_LAUNCH_APP_CRC;
    if(0 <= argc) {
        bootloader_cmd = BOOT_CMD_LAUNCH_APP_CRC;
        res = true;
    }
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &bootloader_cmd);
        if(false == res) {
            LOG_ERROR(BOOTLOADER, "ParseBootCmdErr", argv[0]);
        }
    }
    if(res) {
        res = bootloader_launch_app(bootloader_cmd);
        if(res) {
            LOG_ERROR(BOOTLOADER, "OK");
        } else {
            LOG_ERROR(BOOTLOADER, "Err launch app");
        }
    } else {
        LOG_ERROR(BOOTLOADER, "Usage: la");
    }
    return res;
}

bool bootloader_reboot_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = bootloader_reboot();
    return res;
}
