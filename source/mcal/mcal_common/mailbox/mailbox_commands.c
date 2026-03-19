#include "mailbox_commands.h"

#include <stdio.h>

#include "convert.h"
#include "log.h"
#include "mailbox_mcal.h"

bool mailbox_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    uint8_t num = 0;
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        switch(argc) {
        case 0: {
            res = mailbox_diag();
            log_res(MAILBOX, res, "Diag1");
            res = mailbox_diag();
            log_res(MAILBOX, res, "Diag");
        } break;
        case 1: {
            res = mailbox_diag_one(num);
            log_res(MAILBOX, res, "DiagN");
        } break;
        default:
            break;
        }
    } else {
        LOG_ERROR(MAILBOX, "Usage mbd Num");
    }

    return res;
}

bool mailbox_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }
    if(res) {
        res = mailbox_init_one(num);
        log_res(MAILBOX, res, "Init");
    }
    return res;
}

/*
 mbs 1 1 Hi
 mbs 0 2 Hi
 */
bool mailbox_send_low_level_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t size = 0;
    uint8_t dist_core_id = 1;
    uint8_t num = 1;
    uint32_t channel = 1;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &dist_core_id);
        log_res(MAILBOX, res, "Core");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &channel);
        log_res(MAILBOX, res, "Ch");
    }

    if(4 <= argc) {
        res = try_str2uint8(argv[3], &num);
    }

    MailBoxHandle_t* Node = MailBoxGetNode(num);
    if(Node) {
        if(3 <= argc) {
            res = try_str2array(argv[2], Node->TxData, Node->tx_data_size, &size);
            log_res(MAILBOX, res, "ReadHex");
            if(false == res) {
                LOG_WARNING(MAILBOX, "ExtractHexArrayErr[%s]", argv[2]);
                snprintf((char*)Node->TxData, Node->tx_data_size, "%s", argv[2]);
                size = strlen(argv[2]);
                res = true;
            }
        }
    }

    if(res) {
        res = mailbox_send_request(num, dist_core_id, channel, Node->TxData, size);
        log_res(MAILBOX, res, "Send");
    } else {
        LOG_ERROR(MAILBOX, "Usage mbs ToCore Ch HexArray Num");
    }

    return res;
}

bool mailbox_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t size = 0;
    uint8_t TxData[512] = {0};
    uint8_t num = 1;
    uint8_t dist_core_id = 1;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(MAILBOX, res, "num");
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &dist_core_id);
        log_res(MAILBOX, res, "Core");
    }

    if(3 <= argc) {
        res = try_str2array(argv[2], TxData, sizeof(TxData), &size);
        log_res(MAILBOX, res, "ReadHex");
        if(false == res) {
            LOG_WARNING(MAILBOX, "ExtractHexArrayErr[%s]", argv[2]);
            snprintf((char*)TxData, sizeof(TxData), "%s", argv[2]);
            size = strlen(argv[2]);
            res = true;
        }
    }

    if(res) {
        res = mailbox_send(num, (CpuCoreNumber_t)dist_core_id, TxData, size);
        log_res(MAILBOX, res, "Send");
    } else {
        LOG_ERROR(MAILBOX, "Usage mbs Num ToCore HexArray");
    }

    return res;
}
