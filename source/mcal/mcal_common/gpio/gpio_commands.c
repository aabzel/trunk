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
#include "writer_config.h"
#ifdef HAS_GPIO_TEST
#include "test_gpio.h"
#endif

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
            dir = gpio_dir_get(pad);
            LOG_INFO(GPIO, "Cur Pad:%s: Dir %s", GpioPadToStr(pad), GpioDirToStr(dir));
        } break;
        case 3: {
            LOG_WARNING(GPIO, "TrySetDirOk %s:%s", GpioPadToStr(pad), GpioDirToStr(dir));
            res = gpio_dir_set(pad, (GpioDir_t)dir);
            if(res) {
                LOG_INFO(GPIO, "SetDirOk %s:%s", GpioPadToStr(pad), GpioDirToStr(dir));
            } else {
                LOG_ERROR(GPIO, "SetDirErr %s:%s", GpioPadToStr(pad), GpioDirToStr(dir));
            }

        } break;
        default:
            break;
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
        log_info_res(GPIO, res, "Pad");
    }

    if(res) {
        res = gpio_get_state(pad, &logic_level);
        if(false == res) {
            LOG_ERROR(GPIO, "ParseErr lgcLvl");
        } else {
            LOG_INFO(GPIO, "%s:%u" CRLF, GpioPadToStr(pad), logic_level);
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
        log_info_res(GPIO, res, "Pad");
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
            GpioPullMode_t pull_mode = gpio_pull_get(pad);
            LOG_INFO(GPIO, "PullGet Pad %s, Pull %u=%s " LOG_OK, GpioPadToStr(pad), pull_mode,
                     GpioPullToStr(pull_mode));
        } break;
        case 3: {
            res = gpio_pull_set(pad, (GpioPullMode_t)pull_code);
            if(res) {
                LOG_INFO(GPIO, "PullSet Pad %s Pull%s Ok" LOG_OK, GpioPadToStr(pad), GpioPullToStr(pull_code));
            } else {
                LOG_ERROR(GPIO, "PullSet Pad %s Pull%s Err" LOG_ER, GpioPadToStr(pad), GpioPullToStr(pull_code));
            }

        } break;
        default:
            break;
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
        log_info_res(GPIO, res, "Pad");
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
        LOG_INFO(GPIO, "Set %s:%u" CRLF, GpioPadToStr(pad), logic_level);
        res = gpio_logic_level_set(pad, logic_level);
        if(false == res) {
            LOG_ERROR(GPIO, "Unable to set gpio state");
        } else {
            LOG_INFO(GPIO, "Set gpio state %s %u", GpioPadToStr(pad), logic_level);
        }
    }
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
        log_info_res(GPIO, res, "Pad");
    }

    if(res) {
        res = gpio_toggle(pad);
        if(false == res) {
            LOG_ERROR(GPIO, "TogglePadErr %s", GpioPadToStr(pad));
        } else {
            LOG_INFO(GPIO, "TogglePadOk %s", GpioPadToStr(pad));
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
        log_info_res(GPIO, res, "Pad");
    }

    if(res) {
        res = false;
#ifdef HAS_GPIO_TEST
        LOG_INFO(GPIO, "RunPadTest %s", GpioPadToStr(pad));
        res = test_gpio_pin(pad);
#endif
        if(res) {
            LOG_INFO(GPIO, "PadTestOk %s", GpioPadToStr(pad));
        } else {
            LOG_ERROR(GPIO, "PadTestErr %s", GpioPadToStr(pad));
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
        log_info_res(GPIO, res, "Init");
    }

    return res;
}

bool gpio_mux_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t mux = 0;
    Pad_t pad = {.byte = 0};

    if(2 <= argc) {
        res = parse_pad(argv, &pad);
        log_info_res(GPIO, res, "Pad");
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &mux);
        log_info_res(GPIO, res, "GetMux");
    }

    if(res) {
        switch(argc) {
        case 2: {
            res = gpio_pin_mux_get(pad, &mux);
            if(res) {
                LOG_INFO(GPIO, "Get,%s,Mux:%u", GpioPadToStr(pad), mux);
            }
        } break;
        case 3: {
            LOG_INFO(GPIO, "TrySet,%s,Mux:%u", GpioPadToStr(pad), mux);
            res = gpio_pad_mux_set(pad, mux);
        } break;
        default:
            break;
        }
    } else {
        LOG_ERROR(GPIO, "Usage: gm gpio_port gpio_pin mux");
    }
    return res;
}

bool gpio_mode_command(int32_t argc, char* argv[]) {
    bool res = false;
    Pad_t Pad = {.byte = 0};
    uint8_t mode = 0;

    if(2 <= argc) {
        res = parse_pad(argv, &Pad);
        log_info_res(GPIO, res, "Pad");
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &mode);
        log_info_res(GPIO, res, "GetMux");
    }

    if(res) {
        switch(argc) {
        case 2: {
            mode = gpio_mode_get(Pad);
            LOG_INFO(GPIO, "Get,%s,Mode:%s", GpioPadToStr(Pad), GpioModeToStr(mode));
        } break;
        case 3: {
            LOG_INFO(GPIO, "Set,%s,Mode:%s", GpioPadToStr(Pad), GpioModeToStr(mode));
            res = gpio_mode_set(Pad, (GpioApiMode_t)mode);
            log_info_res(GPIO, res, "ModeSet");
        } break;
        default:
            break;
        }
    } else {
        LOG_ERROR(GPIO, "Usage: gmd port pin mode");
    }
    return res;
}

bool gpio_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t port = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &port);
        log_info_res(GPIO, res, "Port");
    }

    if(res) {
        res = gpio_raw_reg_diag((GpioPort_t)port);
        log_info_res(GPIO, res, "Regs");
    } else {
        LOG_ERROR(GPIO, "Usage: gr port");
    }
    return res;
}
