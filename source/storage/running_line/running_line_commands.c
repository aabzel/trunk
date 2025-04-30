#include "running_line_commands.h"

#include <stdio.h>
#include <string.h>

#include "convert.h"
#include "log.h"
#include "running_line.h"

bool cmd_running_line_get(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(RUNNING_LINE, "ParseErr num %s", argv[0]);
        }
    }

    if(res) {
        LOG_INFO(RUNNING_LINE, "N:%u,[%s]", num, running_line_get_text(num));
    } else {
        LOG_ERROR(RUNNING_LINE, "Usage: rlg Num");
    }
    return res;
}

bool cmd_running_line_diag(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = running_line_diag();
    } else {
        LOG_ERROR(RUNNING_LINE, "Usage: rld");
    }
    return res;
}

bool cmd_running_line_set_text(int32_t argc, char* argv[]) {
    bool res = false;

    char text[20] = "";
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(RUNNING_LINE, "ParseErr num %s", argv[0]);
        }
    }

    if(2 <= argc) {
        strncpy(text, argv[1], sizeof(text));
        res = true;
    }

    if(res) {
        if(2 == argc) {
            res = running_line_set_text(num, text);
        }
    } else {
        LOG_ERROR(RUNNING_LINE, "Usage: rlsp Num prefix");
    }

    return res;
}

bool cmd_running_line_set_prefix(int32_t argc, char* argv[]) {
    bool res = false;

    char prefix[20] = "";
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(RUNNING_LINE, "ParseErr num %s", argv[0]);
        }
    }

    if(2 <= argc) {
        strncpy(prefix, argv[1], sizeof(prefix));
        res = true;
    }

    if(res) {
        if(2 == argc) {
            res = running_line_add_prefix(num, prefix);
        }
    } else {
        LOG_ERROR(RUNNING_LINE, "Usage: rlsp Num prefix");
    }

    return res;
}

bool cmd_running_line_set_suffix(int32_t argc, char* argv[]) {
    bool res = false;

    char suffix[20] = "";
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(RUNNING_LINE, "ParseErr num %s", argv[0]);
        }
    }

    if(2 <= argc) {
        strncpy(suffix, argv[1], sizeof(suffix));
        res = true;
    }

    if(res) {
        if(2 == argc) {
            res = running_line_add_suffix(num, suffix);
        }
    } else {
        LOG_ERROR(RUNNING_LINE, "Usage: rlss Num Suffix");
    }

    return res;
}

bool cmd_running_line_init(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(RUNNING_LINE, "ParseErr num %s", argv[0]);
        }
    }

    if(res) {
        res = running_line_init_one(num);
    }
    return res;
}
