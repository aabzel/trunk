#include "flash_commands.h"

#include <flash.h>
#include <inttypes.h>
#include <stdio.h>
#include <vims.h>

#include "convert.h"
#include "crc16_ccitt.h"
#include "crc32.h"
#include "data_utils.h"
#include "debug_info.h"
#include "diag_page_nums.h"
#include "diag_report.h"
#include "flash_drv.h"
#include "io_utils.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

static bool diag_flash_prot(char* key_word1, char* key_word2) {
    bool res = false;
    uint32_t flash_addr = NOR_FLASH_BASE, num = 0;
    char line_str[120];
    uint32_t prot = 0;
    uint32_t spare = 0;
    bool is_print = false;
    uint32_t busy = 0;
    float usage_pec = 0.0f;
    static const table_col_t cols[] = {{5, "num"},   {11, "Start"}, {11, "End"}, {7, "WrSta"},
                                       {7, "WrSta"}, {7, "cont"},   {8, "Use"}};
    table_header(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    for(flash_addr = 0; flash_addr < NOR_FLASH_SIZE; flash_addr += FLASH_SECTOR_SIZE) {
        strcpy(line_str, TSEP);
        snprintf(line_str, sizeof(line_str), "%s 0x%08x" TSEP, line_str, flash_addr);
        snprintf(line_str, sizeof(line_str), "%s 0x%08x" TSEP, line_str, flash_addr + FLASH_SECTOR_SIZE);
        res = is_addr_protected(flash_addr);
        prot = FlashProtectionGet(flash_addr);
        if(res) {
            snprintf(line_str, sizeof(line_str), "%s %5s " TSEP, line_str, "Prot");
        } else {
            snprintf(line_str, sizeof(line_str), "%s %5s " TSEP, line_str, "WrEn");
            res = true;
        }
        snprintf(line_str, sizeof(line_str), "%s %6u" TSEP, line_str, prot);
        flash_scan((uint8_t*)flash_addr, FLASH_SECTOR_SIZE, &usage_pec, &spare, &busy);
        snprintf(line_str, sizeof(line_str), "%s %6s" TSEP, line_str, (FLASH_SECTOR_SIZE == spare) ? "spare" : "busy");
        snprintf(line_str, sizeof(line_str), "%s %6.2f " TSEP, line_str, usage_pec);
        // snprintf(line_str, sizeof(line_str), "%s", line_str);
        is_print = is_contain(line_str, key_word1, key_word2);
        if(is_print) {
            io_printf(TSEP " %3u ", num);
            io_printf("%s\r\n", line_str);
            wait_in_loop_ms(2);
            num++;
        }
    }
    table_row_bottom(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));

    return res;
}

//! - \ref VIMS_MODE_DISABLED (GPRAM enabled)
//! - \ref VIMS_MODE_ENABLED  (CACHE mode)
//! - \ref VIMS_MODE_OFF

static const char* vims_mode2str(uint32_t mode) {
    const char* name = "undef";
    switch(mode) {
    case VIMS_MODE_OFF:
        name = "OFF";
        break;
    case VIMS_MODE_ENABLED:
        name = "CACHE";
        break;
    case VIMS_MODE_DISABLED:
        name = "GPRAM";
        break;
    default:
        name = "undef";
        break;
    }
    return name;
}

bool flash_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    char keyWord1[20] = "";
    char keyWord2[20] = "";
    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }
    if(1 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }
    if(2 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if(2 < argc) {
        LOG_ERROR(NVS, "Usage: fd key1 key2");
    }

    if(res) {
        uint32_t all_flash_crc = 0;
        // FlashSizeGet
        // FlashPowerModeGet
        // FlashProtectionGet
        all_flash_crc = crc32(((uint8_t*)NOR_FLASH_BASE), NOR_FLASH_SIZE);
        uint32_t mode = VIMSModeGet(VIMS_BASE);
        uint32_t flash_sec_size = FlashSectorSizeGet();
        uint32_t flash_size = FlashSizeGet();
        io_printf("VIMSMode: %s" CRLF, vims_mode2str(mode));
        io_printf("FlashCRC32: 0x%08x" CRLF, all_flash_crc);
        io_printf("FlashSectorSize: %u bytes %u kBytes" CRLF, flash_sec_size, flash_sec_size / K_BYTES);
        io_printf("FlashSize: %u bytes %u kBytes" CRLF, flash_size, flash_size / K_BYTES);
        io_printf("FlashPowerMode: %u" CRLF, FlashPowerModeGet());
        io_printf("FlashFsm: %u" CRLF, FlashCheckFsmForReady());
        io_printf("FlashFsmError: %u" CRLF, FlashCheckFsmForError());

        io_printf("Flash Base: 0x%08x" CRLF, NOR_FLASH_BASE);
        io_printf("Flash size: %u byte %u kByte" CRLF, NOR_FLASH_SIZE, NOR_FLASH_SIZE / K_BYTES);
        io_printf("Flash End: 0x%08x" CRLF, NOR_FLASH_END - 1);

        res = diag_flash_prot(keyWord1, keyWord2);
    }

    return res;
}

