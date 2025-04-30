#include "relay_diag.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#include "gpio_diag.h"
#include "log.h"
#include "relay.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

const char* RelayModeToStr(RelayMode_t mode) {
    const char* name = "?";
    switch((uint8_t)mode) {
    case RELAY_MODE_OFF: {
        name = "Off";
    } break;

    case RELAY_MODE_ON: {
        name = "On";
    } break;

    case RELAY_MODE_BLINK: {
        name = "Blink";
    } break;

    case RELAY_MODE_PWM: {
        name = "Pwm";
    } break;

    case RELAY_MODE_PULSE_TRAIN: {
        name = "Train";
    } break;
    }
    return name;
}

bool relay_diag(char* key_word1, char* key_word2) {
    bool res = false;
    replace_char(key_word1, '_', ' ');
    replace_char(key_word2, '_', ' ');
    uint32_t cnt = relay_get_cnt();
    LOG_INFO(RELAY, "Cnt:%u", cnt);
    static const table_col_t cols[] = {{14, "name"}, {5, "Num"}, {6, "eff"},    {7, "mode"},      {6, "Pad"},
                                       {5, "init"},  {6, "err"}, {8, "restMs"}, {8, "DurationMs"}};

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    char line_str[200] = {0};
    bool on_off = false;
    uint8_t i = 0;
    for(i = 0; i <= cnt; i++) {
        const RelayConfig_t* Config = RelayGetConfig(i);
        if(Config) {
            RelayHandle_t* Node = RelayGetNode(i);
            if(Node) {
                on_off = relay_state_get(Node->num);
                strcpy(line_str, TSEP);
                sprintf(line_str, "%s %12s " TSEP, line_str, Config->name);
                sprintf(line_str, "%s %3u " TSEP, line_str, Node->num);
                sprintf(line_str, "%s %4s " TSEP, line_str, OnOffToStr(on_off));
                sprintf(line_str, "%s %5s " TSEP, line_str, RelayModeToStr(Node->mode));
                sprintf(line_str, "%s %4s " TSEP, line_str, GpioPadToStr(Node->pad_set));
                sprintf(line_str, "%s %3u " TSEP, line_str, Node->init);
                sprintf(line_str, "%s %4u " TSEP, line_str, Node->err_cnt);
                sprintf(line_str, "%s %6d " TSEP, line_str, Node->rest_duration_ms);
                sprintf(line_str, "%s %6d " TSEP, line_str, Node->duration_ms);
                res = is_contain(line_str, key_word1, key_word2);
                if(res) {
                    cli_printf("%s" CRLF, line_str);
                }
            }
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

const char* RelayConfigToStr(const RelayConfig_t* const Config) {
    static char name[150] = "";
    snprintf(name, sizeof(name), "N:%u,%s,Mode:%s,Set:%s,Get:%s,Active:%s,Duty:%u", Config->num, Config->name,
             RelayModeToStr(Config->mode), GpioPadToStr(Config->pad_set), GpioPadToStr(Config->pad_get),
             GpioLevel2Str(Config->active), Config->duty);
    return name;
}
