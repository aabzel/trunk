#include "can_cat_commands.h"

#include "can_cat_mcal.h"
#include "convert.h"
#include "iso_tp_mcal.h"
#include "log.h"

bool can_cat_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }
    if(res) {
        res = can_cat_diag();
        log_info_res(CAN_CAT, res, "Diag");
    } else {
        LOG_ERROR(CAN_CAT, "Usage: fdat");
    }

    return res;
}

bool can_cat_init_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 == argc) {
        res = can_cat_mcal_init();
        log_info_res(CAN_CAT, res, "Init");
    }
    return res;
}

bool can_cat_config_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t com_num = 5;
    uint32_t can_bit_rate = 250000;
    uint32_t my_addr = 0xE;
    uint32_t dist_addr = 0xA;

    uint8_t data[4 * 1024 + 1] = {0};
    uint32_t size = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &com_num);
        log_res(CAN_CAT, res, "ComNum");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &can_bit_rate);
        log_res(CAN_CAT, res, "BitRate");
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &my_addr);
        log_res(CAN_CAT, res, "MyAddr");
    }

    if(4 <= argc) {
        res = try_str2uint32(argv[3], &dist_addr);
        log_res(CAN_CAT, res, "SubScribeAddr");
    }

    if(5 <= argc) {
        res = try_str2array(argv[4], data, sizeof(data), &size);
        if(false == res) {
            LOG_WARNING(ISO_TP, "ExtractHexArrayErr[%s]", argv[4]);
            snprintf((char*)data, sizeof(data), "%s", argv[4]);
            size = strlen(argv[4]);
            res = true;
        }
    }

    if(res) {
        res = can_cat_config(com_num, can_bit_rate, my_addr, dist_addr);
        log_info_res(CAN_CAT, res, "Config");

        if(5 <= argc) {
            res = iso_tp_send(1, dist_addr, data, size);
            log_res(CAN_CAT, res, "Send");
        }

    } else {
        LOG_ERROR(CAN_CAT, "ccc COMx CANbitRate MyId SubScribeId IdType");
    }

    return res;
}
