#include "can_custom_commands.h"

#include <stdio.h>

#include "array_diag.h"
#include "can_custom.h"
#include "can_mcal.h"
#include "convert.h"
#include "log.h"

bool can_diag_custom_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    if(res) {
        // res = can_diag_custom();
        log_res(CAN, res, "DiagCustom");
    } else {
        LOG_ERROR(CAN, "Usage cdc");
    }

    return res;
}
/*
  can_diag_mail_box 0
  */
bool can_diag_mail_box_command(int32_t argc, char* argv[]) {
    uint8_t num = 0;
    bool res = false;

    if(0 <= argc) {
        num = 0;
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "Num");
    }

    if(res) {
        // res = can_diag_mail_box(num, "", "");
        log_res(CAN, res, "MailBox");

    } else {
        LOG_ERROR(CAN, "Usage cdmb Num");
    }

    return res;
}

bool can_send_sdk_command(int32_t argc, char* argv[]) {
    bool res = false;
    CanMessage_t Message = {0};
    uint32_t array_len = 0;

    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &Message.identifier.extended);
        log_res(CAN, res, "Id");
    }

    if(3 <= argc) {
        res = try_str2array(argv[2], Message.data, sizeof(Message.data), &array_len);
        if(false == res) {
            LOG_WARNING(CAN, "ExtractHexArrayErr  [%s]", argv[2]);
            snprintf((char*)Message.data, sizeof(Message.data), "%s", argv[2]);
            array_len = strlen(argv[2]);
            res = true;
        } else {
            LOG_WARNING(CAN, "SpotSize:%u Byte", array_len);
        }
    }

    if(res) {
        if(array_len <= 8) {
            Message.id_type = can_id_val_to_id_type(Message.identifier.extended);
            Message.size = array_len;
            Message.frame_type = CAN_TX_FRAME_DATA;
            res = can_mcal_transmit_message_sdk(num, &Message);
            if(res) {
                print_hex(Message.data, array_len);
                LOG_INFO(CAN, "%u SendOk %u byte", num, array_len);
                cli_printf(CRLF);
            } else {
                LOG_ERROR(CAN, "%u SendErr", num);
            }
        }
    } else {
        LOG_ERROR(CAN, "Usage: cs instance Id hex_string");
        LOG_INFO(CAN, "instance [1...%u]", CAN_COUNT);
        LOG_INFO(CAN, "hex_string 0x[0...F]+");
    }
    return res;
}
