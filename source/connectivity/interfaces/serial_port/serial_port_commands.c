#include "serial_port_commands.h"

#include <stddef.h>
#include <stdio.h>

#include "convert.h"
#include "log.h"
#include "serial_port.h"
#include "serial_port_diag.h"

bool serial_port_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SERIAL_PORT, "ParseErr Num [1....8]");
        }
    }

    if(res) {

        res = serial_port_diag(num);
        log_info_res(SERIAL_PORT, res, "Diag");
    } else {
        LOG_ERROR(SERIAL_PORT, "Usage: spd Num");
    }

    return res;
}

bool serial_port_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SERIAL_PORT, "ParseErr Num [1....8]");
        }
    }

    if(res) {
        res = serial_port_init_one(num);
        log_info_res(SERIAL_PORT, res, "Init");
    } else {
        LOG_ERROR(SERIAL_PORT, "Usage: spi Num");
    }

    return res;
}

bool serial_port_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t array[256];
    size_t array_len = 0;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SERIAL_PORT, "ParseErr Num");
        }
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], array, sizeof(array), &array_len);
        if(false == res) {
            LOG_WARNING(SERIAL_PORT, "ExtractHexArrayErr  [%s]", argv[1]);
            snprintf((char*)array, sizeof(array), "%s", argv[1]);
            array_len = strlen(argv[1]);
            res = true;
        }
    }

    if(res) {
        res = serial_port_send(num, array, array_len);
        log_info_res(SERIAL_PORT, res, "Send");
    } else {
        LOG_ERROR(SERIAL_PORT, "Usage: sps Num HexStr");
    }
    return res;
}
