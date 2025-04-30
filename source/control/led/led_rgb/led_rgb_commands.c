#include "led_rgb_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "convert.h"
#include "data_utils.h"
#include "led_rgb_config.h"
#include "led_rgb_drv.h"
#include "log_utils.h"
#ifdef HAS_LED_DIAG
#include "led_diag.h"
#include "led_rgb_diag.h"
#endif

#include "log.h"

#include "table_utils.h"
#include "writer_config.h"

bool led_rgb_get_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
        uint32_t i = 0;
        static const table_col_t cols[] = {{4, "No"},    {7, "mode"},  {6, "period"}, {5, "duty"},
                                           {6, "phase"}, {7, "color"}, {7, "name"}};
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        uint32_t cnt = led_rgb_get_cnt();
        for(i = 1; i <= cnt; i++) {
            LedRgbHandle_t* LedRgbNode = LedRgbGetNode(i);
            if(LedRgbNode) {
                cli_printf(TSEP " %2u " TSEP, i);
                cli_printf(" %5s " TSEP, LedMode2Str(LedRgbNode->mode));
                cli_printf(" %4u " TSEP, LedRgbNode->period_ms);
                cli_printf(" %3u " TSEP, LedRgbNode->duty);
                cli_printf(" %4u " TSEP, LedRgbNode->phase_ms);
                Color_t color = led_rgb_get_color_ll(LedRgbNode);
                cli_printf(" %5s " TSEP, Color2Str(color));
                const LedRgbConfig_t* LedRgbConfNode = LedRgbGetConfig(i);
                if(LedRgbConfNode) {
                    cli_printf(" %5s " TSEP, LedRgbConfNode->name);
                }
                cli_printf(CRLF);
            }
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    } else {
        LOG_ERROR(LED_RGB, "Usage: lrg");
    }
    return res;
}

bool led_rgb_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t led_rgb_num = 0;
    uint8_t in_duty = 0;
    LedRgbHandle_t* LedRgbNode = NULL;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &led_rgb_num);
        if(false == res) {
            LOG_ERROR(LED_RGB, "ParseErr Num %s", argv[0]);
        } else {
            LedRgbNode = LedRgbGetNode(led_rgb_num);
            if(LedRgbNode) {
                LOG_INFO(LED_RGB, "LedPtrOk!");
                res = true;
            } else {
                LOG_ERROR(LED_RGB, "NoLedPtr%u");
                res = false;
            }
        }
    }

    if(2 <= argc) {
        if(LedRgbNode) {
            res = try_str2uint32(argv[1], &LedRgbNode->period_ms);
            if(false == res) {
                LOG_ERROR(LED_RGB, "ParseErr period %s", argv[1]);
            }
        }
    }

    if(3 <= argc) {
        if(LedRgbNode) {
            res = try_str2uint8(argv[2], &in_duty);
            if(false == res) {
                LOG_ERROR(LED_RGB, "ParseErr duty %s", argv[2]);
            } else {
                if(in_duty <= 100) {
                    LedRgbNode->duty = in_duty;
                }
            }
        }
    }

    if(4 <= argc) {
        if(LedRgbNode) {
            res = try_str2uint32(argv[3], &LedRgbNode->phase_ms);
            if(false == res) {
                LOG_ERROR(LED_RGB, "ParseErr phase %s", argv[3]);
            }
        }
    }

    if(false == res) {
        LOG_ERROR(LED_RGB, "Usage: lrs num period_ms duty phase_ms");
        LOG_INFO(LED_RGB, "period");
        LOG_INFO(LED_RGB, "duty 0....100");
        LOG_INFO(LED_RGB, "phase");
    }
    return res;
}

bool led_rgb_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t led_rgb_num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &led_rgb_num);
        if(false == res) {
            LOG_ERROR(LED_RGB, "ParseErr Num %s", argv[0]);
        } else {
        }
    }

    if(res) {
        res = led_rgb_init_one(led_rgb_num);
    }
    return res;
}

bool led_rgb_color_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t led_rgb_num = 0;
    Color_t color = COLOR_UNDEF;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &led_rgb_num);
        if(false == res) {
            LOG_ERROR(LED_RGB, "ParseErr Num %s", argv[0]);
        } else {
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &color);
        if(false == res) {
            LOG_ERROR(LED_RGB, "ParseErr color %s", argv[1]);
        } else {
        }
    }

    if(res && (1 == argc)) {
        Color_t color = led_rgb_get_color(led_rgb_num);
#ifdef HAS_LED_DIAG
        LOG_INFO(LED_RGB, "%u GetColor %u=[%5s] " TSEP, led_rgb_num, color, Color2Str(color));
#endif
    } else {
        if(res && (2 == argc)) {
#ifdef HAS_LED_DIAG
            LOG_INFO(LED_RGB, "%u SetColor %u=[%5s] " TSEP, led_rgb_num, color, Color2Str(color));
#endif
            res = led_rgb_set_color(led_rgb_num, color);
        } else {
            LOG_ERROR(LED_RGB, "Usage: lrgc num");
        }
    }

    return res;
}
