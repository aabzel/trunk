#include "lis3dh_commands.h"

#include "common_diag.h"
#include "convert.h"
#include "lis3dh_drv.h"
#include "log.h"

bool lis3dh_diag_low_level_command(int32_t argc, char* argv[]) {
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
        LOG_INFO(LIS3DH, "LowLevelDiag KeyWord [%s]", key_word);
        res = lis3dh_diag_low_level(1, key_word);
        if(res) {
            LOG_INFO(LIS3DH, "LowLevelDiagOk");
        } else {
            LOG_ERROR(LIS3DH, "LowLevelDiagOk");
        }
    }
    return res;
}

bool lis3dh_diag_hl_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = lis3dh_diag();
    return res;
}

bool lis3dh_reg_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t addr = 0;
    uint8_t byte = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &addr);
    }
    if(2 <= argc) {
        res = try_str2uint8(argv[1], &byte);
    }

    if(res) {
        res = lis3dh_reg_write(1, addr, byte);
        if(res) {
            LOG_INFO(LIS3DH, "Addr:0x%02x,Val:0x%02x", byte, byte);
        }
    }
    return res;
}

bool lis3dh_reg_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    uint8_t addr = 0;

    if(1 == argc) {
        res = try_str2uint8(argv[0], &addr);
    }

    if(res) {
        uint8_t byte = 0;
        res = lis3dh_reg_read(num, addr, &byte);
        if(res) {
            LOG_INFO(LIS3DH, "Addr:0x%02x,Val:0x%02x", addr, byte);
        }
    } else {
        LOG_INFO(LIS3DH, "Usage: maar RegAddr");
    }

    return res;
}

bool lis3dh_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = lis3dh_init_one(1);
    return res;
}

bool lis3dh_reg_map_command(int32_t argc, char* argv[]) {
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
        LOG_ERROR(LIS3DH, "Usage: maxregs keyWord keyWord");
    }
    if(res) {
        res = lis3dh_reg_map_diag(1, keyWord1, keyWord2);
    }
    return res;
}

bool lis3dh_reg_map_hidden_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = lis3dh_reg_map_hidden_diag(1);
    }
    return res;
}

bool lis3dh_i2c_ping_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = lis3dh_is_connected(1);
    if(res) {
        LOG_INFO(LIS3DH, "Connected!");
    } else {
        LOG_ERROR(LIS3DH, "Disconnected!");
    }
    return res;
}

bool lis3dh_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        res = lis3dh_reset(num);
        if(res) {
            LOG_INFO(LIS3DH, "ResetOk,Num:%u", num);
        } else {
            LOG_ERROR(LIS3DH, "ResetErr,Num:%u", num);
        }
    } else {
        LOG_ERROR(LIS3DH, "Usage: sar Num");
    }

    return res;
}

/*
  lia 1
 */
bool lis3dh_accel_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    Lis3dhHandle_t* Node = Lis3dhGetNode(num);
    if(Node) {
        res = lis3dh_acceleration_fast_get_ll(Node, &Node->Acceleration);
        if(res) {
            res = lis3dh_adc_to_real_ll(Node);
            LOG_INFO(LIS3DH, "%s", Lis3dhAccelerationToStr(&Node->Acceleration));
        }
    } else {
        LOG_ERROR(LIS3DH, "Usage: lia Num");
    }

    return res;
}

/*
 * lil 1 1 0
 * lil 1 0 0
 */
bool lis3dh_log_command(int32_t argc, char* argv[]) {
    bool res = false;
    bool on_off = false;
    bool inplase_on_off = false;
    uint8_t num = 1;

    if(2 <= argc) {
        res = try_str2uint8(argv[0], &num);
        res = try_str2bool(argv[1], &on_off);
    }

    if(3 <= argc) {
        res = try_str2bool(argv[2], &inplase_on_off);
    }

    if(res) {
        res = false;
        Lis3dhHandle_t* Node = Lis3dhGetNode(num);
        if(Node) {
            Node->log_on = on_off;
            Node->log_inplace_on = inplase_on_off;
            LOG_INFO(LIS3DH, "Num:%u,Log:%s", num, OnOffToStr(on_off));
            LOG_INFO(LIS3DH, "Num:%u,Inpl:%s", num, OnOffToStr(inplase_on_off));
            res = true;
        }
    } else {
        LOG_ERROR(LIS3DH, "Usage: lil Num OnOff Inplace");
    }

    return res;
}
