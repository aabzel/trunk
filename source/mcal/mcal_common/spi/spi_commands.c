#include "spi_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "array_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "log.h"
#include "mcal_diag.h"
#include "spi_mcal.h"
#ifdef HAS_TEST_SPI
#include "test_spi.h"
#endif

bool spi_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = spi_diag();
    log_info_res(SPI, res, "Diag");
    return res;
}

bool spi_diag_int_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = spi_diag_int();
    log_info_res(SPI, res, "DiagInt");
    return res;
}

bool spi_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t size = 0;
    uint8_t tx_array[256] = {0};
    uint8_t num = 0;
    if(2 == argc) {
        res = true;
        res = try_str2uint8(argv[0], &num);
        log_info_res(SPI, res, "Num");

        if(res) {
            res = try_str2array(argv[1], tx_array, sizeof(tx_array), &size);
            log_info_res(SPI, res, "Data");
        }
    }
    if(res) {
        res = spi_mcal_write(num, tx_array, size);
        log_info_res(SPI, res, "Write");
    } else {
        LOG_ERROR(SPI, "Usage: spw instance hexString"); /*sw 4 0x55aa*/
        LOG_INFO(SPI, "Num");
        LOG_INFO(SPI, "hexString 0xFEDCAB45");
    }
    return res;
}

bool spi_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t byte = 0;

    uint16_t size = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SPI, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint16(argv[1], &size);
        log_info_res(SPI, res, "Size");
    }

    if(res) {
        uint32_t i = 0;
        for(i = 0; i < size; i++) {
            byte = 0;
            res = spi_read_safe(num, &byte, 1);
            if(res) {
                print_hex(&byte, 1);
            } else {
                LOG_ERROR(SPI, "%u ReadErr", num);
            }
        }
        cli_printf(CRLF);
    } else {
        LOG_ERROR(SPI, "Usage: spr num size");
        LOG_INFO(SPI, "num");
        LOG_INFO(SPI, "size");
    }
    return res;
}

bool spi_read_byte_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 4;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SPI, res, "Num");
    }

    if(res) {
        uint8_t rx_byte = 0;
        rx_byte = spi_read_byte(num);
        LOG_ERROR(SPI, "SPI%u,Rx:0x%02x", num, rx_byte);
    } else {
        LOG_ERROR(SPI, "Usage: spr num size");
    }
    return res;
}

bool spi_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SPI, res, "Num");
    }
    if(res) {
        switch(argc) {
        case 0: {
            res = spi_mcal_init();
            log_info_res(SPI, res, "Int");
        } break;
        case 1: {
            res = spi_init_one(num);
            log_info_res(SPI, res, "IntOne");
        } break;
        default: {

        } break;
        }

    } else {
        LOG_ERROR(SPI, "Usage: spi num");
    }
    return res;
}

bool spi_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SPI, res, "Num");
    }

    if(res) {
        res = spi_raw_reg_diag(num);
        log_info_res(SPI, res, "RegMap");
    } else {
        LOG_ERROR(SPI, "Usage: spirr num");
    }
    return res;
}

bool spi_write_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(2 == argc) {
        res = true;
        uint8_t num = 0;
        uint8_t tx_array[256] = {0};
        uint8_t rx_array[256] = {0};
        uint32_t size = 0;
        res = try_str2uint8(argv[0], &num);
        log_info_res(SPI, res, "Num");

        if(res) {
            res = try_str2array(argv[1], tx_array, sizeof(tx_array), &size);
            log_info_res(SPI, res, "Data");
        }

        if(res) {
            res = spi_mcal_write_read(num, tx_array, rx_array, size);
            log_info_res(SPI, res, "WriteRead");
            if(res) {
                print_hex(rx_array, size);
            }
        }
    } else {
        LOG_ERROR(SPI, "Usage: spw instance hexString"); /*sw 4 0x55aa*/
        LOG_INFO(SPI, "instance");
        LOG_INFO(SPI, "hexString 0x[0...F]+");
    }
    return res;
}

bool spi_loopback_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 == argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SPI, res, "Num");
    }

    if(res) {
        res = false;
#ifdef HAS_TEST_SPI
        res = test_spi_loopback_num(num);
        log_info_res(SPI, res, "LoopBack");
#endif
    } else {
        LOG_ERROR(SPI, "Usage: splb Num"); /**/
    }
    return res;
}

bool spi_move_mode_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t move_mode = MOVE_MODE_INTERRUPT;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SPI, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &move_mode);
        log_info_res(SPI, res, "Mode");
    }

    if(res) {
        switch(argc) {
        case 1: {
            MoveMode_t cur_move_mode = MOVE_MODE_UNDEF;
            res = spi_move_mode_get(num, &cur_move_mode);
            log_info_res(SPI, res, "ModeGet");
            LOG_INFO(SPI, "SPI%u,Get,MoveMode:%s", num, McalMoveModeToStr(cur_move_mode));
        } break;
        case 2: {
            LOG_INFO(SPI, "SPI%u,Set,MoveMode:%s", num, McalMoveModeToStr(move_mode));
            res = spi_move_mode_set(num, (MoveMode_t)move_mode);
            log_info_res(SPI, res, "ModeSet");

        } break;
        default: {
            res = false;
        } break;
        } // switch(argc)
    } else {
        LOG_ERROR(SPI, "Usage: srm Num Mode");
    }
    return res;
}
