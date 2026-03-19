#include "input_capture_commands.h"

#include "common_diag.h"
#include "convert.h"
#include "input_capture_diag.h"
#include "input_capture_mcal.h"
#include "log.h"

bool input_capture_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = input_capture_mcal_init();
    return res;
}

bool input_capture_diag_command(int32_t argc, char* argv[]) {
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
        LOG_ERROR(INPUT_CAPTURE, "Usage: pwd keyWord");
    }
    if(res) {
        res = input_capture_diag(keyWord1, keyWord2);
    }

    return res;
}

bool input_capture_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(INPUT_CAPTURE, "ParseErr InputCaptureNum %s", argv[0]);
        }
    }

    if(res) {
        res = input_capture_reset(num);
        if(res) {
            LOG_INFO(INPUT_CAPTURE, "ResetOk");
        } else {
            LOG_ERROR(INPUT_CAPTURE, "ResetErr");
        }
    } else {
        LOG_ERROR(INPUT_CAPTURE, "Usage: icr Num");
    }
    return res;
}

bool input_capture_enable_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    bool on = 0;
    if(2 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(INPUT_CAPTURE, "ParseErr InputCaptureNum %s", argv[0]);
        }

        res = try_str2bool(argv[1], &on);
        if(false == res) {
            LOG_ERROR(INPUT_CAPTURE, "ParseErrOn %s", argv[1]);
        }
    }

    if(res) {
        LOG_INFO(INPUT_CAPTURE, "INPUT_CAPTURE%u %s", num, OnOffToStr(on));
        res = input_capture_ctrl(num, on);
        if(res) {
            LOG_INFO(INPUT_CAPTURE, "Ok");
        } else {
            LOG_ERROR(INPUT_CAPTURE, "ERR");
        }
    } else {
        LOG_ERROR(INPUT_CAPTURE, "Usage: pe InputCaptureNum En");
    }
    return res;
}
