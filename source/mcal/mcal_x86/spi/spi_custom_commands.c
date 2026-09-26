#include "spi_custom_commands.h"

#include "convert.h"
#include "log.h"
#include "spi_custom_diag.h"

bool spi_diag_low_level_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 2;
    char keyword[80] = {0};
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SPI, "ParseErr I2S Number [1-%d]", I2S_COUNT);
        }
    }

    if(2 <= argc) {
        strcpy(keyword, argv[1]);
    }

    if(res) {
        res = spi_diag_low_level(num, keyword);
    } else {
        LOG_ERROR(SPI, "Usage i2sdl Num");
    }

    return res;
}

bool spi_raw_reg_command(int32_t argc, char* argv[]) {
    uint8_t num = 2;
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SPI, "ParseErr I2S Number [1-%d]", I2S_COUNT);
        }
    }

    if(res) {
        res = spi_raw_reg_diag(num);
    } else {
        LOG_ERROR(SPI, "Usage i2srr Num");
    }

    return res;
}
