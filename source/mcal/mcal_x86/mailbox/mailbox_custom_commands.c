#include "mailbox_custom_commands.h"

#include "convert.h"
#include "log.h"
#include "mailbox_custom_diag.h"

bool mailbox_diag_channel_2_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(MAILBOX, res, "Num");
    }

    if(res) {
        res = mailbox_diag_channel_done(num);
        log_res(MAILBOX, res, "DiagChDone");

        res = mailbox_diag_channel_req(num);
        log_res(MAILBOX, res, "DiagChReq");
    } else {
        LOG_ERROR(MAILBOX, "Usage mddcd Num");
    }

    return res;
}

bool mailbox_diag_channel_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(MAILBOX, res, "Num");
    }

    if(res) {
        res = mailbox_diag_channel(num);
        log_res(MAILBOX, res, "DiagCh");
    } else {
        LOG_ERROR(MAILBOX, "Usage mddc Num");
    }

    return res;
}

bool mailbox_diag_low_level_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 2;
    char keyword[80] = {0};
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(MAILBOX, res, "Num");
    }

    if(2 <= argc) {
        strcpy(keyword, argv[1]);
    }

    if(res) {
        res = mailbox_diag_low_level(num, keyword);
        log_res(MAILBOX, res, "DiagLL");
    } else {
        LOG_ERROR(MAILBOX, "Usage mddl Num");
    }

    return res;
}

bool mailbox_raw_reg_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t channel = 1;
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &channel);
        log_res(MAILBOX, res, "Num");
    }

    if(res) {
        res = mailbox_raw_reg_diag(1, channel);
        log_res(MAILBOX, res, "RawRegDiag");
    } else {
        LOG_ERROR(MAILBOX, "Usage mbrr Channel");
    }

    return res;
}
