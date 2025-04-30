#include "eeprom_commands.h"

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
#include "eeprom_config.h"
#include "eeprom_diag.h"
#include "eeprom_mcal.h"
#ifdef HAS_EEPROM_CUSTOM
#include "eeprom_custom_diag.h"
#endif
#include "log.h"
#include "microcontroller_const.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

bool eeprom_diag_cmd(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t piece_size = 1024;
    LOG_INFO(EEPROM, "Usage: ed pieceSizeBytes");
    if(0 <= argc) {
        piece_size = 16 * 1024;
        res = true;
    }
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &piece_size);
    }

    if(res) {
        res = eeprom_diag_usage(piece_size);
        log_res(EEPROM, res, "DiagUsage");
    } else {
        LOG_ERROR(EEPROM, "Usage: ed piece_size");
    }

    return res;
}

bool eeprom_erase_cmd(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t size = 0;
    uint32_t address = 0;
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &address);
        if(false == res) {
            LOG_ERROR(EEPROM, "ParseErr Address %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &size);
        if(false == res) {
            LOG_ERROR(EEPROM, "ParseErr Size %s", argv[1]);
        }
    }

    if(res) {
        res = false;
#ifdef HAS_EEPROM_WRITE
        res = eeprom_mcal_erase(address, size);
#endif
        log_res(EEPROM, res, "Erase");
    } else {
        LOG_ERROR(EEPROM, "Usage: ee address size");
    }

    return res;
}

bool eeprom_read_cmd(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t eeprom_addr = 0;
    uint32_t num_bytes = 0;
    if(2 == argc) {
        res = true;
        if(res) {
            res = try_str2uint32(argv[0], &eeprom_addr);
            if(false == res) {
                LOG_ERROR(EEPROM, "Unable to parse in_eeprom_addr %s", argv[0]);
            }
        }
        if(res) {
            res = try_str2uint32(argv[1], &num_bytes);
            if(false == res) {
                LOG_ERROR(EEPROM, "Unable to parse num_bytes %s", argv[1]);
            }
        }
    }
    if(res) {
        LOG_INFO(EEPROM, "Read Addr 0x%08x Size %u", eeprom_addr, num_bytes);
        cli_printf(CRLF);
        uint8_t read_val = 0;
        uint32_t i = 0;
        for(i = 0; i < num_bytes; i++) {
            read_val = 0;
            res = eeprom_mcal_read(eeprom_addr + i, &read_val, 1);
            // log_res(EEPROM, res, "Read");
            if(res) {
                cli_printf("%02X", read_val);
            }
        }
        cli_printf(CRLF);

    } else {
        LOG_ERROR(EEPROM, "Usage: er in_eeprom_addr num_bytes");
    }
    return res;
}

bool eeprom_write_cmd(int32_t argc, char* argv[]) {
    bool res = false;
    uint16_t crc16_read = 0;
    uint32_t eeprom_address = 0;
    uint32_t count = 0;
    uint8_t DataBuffer[256] = {0};
    memset(DataBuffer, 0xFF, sizeof(DataBuffer));
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &eeprom_address);
        if(false == res) {
            LOG_ERROR(EEPROM, "Unable to parse sector_address %s", argv[0]);
        } else {
            res = eeprom_is_address(eeprom_address);
            if(false == res) {
                LOG_ERROR(EEPROM, "not eeprom addr 0x%08x", eeprom_address);
            }
        }
    }
    if(2 <= argc) {
        res = try_str2array(argv[1], DataBuffer, sizeof(DataBuffer), &count);
        if(false == res) {
            LOG_ERROR(EEPROM, "Unable to extract hex_string %s", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2uint16(argv[2], &crc16_read);
        if(false == res) {
            LOG_ERROR(EEPROM, "Unable to parse crc16_read %s", argv[2]);
        } else {
            uint16_t crc16_calc = 0;
#ifdef HAS_CRC16
            res = crc16_check(DataBuffer, count, crc16_read, &crc16_calc);
#endif
            if(false == res) {
                LOG_ERROR(EEPROM, "Crc16 error Read 0x%04x calc 0x%04x", crc16_read, crc16_calc);
            }
        }
    }

    if(3 < argc) {
        res = false;
    }

    if(res) {
        res = false;
#ifdef HAS_EEPROM_WRITE
        res = eeprom_mcal_write(eeprom_address, DataBuffer, count);
#endif
        log_res(EEPROM, res, "Write");
    }

    if(false == res) {
        LOG_ERROR(EEPROM, "Usage: ew address hex_string crc16_read");
        LOG_INFO(EEPROM, "sector_address");
        LOG_INFO(EEPROM, "hex_string 0x[0...F]+");
        LOG_INFO(EEPROM, "crc16_read");
    }
    return res;
}

bool eeprom_scan_cmd(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = eeprom_scan_diag(ROM_START, ROM_SIZE);
        log_res(EEPROM, res, "Scan");
    } else {
        LOG_ERROR(EEPROM, "Usage: es");
    }
    return res;
}

bool eeprom_init_cmd(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = eeprom_mcal_init();
        log_res(EEPROM, res, "Init");
    } else {
        LOG_ERROR(EEPROM, "Usage: ei");
    }
    return res;
}

/*
 err 0 16
 */
bool eeprom_read_relatively_command(int32_t argc, char* argv[]) {
    bool res = false;

    uint32_t offset = 0;
    uint32_t size = 0;

    if(0 <= argc) {
        res = true;
        offset = 0;
        size = ROM_SIZE;
    }

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &offset);
        log_res(EEPROM, res, "ReadOffset");
        size = ROM_SIZE - offset;
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &size);
        log_res(EEPROM, res, "ReadSize");
    }

    if(res) {
        res = eeprom_read_relative(offset, size);
        log_res(EEPROM, res, "Read");
    } else {
        LOG_ERROR(EEPROM, "Usage: err offset size");
    }
    return res;
}

bool eeprom_write_relatively_command(int32_t argc, char* argv[]) {
    bool res = false;

    uint32_t offset = 0;
    uint32_t read_crc32 = 0;
    uint32_t size = 0;
    uint8_t wrData[EEPROM_CHUNK_SIZE] = {0};

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &offset);
        log_res(EEPROM, res, "ReadOffset");
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], wrData, sizeof(wrData), &size);
        log_res(EEPROM, res, "ReadData");
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &read_crc32);
        log_res(EEPROM, res, "ReadCrc32");
    }

    if(res) {
        if(3 == argc) {
            res = eeprom_write_relative(offset, wrData, size, read_crc32);
            log_res(EEPROM, res, "Write");
        }
    } else {
        LOG_ERROR(EEPROM, "Usage: ewr offset data crc32");
    }
    return res;
}
