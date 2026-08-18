#include "ltr390_commands.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "array_diag.h"
#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "ltr390_config.h"
#include "ltr390_dep.h"
#include "ltr390_diag.h"
#include "ltr390_drv.h"
#include "ltr390_types.h"
#ifdef HAS_LTR390
#include "ltr390_drv.h"
#endif

#ifndef HAS_LTR390_DIAG
#error "+HAS_LTR390_DIAG"
#endif

#ifdef HAS_I2C
#include "i2c_mcal.h"
#endif

#ifdef HAS_I2C_DIAG
#include "i2c_diag.h"
#endif

#include "log.h"
#include "str_utils.h"

bool ltr390_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(0 == argc) {
        res = true;
    }

    if(1 == argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(LTR390, "Parse Num [%s] Err", argv[0]);
        }
    }

    if(res) {
        res = ltr390_reset(num);
    } else {
        LOG_ERROR(LTR390, "Usage: ltt");
    }
    return res;
}

bool ltr390_i2c_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t buff[128];
    memset(buff, 0, sizeof(buff));
    uint32_t size = 1;
    uint8_t num = 1;
    if(0 == argc) {
        res = true;
        size = 2;
    }
    if(1 == argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(LTR390, "Parse Num [%s] Err", argv[0]);
        }
    }

    if(2 == argc) {
        res = try_str2uint32(argv[1], &size);
        if(false == res) {
            LOG_ERROR(LTR390, "Parse size [%s] Err", argv[1]);
        }
    }

    if(res) {
        Ltr390Handle_t* Node = Ltr390GetNode(num);
        if(Node) {
            res = i2c_mcal_read(Node->i2c_num, LTR390_I2C_ADDR, buff, size);
            if(Node) {
                print_hex(buff, size);
            }
        }
    } else {
        LOG_ERROR(LTR390, "Usage: ltr");
    }
    return res;
}

bool ltr390_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    char key_word1[3] = "";
    char key_word2[3] = "";
    uint8_t num = 1;
    if(0 == argc) {
        num = 1;
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(LTR390, "Parse Num [%s] Err", argv[0]);
        }
    }

    if(res) {
        Ltr390Handle_t* Node = Ltr390GetNode(num);
        if(Node) {
            Ltr390DiagNode(Node);
        }
        LOG_INFO(LTR390, "Version: %u", LTR390_DRIVER_VERSION);
        res = ltr390_diag(key_word1, key_word2);
    } else {
        LOG_ERROR(LTR390, "Usage: ltd");
    }
    return res;
}

bool ltr390_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    char key_word1[3] = "";
    char key_word2[3] = "";
    if(0 == argc) {
        res = true;
    }

    if(res) {
        LOG_INFO(LTR390, "Num: %u", num);
        res = ltr390_diag_registers(num, key_word1, key_word2);
    } else {
        LOG_ERROR(LTR390, "Usage: lrm");
    }
    return res;
}

bool ltr390_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = ltr390_mcal_init();
        if(false == res) {
            LOG_ERROR(LTR390, "Init" LOG_ER);
        } else {
            LOG_INFO(LTR390, "Init" LOG_OK);
        }
    }
    return res;
}

// lts 1 1
bool ltr390_start_measure_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    DataSource_t source = LTR390_SRC_UNDEF;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(LTR390, "Parse Num [%s] Err", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &source);
        if(false == res) {
            LOG_ERROR(LTR390, "Parse Scr [%s] Err", argv[1]);
        }
    }

    if(res) {
        LOG_INFO(LTR390, "Num:%u,Src:%u", num, source);
        res = ltr390_start_measurement(num, source);
    } else {
        LOG_ERROR(LTR390, "Usage: lts Num Sr");
    }
    return res;
}

bool ltr390_undoc_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;

    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(LTR390, "Parse Num [%s] Err", argv[0]);
        }
    }

    if(res) {
        res = ltr390_diag_registers_undoc(num);
    }
    return res;
}
