#include "max9860_commands.h"

#include "audio_types.h"
#include "convert.h"
#include "log.h"
#include "max9860_diag.h"
#include "max9860_drv.h"
#include "max9860_types.h"

bool max9860_diag_low_level_command(int32_t argc, char* argv[]) {
    bool res = false;
    char key_word[20] = "";
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        strcpy(key_word, argv[0]);
        res = true;
    }

    if(res) {
        LOG_INFO(MAX9860, "LowLevelDiag KeyWord [%s]", key_word);
        res = max9860_diag_low_level(key_word);
        if(res) {
            LOG_INFO(MAX9860, "LowLevelDiagOk");
        } else {
            LOG_ERROR(MAX9860, "LowLevelDiagOk");
        }
    }
    return res;
}

bool max9860_diag_hl_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = max9860_diag_high_level();
    return res;
}

bool max9860_reg_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t reg_addr = 0;
    uint8_t reg_val = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &reg_addr);
    }
    if(2 <= argc) {
        res = try_str2uint8(argv[1], &reg_val);
    }

    if(res) {
        res = max9860_reg_set(reg_addr, reg_val);
        if(res) {
            LOG_INFO(MAX9860, "Addr 0x%02x Val: 0x%02x", reg_addr, reg_val);
        }
    }
    return res;
}

bool max9860_reg_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t reg_addr = 0;
    if(1 == argc) {
        res = try_str2uint8(argv[0], &reg_addr);
    }

    if(res) {
        uint8_t reg_val = 0;
        res = max9860_reg_get(reg_addr, &reg_val);
        if(res) {
            LOG_INFO(MAX9860, "Addr 0x%02x Val: 0x%02x", reg_addr, reg_val);
        }
    } else {
        LOG_INFO(MAX9860, "Usage: maar RegAddr");
    }

    return res;
}

bool max9860_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = max9860_init();
    return res;
}

bool max9860_reg_map_command(int32_t argc, char* argv[]) {
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
        LOG_ERROR(MAX9860, "Usage: maxregs keyWord keyWord");
    }
    if(res) {
        res = max9860_reg_map_diag(keyWord1, keyWord2);
    }
    return res;
}

bool max9860_reg_map_hidden_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = max9860_reg_map_hidden_diag();
    }
    return res;
}

bool max9860_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = max9860_reset();
    return res;
}

bool max9860_i2c_ping_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = max9860_is_connected();
    if(res) {
        LOG_INFO(MAX9860, "Connected!");
    } else {
        LOG_ERROR(MAX9860, "Disconnected!");
    }
    return res;
}
