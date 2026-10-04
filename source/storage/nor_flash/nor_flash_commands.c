#include "nor_flash_commands.h"

#include <stdio.h>

#include "convert.h"
#include "debug_info.h"
#include "log.h"
#include "nor_flash_diag.h"
#include "nor_flash_drv.h"
#include "nor_flash_types.h"

bool nor_flash_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t flash_num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &flash_num);
        log_res(NOR_FLASH, res,"Num");
    }

    if(res) {
        res = nor_flash_diag(flash_num);
        log_res(NOR_FLASH, res,"Diag");
    } else {
        LOG_ERROR(NOR_FLASH, "Usage: nfd num");
    }
    return res;
}

bool nor_flash_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t flash_num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &flash_num);
        log_res(NOR_FLASH, res,"Num");
    }

    if(res) {
        res = nor_flash_init_one(flash_num);
        log_res(NOR_FLASH, res,"Init1");
    } else {
        LOG_ERROR(NOR_FLASH, "Usage: nfi num");
    }
    return res;
}

bool nor_flash_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t flash_num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &flash_num);
        log_res(NOR_FLASH, res,"Num");
    }

    if(res) {
        res = nor_flash_reset(flash_num);
        log_res(NOR_FLASH, res,"Reset");
    } else {
        LOG_ERROR(NOR_FLASH, "Usage: nft num");
    }
    return res;
}

bool nor_flash_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t byte = 0;
    uint8_t flash_num = 0;
    uint32_t size = 0;
    uint32_t address = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &flash_num);
        log_res(NOR_FLASH, res,"Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &address);
        log_res(NOR_FLASH, res,"Addr");
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &size);
        log_res(NOR_FLASH, res,"Size");
    }

    if(res && size) {
        cli_printf(CRLF "0x" CRLF);
        uint32_t i = 0;
        for(i = 0; i < size; i++) {
            res = nor_flash_read(flash_num, address + i, &byte, 1);
            if(res) {
                cli_printf("%02x", byte);
            } else {
                LOG_ERROR(NOR_FLASH, "ReadErr Addr:0x%x Size:%u", address, 1);
            }
        }
        cli_printf(CRLF);
    } else {
        LOG_ERROR(NOR_FLASH, "Usage: nfr num address size");
    }
    return res;
}

bool nor_flash_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t flash_num = 0;
    uint8_t buff[OFF_CHIP_NOR_FLASH_PAGE_SIZE + 1];
    memset(buff, 0xFF, sizeof(buff));
    uint32_t size = 0;
    uint32_t address = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &flash_num);
        log_res(NOR_FLASH, res,"Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &address);
        log_res(NOR_FLASH, res,"Addr");
    }

    if(3 <= argc) {
        res = try_str2array(argv[2], buff, sizeof(buff), &size);
        if(false == res) {
            LOG_WARNING(NOR_FLASH, "ExtractHexArrayErr  [%s]", argv[1]);
            snprintf((char*)buff, sizeof(buff), "%s", argv[2]);
            size = strlen(argv[1]);
            res = true;
        }
    }

    if(res) {
        LOG_INFO(NOR_FLASH, "TryWrite Addr 0x%x size %u byte", address, size);
        res = nor_flash_write(flash_num, address, buff, size);
        if(res) {
            LOG_INFO(NOR_FLASH, "Ok 0x%x", address);
        } else {
            LOG_ERROR(NOR_FLASH, "Err  0x%x", address);
        }
    } else {
        LOG_ERROR(NOR_FLASH, "Usage: nfw num address size");
    }
    return res;
}

bool nor_flash_analyze_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t flash_num = 0;
    uint32_t piece_size = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &flash_num);
        log_res(NOR_FLASH, res,"Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &piece_size);
        log_res(NOR_FLASH, res,"PiceSize");
    }

    if(res) {
        NorFlashInstance_t* Node = NorFlashGetNode(flash_num);
        if(Node) {
            res = nor_flash_usage(flash_num, piece_size);
            log_res(NOR_FLASH, res,"Usage");
        }
    } else {
        LOG_ERROR(NOR_FLASH, "Usage:nfa num PieceSize");
    }
    return res;
}
