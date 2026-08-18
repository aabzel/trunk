#include "bc127_commands.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "bc127_config.h"
#include "bc127_diag.h"
#include "bc127_drv.h"
#include "bc127_types.h"
#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

bool bc127_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = bc127_reset();
    } else {
        LOG_ERROR(BC127, "Usage: bct");
    }
    return res;
}

bool bc127_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        cli_printf("DigitalFormat:%u %s" CRLF, Bc127Item.digital_format, DigitalFormatToStr(Bc127Item.digital_format));
        cli_printf("DigitalRate: %u Hz" CRLF, Bc127Item.digital_rate);
        cli_printf("ScalingFactor: %u" CRLF, Bc127Item.param_1);
        if(DFOR_I2S == Bc127Item.digital_format) {
            parse_i2s_param2(Bc127Item.Param2.reg_val);
        }
    } else {
        LOG_ERROR(BC127, "Usage: bcd");
    }
    return res;
}

bool bc127_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = bc127_init();
        if(false == res) {
            LOG_ERROR(BC127, "Init" LOG_ERR);
        } else {
            LOG_INFO(BC127, "Init" LOG_OK);
        }
    }
    return res;
}

bool bc127_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t array[256] = "";
    memset(array, 0, sizeof(array));
    strcpy((char*)array, "");
    uint32_t array_len = 0;
    uint32_t i = 0;
    LOG_WARNING(BC127, "argc:%u", argc);
    for(i = 0; i < argc; i++) {
        if(0 == i) {
            snprintf((char*)array, sizeof(array), "%s", argv[i]);
            array_len += strlen(argv[i]);
        } else {
            snprintf((char*)array, sizeof(array), "%s %s", array, argv[i]);
            array_len += 1 + strlen(argv[i]);
        }
        res = true;
    }

    if(res) {
        array_len++;
        res = bc127_send(array, array_len);
        if(false == res) {
            LOG_ERROR(BC127, "Send" LOG_ERR);
        } else {
            LOG_INFO(BC127, "Send:%u byte" LOG_OK, array_len);
        }
    } else {
        LOG_ERROR(BC127, "Usage: bcs cmd_arg1_arg2");
    }
    return res;
}

bool bc127_get_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t array[256] = "";
    memset(array, 0, sizeof(array));
    strcpy((char*)array, "");
    uint32_t array_len = 0;

    if(1 == argc) {
        snprintf((char*)array, sizeof(array), "%s", argv[0]);
        array_len = strlen(argv[0]);
        res = true;
    }

    if(res) {
        array_len++;
        res = bc127_send_get(array, array_len);
        if(false == res) {
            LOG_ERROR(BC127, "Send" LOG_ERR);
        } else {
            LOG_INFO(BC127, "Send:%u byte" LOG_OK, array_len);
        }
    } else {
        LOG_ERROR(BC127, "Usage: bcg param");
    }
    return res;
}

bool bc127_get_volume_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t volume = 0;
    uint8_t link_id = 0;
    if(0 == argc) {
        res = bc127_get_volume(&volume);
    }
    if(1 == argc) {
        res = try_str2uint8(argv[0], &link_id);
        res = bc127_get_volume_id(link_id, &volume);
    }

    if(res) {
        LOG_INFO(BC127, "GetVol %u Ok!", volume);
    } else {
        LOG_ERROR(BC127, "GetVol %u Err", volume);
        LOG_ERROR(BC127, "Usage: bgv");
    }

    return res;
}

bool bc127_set_volume_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t link_id = 0;
    uint8_t volume = 0;
    if(1 == argc) {
        res = try_str2uint8(argv[0], &volume);
        res = bc127_set_volume(volume);
    }

    if(2 == argc) {
        res = try_str2uint8(argv[0], &link_id);
        res = try_str2uint8(argv[1], &volume);
        res = bc127_set_volume_id(link_id, volume);
    }
    if(res) {
        LOG_INFO(BC127, "SetVol %u Ok!", volume);
    } else {
        LOG_ERROR(BC127, "SetVol %u Err", volume);
        LOG_ERROR(BC127, "Usage: bsv LinkId Vol");
        LOG_INFO(BC127, "vol [0...F]");
    }

    return res;
}