bool flash_mcal_erasecommand(int32_t argc, char* argv[]) {
    uint32_t sector_address = 0;
    bool res = false;
    if(1 == argc) {
        res = true;
        res = try_str2uint32(argv[0], &sector_address);
        if(false == res) {
            LOG_ERROR(LG_FLASH, "Unable to parse sector_address %s", argv[0]);
        }
        if(res) {
            res = flash_mcal_erasesector(sector_address);
            if(res) {
                LOG_INFO(LG_FLASH, "FlashSectorErase OK");
            } else {
                LOG_ERROR(LG_FLASH, "FlashSectorErase error");
            }
        }
    } else {
        LOG_ERROR(LG_FLASH, "Usage: fe sector_address");
    }
    return res;
}

bool flash_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t rx_array[256] = {0};
    if(2 == argc) {
        res = true;
        uint32_t offset = 0;
        uint32_t buffer_size = 0;
        if(res) {
            res = try_str2uint32(argv[0], &offset);
            if(false == res) {
                LOG_ERROR(LG_FLASH, "Unable to parse offset %s", argv[0]);
            }
        }
        if(res) {
            res = try_str2uint32(argv[1], &buffer_size);
            if(false == res) {
                LOG_ERROR(LG_FLASH, "Unable to parse buffer_size %s", argv[1]);
            }
        }

        if(true == res) {
            if(buffer_size <= sizeof(rx_array)) {
                res = flash_read(offset, rx_array, buffer_size);
                if(res) {
                    LOG_INFO(LG_FLASH, "OK");
                    uint16_t crc16_calc = calc_crc16_ccitt_false(rx_array, buffer_size);
                    io_printf(" 0x");
                    print_mem(rx_array, buffer_size, true, false, false, false);
                    io_printf(" 0x%04x" CRLF, crc16_calc);
                } else {
                    LOG_ERROR(LG_FLASH, "read error");
                }
            } else {
                LOG_ERROR(LG_FLASH, "Too big chunk");
            }
        }
    } else {
        LOG_ERROR(LG_FLASH, "Usage: fr offset buffer_size");
    }
    return res;
}

bool flash_mcal_writeite_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint16_t crc16_read = 0;
    uint32_t flash_address = 0;
    uint32_t count = 0;
    uint8_t WrDataBuffer[256] = {0};
    memset(WrDataBuffer, 0x00, sizeof(WrDataBuffer));
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
        res = try_str2array(argv[1], WrDataBuffer, sizeof(WrDataBuffer), &count);
        if(false == res) {
            LOG_ERROR(LG_FLASH, "Unable to extract HexString %s", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2uint16(argv[2], &crc16_read);
        if(false == res) {
            LOG_ERROR(LG_FLASH, "Unable to parse crc16_read %s", argv[2]);
        } else {
            res = crc16_check(WrDataBuffer, count, crc16_read);
            if(false == res) {
                LOG_ERROR(LG_FLASH, "crc16 error");
            }
        }
    }

    if(3 < argc) {
        res = false;
    }

    if(res) {
        res = flash_mcal_write(flash_address, WrDataBuffer, count);
        if(res) {
            LOG_INFO(LG_FLASH, "Ok!");
        } else {
            LOG_ERROR(LG_FLASH, "FlashProgram error");
        }
    } else {
        LOG_ERROR(LG_FLASH, "Usage: fw sector_address hex_string crc16_read");
        LOG_INFO(LG_FLASH, "sector_address");
        LOG_INFO(LG_FLASH, "hex_string 0x[0...F]+");
        LOG_INFO(LG_FLASH, "crc16_read");
    }
    return res;
}

bool flash_scan_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        float usage_pec = 0.0f;
        uint32_t spare = 0;
        uint32_t busy = 0;
        res = mem_scan((uint8_t*)NOR_FLASH_BASE, NOR_FLASH_SIZE, &usage_pec, &spare, &busy);
        if(res) {
            io_printf("usage: %f %%" CRLF, usage_pec);
            io_printf("spare: %u Bytes %u kBytes" CRLF, spare, spare / 1024);
            io_printf("busy : %u Bytes %u kBytes" CRLF, busy, busy / 1024);
        }
    } else {
        LOG_ERROR(NVS, "Usage: fs");
    }
    return res;
}
