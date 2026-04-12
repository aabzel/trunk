#include "boot_commands.h"

#include "boot_driver.h"
#include "convert.h"
#include "float_diag.h"
#include "log.h"
#include "microcontroller_const.h"
#include "rational_num_diag.h"

bool boot_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = boot_mcal_init();
    log_info_res(BOOT, res, "Init");
    return res;
}

bool boot_reboot_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = boot_reboot();
    log_info_res(BOOT, res, "ReBoot");
    return res;
}

bool boot_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = boot_diag();
    log_info_res(BOOT, res, "Diag");
    return res;
}

bool boot_seek_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t mem_start = ROM_START;
    uint32_t size = ROM_SIZE;

    if(0 <= argc) {
        mem_start = ROM_START;
        size = ROM_SIZE;
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &mem_start);
        log_info_res(BOOT, res, "Start");
        size = ROM_END - mem_start;
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &size);
        log_info_res(BOOT, res, "Size");
    }

    if(res) {
        res = boot_seek_vector_table(mem_start, size);
        log_info_res(BOOT, res, "Seek");
    } else {
        LOG_ERROR(BOOT, "Usage: bs address size");
    }
    return res;
}

bool boot_stack_paint_command(int32_t argc, char* argv[]) {
    bool res = true;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(BOOT, res, "Start");
    }

    if(res) {
        FloatFixPoint_t stack_used = {0};
        res = boot_stack_paint(num, &stack_used);
        log_info_res(BOOT, res, "StackPaint");
        if(res) {
            LOG_INFO(BOOT, "StackUsed:%s", FloatFixToStr(&stack_used));
        }
    } else {
        LOG_ERROR(BOOT, "Usage: bsp num");
    }

    return res;
}
