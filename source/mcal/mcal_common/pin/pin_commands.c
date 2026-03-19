#include "pin_commands.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "log.h"
#ifdef HAS_BOARD_INFO
#include "board_info.h"

#ifdef HAS_BOARD_INFO_DIAG
#include "board_diag.h"
#endif /*HAS_BOARD_INFO_DIAG*/

#endif /*HAS_BOARD_INFO*/
#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "pin_config.h"
#include "pin_diag.h"
#include "pin_mcal.h"
#include "pin_types.h"
#ifdef HAS_PIN_CUSTOM
#include "pin_custom_diag.h"
#include "pin_custom_drv.h"
#endif
#include "microcontroller.h"
#include "microcontroller_const.h"
#include "str_utils.h"
#include "table_utils.h"
#ifdef HAS_PIN_TEST
#include "test_pin.h"
#endif
#include "writer_config.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

bool pin_dir_command(int32_t argc, char* argv[]) {
    bool res = false;
    Pad_t pad = {.byte = 0};
    PinDir_t dir = PIN_DIR_UNDEF;
    if(2 <= argc) {
        res = parse_pad(argv, &pad);
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], (uint8_t*)&dir);
        if(false == res) {
            LOG_ERROR(PIN, "ParseErr Dirr %s", argv[2]);
        }
    }
    if(res) {
        switch(argc) {
        case 2: {
            dir = pin_dir_get(pad.byte);
            LOG_INFO(PIN, "Cur Pad:%s: Dir %s", PinPadToStr(pad.byte), PinDirToStr(dir));
        } break;
        case 3: {
            LOG_WARNING(PIN, "TrySetDirOk %s:%s", PinPadToStr(pad.byte), PinDirToStr(dir));
            res = pin_dir_set(pad.byte, (PinDir_t)dir);
            if(res) {
                LOG_INFO(PIN, "SetDirOk %s:%s", PinPadToStr(pad.byte), PinDirToStr(dir));
            } else {
                LOG_ERROR(PIN, "SetDirErr %s:%s", PinPadToStr(pad.byte), PinDirToStr(dir));
            }

        } break;
        }
    } else {
        LOG_ERROR(PIN, "Usage: gd port pin dir");
    }
    return res;
}
/*
gg D 1
*/
bool pin_get_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t logic_level = 0xFF;
    Pad_t pad = {.byte = 0};

    if(2 <= argc) {
        res = parse_pad(argv, &pad);
    }

    if(res) {
        res = pin_get_state(pad.byte, &logic_level);
        if(false == res) {
            LOG_ERROR(PIN, "ParseErr lgcLvl");
        } else {
            LOG_INFO(PIN, "%s:%u" CRLF, PinPadToStr(pad.byte), logic_level);
        }
    }
    if(2 != argc) {
        LOG_ERROR(PIN, "Usage: gg port pin");
        LOG_INFO(PIN, "port [A...Z]");
        LOG_INFO(PIN, "pin 0....15 ");
    }
    return res;
}

bool pin_pull_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t pull_code = PIN__PULL_UNDEF;
    Pad_t pad = {.byte = 0};

    if(2 <= argc) {
        res = parse_pad(argv, &pad);
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &pull_code);
        if(false == res) {
            LOG_ERROR(PIN, "ParseErr pull_code %s", argv[2]);
        }
    }

    if(res) {
        switch(argc) {
        case 2: {
            PinPullMode_t pull_mode = pin_pull_get(pad.byte);
            LOG_INFO(PIN, "PullGet Pad %s, Pull %u=%s " LOG_OK, PinPadToStr(pad.byte), pull_mode,
                     PinPullToStr(pull_mode));
        } break;
        case 3: {
            res = pin_pull_set(pad, (PinPullMode_t)pull_code);
            if(res) {
                LOG_INFO(PIN, "PullSet Pad %s Pull%s Ok" LOG_OK, PinPadToStr(pad.byte), PinPullToStr(pull_code));
            } else {
                LOG_ERROR(PIN, "PullSet Pad %s Pull%s Err" LOG_ER, PinPadToStr(pad.byte), PinPullToStr(pull_code));
            }

        } break;
        }
    } else {
        LOG_ERROR(PIN, "Usage: gp port pin pull");
        LOG_INFO(PIN, "port A(0)....H(7)");
        LOG_INFO(PIN, "pin 0....15 ");
        LOG_INFO(PIN, "pull 3-Air;2-Up;1-Down;3-Res ");
        res = false;
    }
    return res;
}

