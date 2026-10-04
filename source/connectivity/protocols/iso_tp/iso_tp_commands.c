#include "iso_tp_commands.h"

#include <stdio.h>

#include "array.h"
#include "convert.h"
#include "iso_tp_mcal.h"
#include "log.h"
#include "std_includes.h"
#ifdef HAS_CRC32
#include "crc32.h"
#endif

static uint8_t data[ISO_TP_MTU] = {0};

bool iso_tp_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = iso_tp_diag();
        log_info_res(ISO_TP, res, "Diag");
    } else {
        LOG_ERROR(ISO_TP, "Usage: tbfpd if");
    }
    return res;
}

/*
  iso_tp_send 1 0xd Hello_Com6_I_am_COM4
  iso_tp_send 1 0x1122334455667788991122334455
 */
bool iso_tp_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    uint32_t size = 0;
    uint8_t target_addr = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(ISO_TP, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &target_addr);
        log_info_res(ISO_TP, res, "TxAddr");
    }

    if(3 <= argc) {
        memset(data, 0, sizeof(data));
        res = try_str2array(argv[2], data, sizeof(data), &size);
        if(false == res) {
            LOG_WARNING(ISO_TP, "ExtractHexArrayErr[%s]", argv[2]);
            snprintf((char*)data, sizeof(data), "%s", argv[2]);
            size = strlen(argv[2]);
            res = true;
        }
    }

    if(res) {
        LOG_INFO(ISO_TP, "TrySend Num:%u,Size:%u", num, size);
        res = iso_tp_send(num, target_addr, data, size);
        log_info_res(ISO_TP, res, "Send");
    } else {
        LOG_ERROR(ISO_TP, "Usage: iso_tp Num TargetAddr HExData");
    }

    return res;
}

/*
tptsj 1 0xd 4094
 */
bool iso_tp_test_send_jumbo_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t target_addr = 0;
    memset(data, 0xA5, ISO_TP_MTU);
    uint32_t size = ISO_TP_MTU - 1;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(ISO_TP, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &target_addr);
        log_info_res(ISO_TP, res, "TxAddr");
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &size);
        log_info_res(ISO_TP, res, "Size");
    }

    if(res) {
        res = array_incr(data, size, 0);
        uint32_t crc32 = crc32_calc(data, size);
        LOG_INFO(ISO_TP, "TrySendJumbo Num:%u,Target:0x%x,crc32:0x%08X,Size:%u", num, target_addr, crc32, size);
        res = iso_tp_send(num, target_addr, data, size);
        log_info_res(ISO_TP, res, "SendJumbo");
    } else {
        LOG_ERROR(ISO_TP, "Usage: tptsj Num TargetAddr");
    }

    return res;
}

bool iso_tp_buff_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint32_t size = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(ISO_TP, res, "Num");
        if(false == res) {
            LOG_ERROR(ISO_TP, "ParseErr num %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &size);
        log_info_res(ISO_TP, res, "Size");
    }

    if(res) {
        res = iso_tp_buff_print(num, size, ISO_TP_BUFF_RX);
        res = iso_tp_buff_print(num, size, ISO_TP_BUFF_TX);
    }
    return res;
}

bool iso_tp_compose_address_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t src_addr = 0;
    uint8_t dist_addr = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &src_addr);
        log_info_res(ISO_TP, res, "SrcAddr");
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &dist_addr);
        log_info_res(ISO_TP, res, "DistAddr");
    }

    if(res) {
        uint32_t final_id = 0;
        final_id = iso_tp_compose_normal_fixed_addr(src_addr, dist_addr);
        LOG_INFO(ISO_TP, "Src:0x%02X,Dist:0x%02X->CAN_ID:0x%08X", src_addr, dist_addr, final_id);
    } else {
        LOG_ERROR(ISO_TP, "Usage: tpca Src Dst");
    }
    return res;
}

bool iso_tp_init_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = iso_tp_mcal_init();
        log_info_res(ISO_TP, res, "Init");
    } else {
        LOG_ERROR(ISO_TP, "Usage: tpi");
    }
    return res;
}

bool iso_tp_writer_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(ISO_TP, res, "Num");
    }

    if(res) {
        res = iso_tp_writer(num);
        log_info_res(ISO_TP, res, "Writer");
    } else {
        LOG_ERROR(ISO_TP, "Usage: tpw Num");
    }
    return res;
}
