#include "wm8731_commands.h"

#include <stdio.h>

#include "std_includes.h"

#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "str_utils.h"
#include "table_utils.h"
#include "test_wm8731.h"
#include "wm8731_drv.h"
#include "writer_config.h"

static bool wm8731_diag(uint8_t num, char* key_word1, char* key_word2) {
    bool res = false;
    static const table_col_t cols[] = {{5, "No"}, {6, "addr"}, {6, "val"}, {14, "name"}};
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint8_t i = 0;
    char line_str[120];
    uint16_t reg_cnt = wm8731_get_reg_cnt();
    for(i = 0; i < reg_cnt; i++) {
        uint8_t reg_val = 0;
        res = wm8731_get_reg(num, Wm8731RegMap[i].reg_addr, &reg_val);
        if(res) {
            strcpy(line_str, TSEP);
            snprintf(line_str, sizeof(line_str), "%s 0x%02x " TSEP, line_str, Wm8731RegMap[i].reg_addr);
            snprintf(line_str, sizeof(line_str), "%s 0x%02x " TSEP, line_str, reg_val);
            snprintf(line_str, sizeof(line_str), "%s %12s " TSEP, line_str, Wm8731RegMap[i].name);

            if(is_contain(line_str, key_word1, key_word2)) {
                cli_printf(TSEP " %3u ", num);
                cli_printf("%s" CRLF, line_str);
                num++;
            }
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool cmd_wm8731_reg_map(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
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
        LOG_ERROR(WM8731, "Usage: gl keyWord");
    }
    if(true == res) {
        res = wm8731_diag(num, keyWord1, keyWord2);
    }
    return res;
}

bool cmd_wm8731_get_reg(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t reg_addr = 0;
    uint8_t num = 1;
    if(1 == argc) {
        res = try_str2uint8(argv[0], &reg_addr);
    }
    if(res) {
        uint8_t reg_val = 0;
        res = wm8731_get_reg(num, reg_addr, &reg_val);
        if(res) {
            LOG_INFO(WM8731, "Addr 0x%02x Val: 0x%02x", reg_addr, reg_val);
        }
    }
    return res;
}

bool cmd_wm8731_set_reg(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t reg_addr = 0;
    uint8_t reg_val = 0;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &reg_addr);
    }
    if(2 <= argc) {
        res = try_str2uint8(argv[1], &reg_val);
    }
    if(res) {
        res = wm8731_set_reg(num, reg_addr, reg_val);
        if(res) {
            LOG_INFO(WM8731, "Addr 0x%02x Val: 0x%02x", reg_addr, reg_val);
        }
    }
    return res;
}

bool cmd_wm8731_diag(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(0 == argc) {
        res = wm8731_reset(num);
    } else {
        LOG_ERROR(WM8731, "Usage: wmt");
    }
    return res;
}

bool cmd_wm8731_reset(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
    } else {
        LOG_ERROR(WM8731, "Usage: wmr");
    }
    return res;
}

bool cmd_wm8731_init(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(0 == argc) {
        res = wm8731_init_one(num);
        if(false == res) {
            LOG_ERROR(WM8731, "InitErr");
        } else {
            LOG_INFO(WM8731, "InitOk");
        }
    }
    return res;
}

bool cmd_wm8731_set_sidetone(int32_t argc, char* argv[]) {
    bool state = false;
    bool res = false;
    uint8_t num = 1;
    if(1 == argc) {
        res = try_str2bool(argv[0], &state);
    }
    if(res) {
        res = wm8731_set_sidetone(num, state);
    } else {
        LOG_ERROR(WM8731, "Usage: wms OnOff");
    }
    return res;
}

bool cmd_wm8731_set_volume(int32_t argc, char* argv[]) {
    bool res = false;
    int8_t left = -73;
    int8_t right = -73;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2int8(argv[0], &left);
        res = try_str2int8(argv[0], &right);
    }
    if(2 <= argc) {
        res = try_str2int8(argv[1], &right);
    }
    if(res) {
        LOG_INFO(WM8731, "TrySetVlo L%d R%d", left, right);
        set_log_level(WM8731, LOG_LEVEL_DEBUG);
        res = wm8731_set_volume(num, left, right);
        if(res) {
            LOG_INFO(WM8731, "Ok! L%d R%d", left, right);
        } else {
            LOG_ERROR(WM8731, "SetLovErr! L%d R%d", left, right);
        }
    } else {
        LOG_ERROR(WM8731, "Usage: wmv left right");
    }
    set_log_level(WM8731, LOG_LEVEL_INFO);
    return res;
}

bool cmd_wm8731_1khz(int32_t argc, char* argv[]) {
    bool res = false;
    int32_t amplitude = 0;
    uint32_t duration_ms = 3000;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2int32(argv[0], &amplitude);
        if(false == res) {
            LOG_ERROR(WM8731, "ParseErr Amplitude %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &duration_ms);
        if(false == res) {
            LOG_ERROR(WM8731, "ParseErr DurationMs %s", argv[1]);
        }
    }

    if(res) {
        res = wm8731_play_1khz(num, (SampleType_t)amplitude, duration_ms);

        if(res) {
            LOG_INFO(WM8731, "Play1kHzOk");
        } else {
            LOG_ERROR(WM8731, "Play1kHzErr");
        }
    } else {
        LOG_ERROR(WM8731, "Usage: wmk amp duration");
        /* Example:
         wmk 300  1000
         wmk 2000  10000
          */
    }
    return res;
}

/*
    wmp 1000 100
 * */
bool cmd_wm8731_tone(int32_t argc, char* argv[]) {
    bool res = false;
    double freq = 0.0;
    int32_t amplitude = 0;
    uint32_t duration_ms = 3000;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2double(argv[0], &freq);
        if(false == res) {
            LOG_ERROR(WM8731, "ParseErr freq %s", argv[0]);
        }
    }
    if(2 <= argc) {
        res = try_str2int32(argv[1], &amplitude);
        if(false == res) {
            LOG_ERROR(WM8731, "ParseErr Amplitude %s", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &duration_ms);
        if(false == res) {
            LOG_ERROR(WM8731, "ParseErr DurationMs %s", argv[2]);
        }
    }

    if(res) {
        switch(argc) {
        case 2: {
            res = wm8731_play_freq(num, freq, (SampleType_t)amplitude);
        } break;
        case 3: {
            res = test_wm8731_play_freq(num, (double)freq, (SampleType_t)amplitude, duration_ms);
        } break;
        }

        if(res) {
            LOG_INFO(WM8731, "PlayOk");
        } else {
            LOG_ERROR(WM8731, "ChPlayErr");
        }
    } else {
        LOG_ERROR(WM8731, "Usage: wmp freq amp time");
        /* Example:
         wmp 1000 90000 1000
         wmp 2000 90000 10000
          */
    }
    return res;
}

bool cmd_wm8731_bypass(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    res = wm8731_bypass(num);
    return res;
}

bool cmd_wm8731_listen(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    uint32_t duration_ms = 3000;
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &duration_ms);
        if(false == res) {
            LOG_ERROR(WM8731, "ParseErr DurationMs %s", argv[0]);
        }
    }

    if(res) {
        res = wm8731_listen(num, duration_ms);
        if(res) {
            LOG_INFO(WM8731, "RecOk");
        } else {
            LOG_ERROR(WM8731, "RecErr");
        }
    } else {
        LOG_ERROR(WM8731, "Usage: wml duration_ms");
    }

    return res;
}
