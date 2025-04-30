#include "gpio_commands.h"

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
#include "gpio_config.h"
#include "gpio_diag.h"
#include "gpio_mcal.h"
#include "gpio_types.h"
#ifdef HAS_GPIO_CUSTOM
#include "gpio_custom_diag.h"
#include "gpio_custom_drv.h"
#endif
#include "microcontroller.h"
#include "microcontroller_const.h"
#include "str_utils.h"
#include "table_utils.h"
#ifdef HAS_GPIO_TEST
#include "test_gpio.h"
#endif
#include "writer_config.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

bool gpio_dir_command(int32_t argc, char* argv[]) {
    bool res = false;
    Pad_t pad = {.byte = 0};
    GpioDir_t dir = GPIO_DIR_UNDEF;
    if(2 <= argc) {
        res = parse_pad(argv, &pad);
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], (uint8_t*)&dir);
        if(false == res) {
            LOG_ERROR(GPIO, "ParseErr Dirr %s", argv[2]);
        }
    }
    if(res) {
        switch(argc) {
        case 2: {
            dir = gpio_dir_get(pad.byte);
            LOG_INFO(GPIO, "Cur Pad:%s: Dir %s", GpioPad2Str(pad.byte), GpioDir2Str(dir));
        } break;
        case 3: {
            LOG_WARNING(GPIO, "TrySetDirOk %s:%s", GpioPad2Str(pad.byte), GpioDir2Str(dir));
            res = gpio_dir_set(pad.byte, (GpioDir_t)dir);
            if(res) {
                LOG_INFO(GPIO, "SetDirOk %s:%s", GpioPad2Str(pad.byte), GpioDir2Str(dir));
            } else {
                LOG_ERROR(GPIO, "SetDirErr %s:%s", GpioPad2Str(pad.byte), GpioDir2Str(dir));
            }

        } break;
        }
    } else {
        LOG_ERROR(GPIO, "Usage: gd port pin dir");
    }
    return res;
}
/*
gg D 1
*/
bool gpio_get_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t logic_level = 0xFF;
    Pad_t pad = {.byte = 0};

    if(2 <= argc) {
        res = parse_pad(argv, &pad);
    }

    if(res) {
        res = gpio_get_state(pad.byte, &logic_level);
        if(false == res) {
            LOG_ERROR(GPIO, "ParseErr lgcLvl");
        } else {
            LOG_INFO(GPIO, "%s:%u" CRLF, GpioPad2Str(pad.byte), logic_level);
        }
    }
    if(2 != argc) {
        LOG_ERROR(GPIO, "Usage: gg port pin");
        LOG_INFO(GPIO, "port [A...Z]");
        LOG_INFO(GPIO, "pin 0....15 ");
    }
    return res;
}

bool gpio_pull_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t pull_code = GPIO__PULL_UNDEF;
    Pad_t pad = {.byte = 0};

    if(2 <= argc) {
        res = parse_pad(argv, &pad);
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &pull_code);
        if(false == res) {
            LOG_ERROR(GPIO, "ParseErr pull_code %s", argv[2]);
        }
    }

    if(res) {
        switch(argc) {
        case 2: {
            GpioPullMode_t pull_mode = gpio_pull_get(pad.byte);
            LOG_INFO(GPIO, "PullGet Pad %s, Pull %u=%s " LOG_OK, GpioPad2Str(pad.byte), pull_mode,
                     GpioPull2Str(pull_mode));
        } break;
        case 3: {
            res = gpio_pull_set(pad, (GpioPullMode_t)pull_code);
            if(res) {
                LOG_INFO(GPIO, "PullSet Pad %s Pull%s Ok" LOG_OK, GpioPad2Str(pad.byte), GpioPull2Str(pull_code));
            } else {
                LOG_ERROR(GPIO, "PullSet Pad %s Pull%s Err" LOG_ER, GpioPad2Str(pad.byte), GpioPull2Str(pull_code));
            }

        } break;
        }
    } else {
        LOG_ERROR(GPIO, "Usage: gp port pin pull");
        LOG_INFO(GPIO, "port A(0)....H(7)");
        LOG_INFO(GPIO, "pin 0....15 ");
        LOG_INFO(GPIO, "pull 3-Air;2-Up;1-Down;3-Res ");
        res = false;
    }
    return res;
}

bool gpio_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t logic_level;

    Pad_t pad = {.byte = 0};

    if(2 <= argc) {
        res = parse_pad(argv, &pad);
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &logic_level);
        if(false == res) {
            LOG_ERROR(GPIO, "ParseErr logic_level %s", argv[2]);
        }
    }

    if(argc < 3) {
        LOG_ERROR(GPIO, "Usage: gs port pin level");
        LOG_INFO(GPIO, "port A....H");
        LOG_INFO(GPIO, "pin 0....15 ");
        LOG_INFO(GPIO, "level 0..1 ");
        res = false;
    }

    if(res) {
        LOG_INFO(GPIO, "Set %s:%u" CRLF, GpioPad2Str(pad.byte), logic_level);
        res = gpio_logic_level_set(pad, logic_level);
        if(false == res) {
            LOG_ERROR(GPIO, "Unable to set gpio state");
        } else {
            LOG_INFO(GPIO, "Set gpio state %s %u", GpioPad2Str(pad.byte), logic_level);
        }
    }
    return res;
}

