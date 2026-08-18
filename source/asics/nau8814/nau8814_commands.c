#include "nau8814_commands.h"

#include "convert.h"
#include "log.h"
#include "nau8814_drv.h"
// ncp 5000000 48000 128
bool nau8814_calc_pll_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t mclk_hz = 12288800;
    uint32_t fs_hz = 48000;
    uint32_t k_step = 64;
    if(0 <= argc) {
        res = true;
    }
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &mclk_hz);
    }
    if(2 <= argc) {
        res = try_str2uint32(argv[1], &fs_hz);
    }
    if(3 <= argc) {
        res = try_str2uint32(argv[2], &k_step);
    }

    if(res) {
        res = nau8814_calc_pll(mclk_hz, fs_hz, k_step);
        log_res(NAU8814, res, "CalcPll");
    } else {
        LOG_ERROR(NAU8814, "Usage: ncp MclkHz FsHz Kstep");
    }
    return res;
}

bool nau8814_diag_low_level_command(int32_t argc, char* argv[]) {
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
        LOG_INFO(NAU8814, "LowLevelDiag KeyWord [%s]", key_word);
        res = nau8814_diag_low_level(1, key_word);
        log_res(NAU8814, res, "LowLevelDiag");
    }
    return res;
}

bool nau8814_diag_hl_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = nau8814_diag_high_level(1);
    log_res(NAU8814, res, "HiLevelDiag");
    return res;
}

bool nau8814_reg_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t addr = 0;
    uint16_t word = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &addr);
    }
    if(2 <= argc) {
        res = try_str2uint16(argv[1], &word);
    }

    if(res) {
        res = nau8814_reg_write(1, addr, word);
        if(res) {
            LOG_INFO(NAU8814, "Addr 0x%02x Val: 0x%02x", word, word);
        }
    }
    return res;
}

bool nau8814_reg_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    uint8_t addr = 0;

    if(1 == argc) {
        res = try_str2uint8(argv[0], &addr);
    }

    if(res) {
        uint16_t word = 0;
        res = nau8814_reg_read(num, addr, &word);
        if(res) {
            LOG_INFO(NAU8814, "Addr:0x%02x,Val:0x%04x", addr, word);
        }
    } else {
        LOG_INFO(NAU8814, "Usage: maar RegAddr");
    }

    return res;
}

bool nau8814_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = nau8814_init_one(1);
    log_res(NAU8814, res, "Init1");
    return res;
}

bool nau8814_reg_hazy_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = nau8814_reg_hazy(1);
        log_res(NAU8814, res, "Hazy");
        res = nau8814_reg_map_hidden_diag(1);
        log_res(NAU8814, res, "Hidden");
    } else {
        LOG_ERROR(NAU8814, "Usage: nrh");
    }
    return res;
}

bool nau8814_reg_map_command(int32_t argc, char* argv[]) {
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
        LOG_ERROR(NAU8814, "Usage: maxregs keyWord keyWord");
    }
    if(res) {
        res = nau8814_reg_map_diag(1, keyWord1, keyWord2);
        log_res(NAU8814, res, "RegMap");
    }
    return res;
}

bool nau8814_reg_map_hidden_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = nau8814_reg_map_hidden_diag(1);
        log_res(NAU8814, res, "HiddenDiag");
    }
    return res;
}

bool nau8814_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = nau8814_reset(1);
    log_res(NAU8814, res, "Reset");
    return res;
}

bool nau8814_i2c_ping_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = nau8814_is_connected(1);
    if(res) {
        LOG_INFO(NAU8814, "Connected!");
    } else {
        LOG_ERROR(NAU8814, "Disconnected!");
    }
    return res;
}
