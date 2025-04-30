#include "spi_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "log.h"
#include "spi_mcal.h"
#include "table_utils.h"
#include "writer_config.h"

bool spi_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = spi_diag();

    return res;
}

bool spi_diag_int_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = spi_diag_int();

    return res;
}

bool spi_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(2 == argc) {
        res = true;
        uint8_t num = 0;
        uint8_t tx_array[256] = {0};
        uint32_t array_len = 0;
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SPI, "ParseErr SPINum [0~%u]", SPI_COUNT);
        }

        if(res) {
            res = try_str2array(argv[1], tx_array, sizeof(tx_array), &array_len);
            if(false == res) {
                LOG_ERROR(SPI, "Unable to extract tx array %s", argv[1]);
            }
        }

        if(res) {
            res = spi_api_write(num, tx_array, array_len);
            if(false == res) {
                LOG_ERROR(SPI, "Unable to send SPI");
            } else {
                LOG_INFO(SPI, "OK");
            }
        }
    } else {
        LOG_ERROR(SPI, "Usage: spw instance hex_string"); /*sw 4 0x55aa*/
        LOG_INFO(SPI, "instance");
        LOG_INFO(SPI, "hex_string 0x[0...F]+");
    }
    return res;
}

bool spi_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t byte = 0;

    uint16_t array_len = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SPI, "ParseErr SPINum [0~%u]", SPI_COUNT);
        }
    }

    if(2 <= argc) {
        res = try_str2uint16(argv[1], &array_len);
        if(false == res) {
            LOG_ERROR(SPI, "Unable to extract array %s", argv[1]);
        }
    }

    if(res) {
        uint32_t i = 0;
        for(i = 0; i < array_len; i++) {
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

bool spi_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t snum = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &snum);
        if(false == res) {
            LOG_ERROR(SPI, "ParseErr SPINum [0~%u]", SPI_COUNT);
        }
    }
    if(res) {
        res = spi_init_one(snum);
    }
    return res;
}
