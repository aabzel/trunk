#include "flash_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "convert.h"

#ifdef HAS_CRC16
#include "crc16_ccitt.h"
#endif /*HAS_CRC16*/

#ifdef HAS_CRC32
#include "crc32.h"
#endif /*HAS_CRC32*/
#include "data_utils.h"
#include "debug_info.h"
#include "flash_config.h"
#include "flash_diag.h"
#include "flash_mcal.h"
#include "log.h"
#include "microcontroller_const.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"
#ifdef HAS_FLASH_CUSTOM
#include "flash_custom_diag.h"
#endif

bool flash_diag_cmd(int32_t argc, char* argv[]) {
    bool res = false;

    uint32_t flash_start = ROM_START;
    uint32_t flash_size = ROM_SIZE;
    uint32_t piece_size = 1024;

    LOG_INFO(LG_FLASH, "Usage: fd pieceSizeBytes");
    if(0 <= argc) {
        piece_size = 128 * 1024;
        flash_start = ROM_START;
        flash_size = ROM_SIZE;
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &flash_start);
        log_info_res(LG_FLASH, res, "FlashStart");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &flash_size);
        log_info_res(LG_FLASH, res, "FlashSize");
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &piece_size);
        log_info_res(LG_FLASH, res, "PieceSize");
    }

    if(res) {
        res = flash_diag_usage(flash_start, flash_size, piece_size);
        log_info_res(LG_FLASH, res, "DiagUsage");
    } else {
        LOG_ERROR(LG_FLASH, "Usage: fd start size piece_size");
    }

    return res;
}

bool flash_erase_cmd(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t size = 0;
    uint32_t address = 0;
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &address);
        log_info_res(LG_FLASH, res, "Addr");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &size);
        log_info_res(LG_FLASH, res, "Size");
    }

    if(res) {
        res = false;
#ifdef HAS_FLASH_WRITE
        res = flash_mcal_erase(address, size);
#endif
        log_res(LG_FLASH, res, "Erase");
    } else {
        LOG_ERROR(LG_FLASH, "Usage: fe address size");
    }

    return res;
}

bool flash_read_cmd(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t flash_addr = 0;
    uint32_t num_bytes = 0;
    if(2 == argc) {
        res = try_str2uint32(argv[0], &flash_addr);
        log_info_res(LG_FLASH, res, "Addr");
        res = try_str2uint32(argv[1], &num_bytes);
        log_info_res(LG_FLASH, res, "Size");
    }
    if(res) {
        LOG_INFO(LG_FLASH, "ReadAddr:0x%08x,Size %u", flash_addr, num_bytes);
        cli_printf(CRLF);
        uint8_t read_val = 0;
        uint32_t i = 0;
        for(i = 0; i < num_bytes; i++) {
            read_val = 0;
            res = flash_mcal_read(flash_addr + i, &read_val, 1);
            log_res(LG_FLASH, res, "Read");
            if(res) {
                cli_printf("%02X", read_val);
            }
        }
        cli_printf(CRLF);

    } else {
        LOG_ERROR(LG_FLASH, "Usage: fr in_flash_addr num_bytes");
    }
    return res;
}

bool flash_write_cmd(int32_t argc, char* argv[]) {
    bool res = false;
    uint16_t crc16_read = 0;
    uint32_t address = 0;
    uint32_t count = 0;
    uint8_t DataBuffer[256] = {0};
    memset(DataBuffer, 0xFF, sizeof(DataBuffer));
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &address);
        log_info_res(LG_FLASH, res, "Addr");
    }
    if(2 <= argc) {
        res = try_str2array(argv[1], DataBuffer, sizeof(DataBuffer), &count);
        log_info_res(LG_FLASH, res, "Data");
        LOG_INFO(LG_FLASH, "ReadSize:%u", count);
    }

    if(3 <= argc) {
        res = try_str2uint16(argv[2], &crc16_read);
        log_info_res(LG_FLASH, res, "ReadCrc16");
        if(res) {
            uint16_t crc16_calc = 0;
#ifdef HAS_CRC16
            res = crc16_check(DataBuffer, count, crc16_read, &crc16_calc);
#endif
            if(false == res) {
                LOG_ERROR(LG_FLASH, "Crc16 error Read 0x%04x calc 0x%04x", crc16_read, crc16_calc);
            }
        }
    }

    if(3 < argc) {
        res = false;
    }

    if(res) {
        res = is_flash_addr(address);
        if(false == res) {
            LOG_ERROR(LG_FLASH, "not flash addr 0x%08x", address);
        }
        res = false;
#ifdef HAS_FLASH_WRITE
        res = flash_mcal_write(address, DataBuffer, count);
#endif
        log_info_res(LG_FLASH, res, "Write");
    } else {
        LOG_ERROR(LG_FLASH, "Usage: fw address hexString crc16Read");
        LOG_INFO(LG_FLASH, "address");
        LOG_INFO(LG_FLASH, "hexString 0x[0...F]+");
        LOG_INFO(LG_FLASH, "crc16Read");
    }
    return res;
}

bool flash_lock_cmd(int32_t argc, char* argv[]) {
    bool res = false;
    bool on_off = true;
    if(1 <= argc) {
        res = try_str2bool(argv[0], &on_off);
        log_info_res(LG_FLASH, res, "Ctrl");
    }

    if(res) {
        res = flash_lock_ctrl(on_off);
        log_res(LG_FLASH, res, "Lock");
    }
    return res;
}

bool flash_scan_cmd(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t address = ROM_START;
    uint32_t size = ROM_SIZE;
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &address);
        log_res(LG_FLASH, res, "Addr");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &size);
        log_res(LG_FLASH, res, "Size");
    }

    if(res) {
        res = flash_scan_diag(address, size);
        log_res(LG_FLASH, res, "Scan");
    } else {
        LOG_ERROR(LG_FLASH, "Usage: fs address size");
    }
    return res;
}

bool flash_init_cmd(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = flash_mcal_init();
        log_res(LG_FLASH, res, "Init");
    } else {
        LOG_ERROR(LG_FLASH, "Usage: fi");
    }
    return res;
}

bool flash_get_spare_aligne_cmd(int32_t argc, char* argv[]) {
    bool res = false;

    uint32_t aligne = 128;
    uint32_t size = 128;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &aligne);
        log_res(LG_FLASH, res, "Align");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &size);
        log_res(LG_FLASH, res, "Rize");
    }

    const FlashConfig_t* Config = FlashGetConfig(1);
    if(Config) {
        uint32_t spare_addr = flash_get_first_spare_size_aligned(Config->start, Config->size, aligne, size);
        LOG_INFO(LG_FLASH, "StartAddr:0x%08X", spare_addr);
    }
    return res;
}
