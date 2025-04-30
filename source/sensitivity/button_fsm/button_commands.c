#include "button_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "button_drv.h"
#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "gpio_diag.h"
#include "log.h"
#include "table_utils.h"
#include "writer_config.h"

#ifdef HAS_BOARD_INFO_DIAG
#include "board_diag.h"
#endif

#ifndef HAS_BUTTON_COMMANDS
#error "+HAS_BUTTON_COMMANDS"
#endif /*HAS_BUTTON_COMMANDS*/

bool button_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    ButtonHandle_t* ButtonNode = NULL;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(BUTTON, "ParseErr Num %s", argv[0]);
        } else {
            ButtonNode = ButtonGetNode(num);
            if(ButtonNode) {
                LOG_INFO(BUTTON, "ButtonPtrOk!");
                res = true;
            } else {
                LOG_ERROR(BUTTON, "NoButtonPtr%u");
                res = false;
            }
        }
    }

    if(false == res) {
        LOG_ERROR(BUTTON, "Usage: bs num on_off");
    }
    return res;
}

bool button_get_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(BUTTON, "ParseErr Num %s", argv[0]);
        }
    }

    if(res) {
        ButtonState_t state = button_get(num);
        LOG_INFO(BUTTON, "%u %s", num, ButtonState2Str(state));
    } else {
        LOG_ERROR(BUTTON, "Usage: bs num on_off");
    }
    return res;
}
// TODO move to diag
bool button_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "Num"},       {7, "Pad"},          {10, "short_pres_cnt"}, {10, "long_pres_cnt"}, {6, "Act"},
        {11, "State"},    {12, "handlerLong"}, {12, "handlerShort"},   {8, "name"},
#ifdef HAS_BOARD_INFO_DIAG
        {8, "connector"}, {8, "Silk"},
#endif
    };

    uint8_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint32_t cnt = button_get_cnt();
    for(num = 0; num <= cnt; num++) {
        const ButtonConfig_t* ConfNode = ButtonGetConfig(num);
        ButtonHandle_t* Node = ButtonGetNode(num);
        if(Node && ConfNode) {
            cli_printf(TSEP);
            cli_printf(" %02u  " TSEP, num);
            cli_printf(" %5s " TSEP, GpioPad2Str(Node->pad.byte));
            cli_printf(" %8u " TSEP, Node->short_pres_cnt);
            cli_printf(" %8u " TSEP, Node->long_pres_cnt);
            cli_printf(" %04s " TSEP, GpioLevel2Str(Node->active));
            cli_printf(" %9s " TSEP, ButtonState2Str(Node->state));
            cli_printf(" 0x%08x " TSEP, (uint32_t)Node->press_long_handler);
            cli_printf(" 0x%08x " TSEP, (uint32_t)Node->press_short_handler);
            cli_printf(" %6s " TSEP, ConfNode->name);
#ifdef HAS_BOARD_INFO_DIAG
            cli_printf(" %6s " TSEP, Pad2ConnectorPin(Node->pad));
            cli_printf(" %6s " TSEP, Pad2SilkName(Node->pad));
#endif

            cli_printf(CRLF);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool button_press_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    ButtonPressType_t press_type = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(BUTTON, "ParseErr Num %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &press_type);
        if(false == res) {
            LOG_ERROR(BUTTON, "ParseErr PressType %s", argv[1]);
        }
    }

    if(res) {
        res = button_press(num, press_type);
    }
    return res;
}