bool pin_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t logic_level;

    Pad_t pad = {.byte = 0};

    if(2 <= argc) {
        res = parse_pad(argv, &pad);
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &logic_level);
        if(false == res) {
            LOG_ERROR(PIN, "ParseErr logic_level %s", argv[2]);
        }
    }

    if(argc < 3) {
        LOG_ERROR(PIN, "Usage: gs port pin level");
        LOG_INFO(PIN, "port A....H");
        LOG_INFO(PIN, "pin 0....15 ");
        LOG_INFO(PIN, "level 0..1 ");
        res = false;
    }

    if(res) {
        LOG_INFO(PIN, "Set %s:%u" CRLF, PinPadToStr(pad.byte), logic_level);
        res = pin_logic_level_set(pad, logic_level);
        if(false == res) {
            LOG_ERROR(PIN, "Unable to set pin state");
        } else {
            LOG_INFO(PIN, "Set pin state %s %u", PinPadToStr(pad.byte), logic_level);
        }
    }
    return res;
}

static bool diag_pin(char* key_word1, char* key_word2) {
    bool res = false;
    static const table_col_t cols[] = {{5, "No"},        {7, "pad"},  {8, "mode"}, {7, "level"}, {8, "Fun"},
                                       {6, "dir"},       {6, "pull"}, {5, "MuxS"}, {5, "MuxG"},
#ifdef HAS_BOARD_INFO_DIAG
                                       {12, "connect1"},
#endif
                                       {12, "connect2"}, {15, "name"}};
    uint16_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    PinLogicLevel_t logic_level = PIN_LVL_UNDEF;
    uint8_t i = 0;
    char log_line[150];
    uint16_t pin_cnt = pin_get_cnt();
    for(i = 0; i < pin_cnt; i++) {
        if(PORT_UNDEF != PinConfig[i].pad.port) {
            PinDir_t dirr = pin_dir_get(PinConfig[i].pad.byte);
            PinPullMode_t pull = pin_pull_get(PinConfig[i].pad.byte);
            PinPinFunction_t function = PIN_FUN_UNDEF;
            res = pin_pin_fun_get(PinConfig[i].pad, &function);
            PinApiMode_t mode = pin_mode_get(PinConfig[i].pad.byte);

            uint8_t pin_mux = 0;

            res = pin_pin_mux_get(PinConfig[i].pad.port, PinConfig[i].pad.pin, &pin_mux);
#ifdef HAS_PIN_NRFX
            nrf_pin_pin_mcusel_t mcu_sel = nrf_pin_pin_mcu_select_get(PinConfig[i].pad.byte);
#endif
            strcpy(log_line, TSEP);
            logic_level = PIN_LVL_UNDEF;
            pin_get_state(PinConfig[i].pad.byte, &logic_level);
            snprintf(log_line, sizeof(log_line), "%s %5s " TSEP, log_line, PinPadToStr(PinConfig[i].pad.byte));
            snprintf(log_line, sizeof(log_line), "%s %6s " TSEP, log_line, PinModeToStr(mode));
            snprintf(log_line, sizeof(log_line), "%s   %s   " TSEP, log_line, PinLevelToStr(logic_level));
            snprintf(log_line, sizeof(log_line), "%s %6s " TSEP, log_line, PinFunToStr(function));
            snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, PinDirToStr(dirr));
            snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, PinPullToStr(pull));
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, PinConfig[i].mux);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, pin_mux);
#ifdef HAS_PIN_NRFX
            snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, McuSelToStr(mcu_sel));
