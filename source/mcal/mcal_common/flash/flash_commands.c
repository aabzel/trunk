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
#ifdef HAS_FLASH_CUSTOM
#include "flash_custom_diag.h"
#endif
#include "log.h"
#include "microcontroller_const.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

bool flash_diag_cmd(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t piece_size = 1024;
    LOG_INFO(LG_FLASH, "Usage: fd pieceSizeBytes");
    if(0 <= argc) {
        piece_size = 16 * 1024;
        res = true;
    }
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &piece_size);
    }

    if(res) {
        res = flash_diag_usage(piece_size);
        log_res(LG_FLASH, res, "DiagUsage");
    } else {
        LOG_ERROR(LG_FLASH, "Usage: fd piece_size");
    }

    return res;
}

bool flash_mcal_erasecmd(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t size = 0;
    uint32_t address = 0;
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &address);
        if(false == res) {
            LOG_ERROR(LG_FLASH, "ParseErr Address %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &size);
        if(false == res) {
            LOG_ERROR(LG_FLASH, "ParseErr Size %s", argv[1]);
        }
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
        res = true;
        if(res) {
            res = try_str2uint32(argv[0], &flash_addr);
            if(false == res) {
                LOG_ERROR(LG_FLASH, "Unable to parse in_flash_addr %s", argv[0]);
            }
        }
        if(res) {
            res = try_str2uint32(argv[1], &num_bytes);
            if(false == res) {
                LOG_ERROR(LG_FLASH, "Unable to parse num_bytes %s", argv[1]);
            }
        }
    }
    if(res) {
        LOG_INFO(LG_FLASH, "Read Addr 0x%08x Size %u", flash_addr, num_bytes);
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

bool flash_mcal_writeite_cmd(int32_t argc, char* argv[]) {
    bool res = false;
    uint16_t crc16_read = 0;
    uint32_t flash_address = 0;
    uint32_t count = 0;
    uint8_t DataBuffer[256] = {0};
    memset(DataBuffer, 0xFF, sizeof(DataBuffer));
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &flash_address);
        if(false == res) {
            LOG_ERROR(LG_FLASH, "Unable to parse sector_address %s", argv[0]);
        } else {
            res = is_flash_addr(flash_address);
            if(false == res) {
                LOG_ERROR(LG_FLASH, "not flash addr 0x%08x", flash_address);
            }
        }
    }
    if(2 <= argc) {
        res = try_str2array(argv[1], DataBuffer, sizeof(DataBuffer), &count);
        if(false == res) {
            LOG_ERROR(LG_FLASH, "Unable to extract hex_string %s", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2uint16(argv[2], &crc16_read);
        if(false == res) {
            LOG_ERROR(LG_FLASH, "Unable to parse crc16_read %s", argv[2]);
        } else {
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
        res = false;
#ifdef HAS_FLASH_WRITE
        res = flash_mcal_write(flash_address, DataBuffer, count);
#endif
        log_res(LG_FLASH, res, "Write");
    }

    if(false == res) {
        LOG_ERROR(LG_FLASH, "Usage: fw sector_address hex_string crc16_read");
        LOG_INFO(LG_FLASH, "sector_address");
        LOG_INFO(LG_FLASH, "hex_string 0x[0...F]+");
        LOG_INFO(LG_FLASH, "crc16_read");
    }
    return res;
}

bool flash_lock_cmd(int32_t argc, char* argv[]) {
    bool res = false;
    bool on_off = true;
    if(1 <= argc) {
        res = try_str2bool(argv[0], &on_off);
    }

    if(res) {
        res = flash_lock_ctrl(on_off);
        log_res(LG_FLASH, res, "Lock");
    }
    return res;
}

bool flash_scan_cmd(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    } else {
        LOG_ERROR(LG_FLASH, "Usage: fs");
    }

    if(res) {
        res = flash_scan_diag(ROM_START, ROM_SIZE);
    }
    return res;
}

bool flash_init_cmd(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = flash_init();
        log_res(LG_FLASH, res, "Init");
    } else {
        LOG_ERROR(LG_FLASH, "Usage: fi");
    }
    return res;
}
