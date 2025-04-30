#include "gpio_commands.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "base_cmd.h"
#include "board_layout.h"
#include "convert.h"
#include "ctype.h"
#include "data_utils.h"
#include "gpio_common.h"
#include "gpio_diag.h"
#include "gpio_drv.h"
#include "io_utils.h"
#include "log.h"
#include "ostream.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

static bool gpio_diag(char* key_word1, char* key_word2) {
    bool res = false;
    replace_char(key_word1, '_', ' ');
    replace_char(key_word2, '_', ' ');
    static const table_col_t cols[] = {{5, "No"},
    		{5, "dio"},
			{5, "pin"},
			{5, "dir"},
            {7, "level"},
		    {5, "irq"},
		    {6, "edge"},
		    {6, "pull"},
		    {13, "type"},
		    {10, "AltFun"},
		    {12, "name"}};
    uint16_t num = 0;
    table_header(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    uint8_t logic_level = 0xFF;

    uint8_t i = 0;
    char line_str[300] = "";
    char sufix_str[50]= "";
    DioDir_t gpio_dir;
    for(i = 0; i < pin_get_cnt(); i++) {
    	logic_level = 0;
        res = gpio_get_state(PinTable[i].dio, &logic_level);
        if(true == res) {
            memset(line_str, 0x0, sizeof(line_str));
            strcpy(line_str, TSEP);
            //https://stackoverflow.com/questions/69519821/error-passing-argument-1-to-restrict-qualified-parameter-aliases-with-argument
            snprintf(sufix_str, sizeof(sufix_str), "%4d " TSEP, PinTable[i].dio);
            strncat(line_str, sufix_str, sizeof(line_str));

            snprintf(sufix_str, sizeof(sufix_str), "%4u " TSEP, PinTable[i].mcu_pin);
            strncat(line_str, sufix_str,sizeof(line_str));

            gpio_dir = gpio_get_dir(PinTable[i].dio);
            snprintf(sufix_str, sizeof(sufix_str), "%3s  " TSEP, gpio_dir2str(gpio_dir));
            strncat(line_str, sufix_str,sizeof(line_str));

            snprintf(sufix_str, sizeof(sufix_str), " %2s    " TSEP, (1 == logic_level) ? "H" : "L");
            strncat(line_str, sufix_str,sizeof(line_str));

            snprintf(sufix_str, sizeof(sufix_str), "  %s  " TSEP, (1 == is_edge_irq_en(i)) ? "Y" : "N");
            strncat(line_str, sufix_str,sizeof(line_str));

            snprintf(sufix_str, sizeof(sufix_str), "%4s " TSEP, get_gpio_edge(PinTable[i].dio));
            strncat(line_str, sufix_str,sizeof(line_str));

            snprintf(sufix_str, sizeof(sufix_str), "%4s " TSEP, get_gpio_pull_mode(PinTable[i].dio));
            strncat(line_str, sufix_str,sizeof(line_str));

            snprintf(sufix_str, sizeof(sufix_str), "%11s " TSEP, get_gpio_type(PinTable[i].dio));
            strncat(line_str, sufix_str,sizeof(line_str));

            snprintf(sufix_str, sizeof(sufix_str), "%8s " TSEP, get_gpio_alter_fun(PinTable[i].dio));
            strncat(line_str, sufix_str,sizeof(line_str));

            snprintf(sufix_str, sizeof(sufix_str), "%10s " TSEP, PinTable[i].name);
            strncat(line_str, sufix_str,sizeof(line_str));

            if(is_contain(line_str, key_word1, key_word2)) {
                io_printf(TSEP " %3u ", num);
                io_printf("%s\r\n", line_str);
                num++;
            }
        }
    }

    table_row_bottom(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));

    return res;
}
/*
gg D 1
*/
bool gpio_get_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(1 == argc) {
        res = true;
        uint8_t logic_level = 0xFF;
        uint8_t dio_num = 0;

        if(true == res) {
            res = try_str2uint8(argv[0], &dio_num);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to extract dio_num %s", argv[0]);
            }
        }

        if(true == res) {
            res = gpio_get_state(dio_num, &logic_level);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to get gpio state");
            } else {
                io_printf("%u" CRLF, logic_level);
            }
        }
    } else {
        LOG_ERROR(SYS, "Usage: gg dio");
        LOG_INFO(SYS, "dio 0....31 ");
    }
    return res;
}

