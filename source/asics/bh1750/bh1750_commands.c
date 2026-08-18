#include "bh1750_commands.h"

#include <stdio.h>
#include <string.h>

#include "array_diag.h"
#include "bh1750_drv.h"
#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "log.h"
#include "std_includes.h"
#include "str_utils.h"

#ifdef HAS_BH1750
#include "bh1750_drv.h"
#endif

#ifdef HAS_I2C
#include "i2c_mcal.h"
#endif

#ifndef HAS_BH1750_DIAG
#error "+HAS_BH1750_DIAG"
#endif

bool bh1750_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(BH1750, res, "Num");
    }

    if(res) {
        res = bh1750_reset(num);
        log_res(BH1750, res, "Rst");
    } else {
        LOG_ERROR(BH1750, "Usage: btt");
    }
    return res;
}

bool bh1750_i2c_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t buff[128];
    memset(buff, 0, sizeof(buff));
    uint32_t size = 1;
    if(0 <= argc) {
        res = true;
        size = 2;
    }
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(BH1750, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &size);
        log_res(BH1750, res, "Size");
    }

    if(res) {
        Bh1750Handle_t* Node = Bh1750GetNode(num);
        if(Node) {

            res = i2c_mcal_read(Node->i2c_num, Node->chip_addr, buff, size);
            log_res(BH1750, res, "Read");
            if(Node) {
                print_hex(buff, size);
            }
        }
    } else {
        LOG_ERROR(BH1750, "Usage: btr");
    }
    return res;
}

bool bh1750_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    char key_word1[3] = "";
    char key_word2[3] = "";
    if(0 <= argc) {
        res = true;
    }

    if(res) {
        LOG_INFO(BH1750, "Version: %u", BH1750_DRIVER_VERSION);
        res = bh1750_diag(key_word1, key_word2);
        log_res(BH1750, res, "Diag");
    } else {
        LOG_ERROR(BH1750, "Usage: bhd");
    }
    return res;
}

bool bh1750_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 <= argc) {
        res = bh1750_mcal_init();
        log_res(BH1750, res, "Init");
    }
    return res;
}

bool bh1750_get_light_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t light = 0;

    if(res) {
        LOG_INFO(BH1750, "GetVol %u Ok!", light);
    } else {
        LOG_ERROR(BH1750, "GetVol %u Err", light);
        LOG_ERROR(BH1750, "Usage: btgv");
    }

    return res;
}

bool bh1750_send_opcode_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(BH1750, res, "Num");
    }

    BhOpCode_t op_code = 0;
    if(2 <= argc) {
        res = try_str2uint8(argv[1], &op_code);
        log_res(BH1750, res, "OpCode");
    }

    if(res) {
        res = bh1750_send_opcode(num, op_code);
        log_res(BH1750, res, "SendOpCode");
    }
    return res;
}

bool bh1750_read_light_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(BH1750, res, "Num");
    }

    if(res) {
        double lighting = 0.0;
        res = bh1750_read_lx(num, &lighting);
        LOG_INFO(BH1750, "%u,illumination:%f lx ", num, lighting);
    }
    return res;
}