#endif
#ifdef HAS_BOARD_INFO_DIAG
            snprintf(log_line, sizeof(log_line), "%s %10s " TSEP, log_line, Pad2ConnectorPin(PinConfig[i].pad));
#endif /*HAS_BOARD_INFO_DIAG*/
            snprintf(log_line, sizeof(log_line), "%s %10s " TSEP, log_line, PinGetCon2(PinConfig[i].pad.byte));
            snprintf(log_line, sizeof(log_line), "%s %13s " TSEP, log_line, PinPad2WireName(PinConfig[i].pad.byte));
            if(is_contain(log_line, key_word1, key_word2)) {
                cli_printf(TSEP " %3u ", num);
                cli_printf("%s" CRLF, log_line);
                // cli_printf(CRLF);
                num++;
                res = true;
            }
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool pin_list_command(int32_t argc, char* argv[]) {
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
        LOG_ERROR(PIN, "Usage: gl keyWord");
    }
    if(res) {
        res = diag_pin(keyWord1, keyWord2);
    }
    return res;
}

bool pin_toggle_command(int32_t argc, char* argv[]) {
    bool res = false;
    Pad_t pad = {.byte = 0};

    if(2 <= argc) {
        res = parse_pad(argv, &pad);
    }

    if(res) {
        res = pin_toggle(pad);
        if(false == res) {
            LOG_ERROR(PIN, "TogglePadErr %s", PinPadToStr(pad.byte));
        } else {
            LOG_INFO(PIN, "TogglePadOk %s", PinPadToStr(pad.byte));
        }
    } else {
        LOG_ERROR(PIN, "Usage: gt pin_port pin_pin");
    }
    return res;
}

bool pin_test_command(int32_t argc, char* argv[]) {
    bool res = false;
    Pad_t pad = {.byte = 0};

    if(2 <= argc) {
        res = parse_pad(argv, &pad);
    }

    if(res) {
        res = false;
#ifdef HAS_PIN_TEST
        LOG_INFO(PIN, "RunPadTest %s", PinPadToStr(pad.byte));
        res = test_pin_pin(pad.byte);
#endif
        if(res) {
            LOG_INFO(PIN, "PadTestOk %s", PinPadToStr(pad.byte));
        } else {
            LOG_ERROR(PIN, "PadTestErr %s", PinPadToStr(pad.byte));
        }
    } else {
        LOG_ERROR(PIN, "Usage: ge pin_port pin_pin");
    }
    return res;
}

bool pin_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = pin_mcal_init();
        if(res) {
            LOG_INFO(PIN, "Init,Ok");
        } else {
            LOG_ERROR(PIN, "Init,Err");
        }
    }

    return res;
}

bool pin_mux_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t mux = 0;
    Pad_t pad = {.byte = 0};

    if(2 <= argc) {
        res = parse_pad(argv, &pad);
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &mux);
        if(false == res) {
            LOG_ERROR(PIN, "ParseErr Mux %s", argv[2]);
        }
    }

    if(res) {
        switch(argc) {
        case 2: {
            res = pin_pin_mux_get(pad.port, pad.pin, &mux);
            if(res) {
                LOG_INFO(PIN, "Get,%s,Mux:%u", PinPadToStr(pad), mux);
            }
        } break;
        case 3: {
            LOG_INFO(PIN, "Set,%s,Mux:%u", PinPadToStr(pad), mux);
            res = pin_pin_mux_set(pad.port, pad.pin, mux);
        } break;
        }
    } else {
        LOG_ERROR(PIN, "Usage: gm pin_port pin_pin mux");
    }
    return res;
}