bool gpio_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(2 == argc) {
        res = true;
        uint8_t logic_level = 0xFF;
        uint8_t dio_num = 0;

        if(true == res) {
            res = try_str2uint8(argv[0], &dio_num);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to extract dio_num %s", argv[0]);
            }
        }

        if(true == res) {
            res = try_str2uint8(argv[1], &logic_level);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to extract logic_level %s", argv[1]);
            }
        }

        if(true == res) {
            res = gpio_set_state(dio_num, logic_level);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to set gpio state");
            } else {
                io_printf("%u" CRLF, logic_level);
            }
        }
    } else {
        LOG_ERROR(SYS, "Usage: gs dio_num gpio_pin logic_level");
        LOG_INFO(SYS, "gpio_pin 0....30 ");
        LOG_INFO(SYS, "logic_level 0..1 ");
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
        LOG_ERROR(SYS, "Usage: gl keyWord");
    }
    if(true == res) {
        res = gpio_diag(keyWord1, keyWord2);
    }
    return res;
}

bool gpio_toggle_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(1 == argc) {
        res = true;
        uint8_t dio_num = 0;

        if(true == res) {
            res = try_str2uint8(argv[0], &dio_num);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to extract dio_num %s", argv[0]);
            }
        }

        if(true == res) {
            res = gpio_toggle(dio_num);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to toggle gpio %u %s", dio_num, gpio_get_name(dio_num));
            } else {
                LOG_INFO(SYS, "pin %u %s toggle OK" CRLF, dio_num, gpio_get_name(dio_num));
            }
        }
    } else {
        LOG_ERROR(SYS, "Usage: gt dio_num gpio_pin");
        LOG_INFO(SYS, "gpio_pin 0....15 ");
    }
    return res;
}

bool gpio_set_dir_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t dio_num = 0;
    DioDir_t dio_dir = GPIO_DIR_UNDEF;
    if(1 <= argc) {

        res = try_str2uint8(argv[0], &dio_num);
        if(false == res) {
            LOG_ERROR(SYS, "Unable to extract dio_num %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1],(uint8_t*) &dio_dir);
        if(false == res) {
            LOG_ERROR(SYS, "Unable to extract dio_dir %s", argv[1]);
        } else {
            io_printf("Des dir %s" CRLF, gpio_dir2str(dio_dir));
        }
    }

    if(2 < argc) {
        LOG_ERROR(SYS, "Usage: gsd dio_num dir");
    }

    if(res) {
        res = gpio_set_dir(dio_num, dio_dir);
        if(false == res) {
            LOG_ERROR(SYS, "error %u %s", dio_num, gpio_get_name(dio_num));
        } else {
            LOG_INFO(SYS, "pin %u dir %u %s", dio_num, dio_dir, gpio_get_name(dio_num));
        }
    }
    return res;
}

bool gpio_get_dir_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(1 == argc) {
        res = true;
        uint8_t dio_num = 0;
        DioDir_t dio_dir = GPIO_DIR_UNDEF;
        if(true == res) {
            res = try_str2uint8(argv[0], &dio_num);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to extract dio_num %s", argv[0]);
            }
        }

        if(true == res) {
            dio_dir = gpio_get_dir(dio_num);
            if(false == res) {
                LOG_ERROR(SYS, "error %u %s", dio_num, gpio_get_name(dio_num));
            } else {
                LOG_INFO(SYS, "DIO_%u (%s) dir [%u] %s " CRLF, dio_num, gpio_get_name(dio_num), dio_dir,
                         gpio_dir2str(dio_dir));
            }
        }
    } else {
        LOG_ERROR(SYS, "Usage: gd dio_num");
    }
    return res;
}

bool gpio_set_pull_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t dio = 0;
    uint8_t pull_mode = 0;
    if(2 == argc) {
        res = true;

        res = try_str2uint8(argv[0], &dio);
        if(false == res) {
            LOG_ERROR(SYS, "Unable to extract dio %s", argv[0]);
        }

        if(true == res) {
            res = try_str2uint8(argv[1], &pull_mode);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to extract pull_mode %s", argv[1]);
            }
        }

        if(true == res) {
            res = gpio_set_pull_mode(dio, (PullMode_t)pull_mode);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to set pull");
            } else {
                LOG_INFO(SYS, "OK");
            }
        }
    } else {
        LOG_ERROR(SYS, "Usage: gp dio mode");
        LOG_INFO(SYS, "dio 0....15 ");
        LOG_INFO(SYS, "mode [1-Down 2-Up 3-Air]");
    }
    return res;
}

bool gpio_set_in_mode_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t dio = 0;
    bool is_in_mode = 0;
    if(2 == argc) {
        res = true;

        if(true == res) {
            res = try_str2uint8(argv[0], &dio);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to extract dio %s", argv[0]);
            }
        }

        if(true == res) {
            res = try_str2bool(argv[1], &is_in_mode);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to extract is_in_mode %s", argv[1]);
            }
        }

        if(true == res) {
            res = gpio_set_in_mode(dio, is_in_mode);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to set in mode");
            } else {
                LOG_INFO(SYS, "OK");
            }
        }
    } else {
        LOG_ERROR(SYS, "Usage: gis dio is_in_mode");
        LOG_INFO(SYS, "dio 0....15");
        LOG_INFO(SYS, "state [0-off 1-on]");
    }
    return res;
}
