#include "usb_device_commands.h"

#include "convert.h"
#include "key_board_drv.h"
#include "std_includes.h"
#include "usb_device.h"
#include "usb_device_diag.h"

// compile

bool usb_device_timeout_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 <= argc) {
        LOG_INFO(USB, "PrevKeyInsertTimeOut:%u ms", key_insert_timeout_ms);
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &key_insert_timeout_ms);
    }

    if(res) {
        LOG_INFO(USB, "NewKeyInsertTimeOut:%u ms", key_insert_timeout_ms);
    } else {
        LOG_ERROR(USB, "Usage: udt KeyInsertTimeOutMs");
    }

    return res;
}

bool hid_keyboard_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t letter = '.';
    uint32_t time_out_ms = 40;
    if(1 == argc) {
        res = try_str2uint8(argv[0], &letter);
        if(false == res) {
            letter = argv[0][0];
            res = true;
        }
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &time_out_ms);
    }

    if(res) {
        LOG_INFO(USB, "TryPress [%c]", letter);
        res = usb_key_board_press(letter, time_out_ms);
        if(res) {
            LOG_INFO(USB, "Press [%c] Ok", letter);
        } else {
            LOG_ERROR(USB, "Press [%c] Err", letter);
        }
    } else {
        LOG_ERROR(USB, "Usage: ks letter");
    }
    return res;
}

bool hid_keyboard_send_ll_command(int32_t argc, char* argv[]) {
    bool res = false;
    memset(&keyBoardCode, 0, sizeof(KeyBoard_t));
    if(2 <= argc) {
        res = try_str2uint8(argv[0], &keyBoardCode.modifier.byte);
        if(false == res) {
            LOG_ERROR(USB, "ParseErr modifier [1....8]");
        }
        uint8_t i = 0;
        for(i = 0; i < (argc - 1); i++) {
            res = try_str2uint8(argv[1 + i], &keyBoardCode.key_code[i]);
            if(false == res) {
                LOG_ERROR(USB, "ParseErr KeyCode %u", i);
            }
        }
    }
    if(res) {
        res = usb_dev_press_key(keyBoardCode, 50);
        if(res) {
            LOG_INFO(USB, "PressOk");
        } else {
            LOG_ERROR(USB, "PressErr");
        }
    } else {
        LOG_ERROR(USB, "Usage: khl mod KeyCode1 KeyCode2 KeyCode3 KeyCode4 KeyCode5 KeyCode6");
    }
    return res;
}

bool hid_keyboard_send_text_command(int32_t argc, char* argv[]) {
    bool res = false;
    static char text[80] = "";
    uint32_t time_out = 250;
    if(1 <= argc) {
        strncpy(text, argv[0], sizeof(text));
        res = true;
    }
    if(2 <= argc) {
        res = try_str2uint32(argv[1], &time_out);
    }
    if(res) {
        LOG_INFO(USB, "SendText [%s]", text);
        res = usb_key_board_send_text(text, time_out);
        if(res) {
            LOG_INFO(USB, "SendTextOk");
        } else {
            LOG_ERROR(USB, "SendTextErr");
        }
    } else {
        LOG_ERROR(USB, "Usage: kt text to");
    }
    return res;
}

bool usb_device_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = usb_device_diag();
    return res;
}