static bool diag_gpio(char* key_word1, char* key_word2) {
    bool res = false;
    static const table_col_t cols[] = {{5, "No"},        {7, "pad"},  {8, "mode"}, {7, "level"}, {8, "Fun"},
                                       {6, "dir"},       {6, "pull"}, {5, "MuxS"}, {5, "MuxG"},
#ifdef HAS_BOARD_INFO_DIAG
                                       {12, "connect1"},
#endif
                                       {12, "connect2"}, {15, "name"}};
    uint16_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    GpioLogicLevel_t logic_level = GPIO_LVL_UNDEF;
    uint8_t i = 0;
    char log_line[150];
    uint16_t gpio_cnt = gpio_get_cnt();
    for(i = 0; i < gpio_cnt; i++) {
        if(PORT_UNDEF != GpioConfig[i].pad.port) {
            GpioDir_t dirr = gpio_dir_get(GpioConfig[i].pad.byte);
            GpioPullMode_t pull = gpio_pull_get(GpioConfig[i].pad.byte);
            GpioPinFunction_t function = GPIO_FUN_UNDEF;
            res = gpio_pin_fun_get(GpioConfig[i].pad, &function);
            GpioApiMode_t mode = gpio_mode_get(GpioConfig[i].pad.byte);

            uint8_t pin_mux = 0;

            res = gpio_pin_mux_get(GpioConfig[i].pad.port, GpioConfig[i].pad.pin, &pin_mux);
#ifdef HAS_GPIO_NRFX
            nrf_gpio_pin_mcusel_t mcu_sel = nrf_gpio_pin_mcu_select_get(GpioConfig[i].pad.byte);
#endif
            strcpy(log_line, TSEP);
            logic_level = GPIO_LVL_UNDEF;
            gpio_get_state(GpioConfig[i].pad.byte, &logic_level);
            snprintf(log_line, sizeof(log_line), "%s %5s " TSEP, log_line, GpioPad2Str(GpioConfig[i].pad.byte));
            snprintf(log_line, sizeof(log_line), "%s %6s " TSEP, log_line, GpioMode2Str(mode));
            snprintf(log_line, sizeof(log_line), "%s   %s   " TSEP, log_line, GpioLevel2Str(logic_level));
            snprintf(log_line, sizeof(log_line), "%s %6s " TSEP, log_line, GpioFunToStr(function));
            snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, GpioDir2Str(dirr));
            snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, GpioPull2Str(pull));
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, GpioConfig[i].mux);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, pin_mux);
#ifdef HAS_GPIO_NRFX
            snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, McuSel2Str(mcu_sel));
#endif
#ifdef HAS_BOARD_INFO_DIAG
            snprintf(log_line, sizeof(log_line), "%s %10s " TSEP, log_line, Pad2ConnectorPin(GpioConfig[i].pad));
#endif /*HAS_BOARD_INFO_DIAG*/
            snprintf(log_line, sizeof(log_line), "%s %10s " TSEP, log_line, GpioGetCon2(GpioConfig[i].pad.byte));
            snprintf(log_line, sizeof(log_line), "%s %13s " TSEP, log_line, GpioPad2WireName(GpioConfig[i].pad.byte));
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

bool gpio_list_command(int32_t argc, char* argv[]) {
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
        LOG_ERROR(GPIO, "Usage: gl keyWord");
    }
    if(res) {
        res = diag_gpio(keyWord1, keyWord2);
    }
    return res;
}

bool gpio_toggle_command(int32_t argc, char* argv[]) {
    bool res = false;
    Pad_t pad = {.byte = 0};

    if(2 <= argc) {
        res = parse_pad(argv, &pad);
    }

    if(res) {
        res = gpio_toggle(pad);
        if(false == res) {
            LOG_ERROR(GPIO, "TogglePadErr %s", GpioPad2Str(pad.byte));
        } else {
            LOG_INFO(GPIO, "TogglePadOk %s", GpioPad2Str(pad.byte));
        }
    } else {
        LOG_ERROR(GPIO, "Usage: gt gpio_port gpio_pin");
    }
    return res;
}

bool gpio_test_command(int32_t argc, char* argv[]) {
    bool res = false;
    Pad_t pad = {.byte = 0};

    if(2 <= argc) {
        res = parse_pad(argv, &pad);
    }

    if(res) {
        res = false;
#ifdef HAS_GPIO_TEST
        LOG_INFO(GPIO, "RunPadTest %s", GpioPad2Str(pad.byte));
        res = test_gpio_pin(pad.byte);
#endif
        if(res) {
            LOG_INFO(GPIO, "PadTestOk %s", GpioPad2Str(pad.byte));
        } else {
            LOG_ERROR(GPIO, "PadTestErr %s", GpioPad2Str(pad.byte));
        }
    } else {
        LOG_ERROR(GPIO, "Usage: ge gpio_port gpio_pin");
    }
    return res;
}

bool gpio_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = gpio_mcal_init();
        if(res) {
            LOG_INFO(GPIO, "Init,Ok");
        } else {
            LOG_ERROR(GPIO, "Init,Err");
        }
    }

    return res;
}

bool gpio_mux_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t mux = 0;
    Pad_t pad = {.byte = 0};

    if(2 <= argc) {
        res = parse_pad(argv, &pad);
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &mux);
        if(false == res) {
            LOG_ERROR(GPIO, "ParseErr Mux %s", argv[2]);
        }
    }

    if(res) {
        switch(argc) {
        case 2: {
            res = gpio_pin_mux_get(pad.port, pad.pin, &mux);
            if(res) {
                LOG_INFO(GPIO, "Get,%s,Mux:%u", GpioPadToStr(pad), mux);
            }
        } break;
        case 3: {
            LOG_INFO(GPIO, "Set,%s,Mux:%u", GpioPadToStr(pad), mux);
            res = gpio_pin_mux_set(pad.port, pad.pin, mux);
        } break;
        }
    } else {
        LOG_ERROR(GPIO, "Usage: gm gpio_port gpio_pin mux");
    }
    return res;
}
