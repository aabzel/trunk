#include "led_mono_diag.h"

#include "diag_inc.h"
#include "gpio_diag.h"
#include "gpio_mcal.h"
#include "led_diag.h"
#include "led_mono_drv.h"
#include "log.h"
#include "shared_array.h"
#include "table_utils.h"
#include "writer_config.h"

const char* LedMonoConfigToStr(const LedMonoConfig_t* const Config) {
    strcpy(text, "");
    if(Config) {
        snprintf(text, sizeof(text), "%s%5s,", text, GpioPadToStr(Config->pad));
        snprintf(text, sizeof(text), "%s%5s,", text, LedModeToStr(Config->mode));
        snprintf(text, sizeof(text), "%sAct:%u,", text, Config->active);
        snprintf(text, sizeof(text), "%sPer:%4u,", text, Config->period_ms);
        snprintf(text, sizeof(text), "%sGr:%u,", text, Config->group);
        snprintf(text, sizeof(text), "%sDu:%3u,", text, Config->duty);
        snprintf(text, sizeof(text), "%sPha:%4u,", text, Config->phase_ms);
        snprintf(text, sizeof(text), "%s%5s,", text, Config->name);
        snprintf(text, sizeof(text), "%s%5s", text, ColorToStr(Config->color));
    }

    return text;
}

const char* LedMonoNodeToStr(const LedMonoHandle_t* const Node) {
    strcpy(text, "");
    if(Node) {
        snprintf(text, sizeof(text), "%s %5s,", text, GpioPadToStr(Node->pad));
        snprintf(text, sizeof(text), "%s %5s,", text, LedModeToStr(Node->mode));
        snprintf(text, sizeof(text), "%s Per:%4u,", text, Node->period_ms);
        snprintf(text, sizeof(text), "%s Act:%u,", text, Node->active);
        snprintf(text, sizeof(text), "%s Gr:%u,", text, Node->group);
        snprintf(text, sizeof(text), "%s Du:%3u,", text, Node->duty);
        snprintf(text, sizeof(text), "%s Prev:%1u,", text, Node->prev);
        snprintf(text, sizeof(text), "%s Init:%1u,", text, Node->init);
        snprintf(text, sizeof(text), "%s Pha:%4u,", text, Node->phase_ms);
        snprintf(text, sizeof(text), "%s %5s", text, ColorToStr(Node->color));
    }

    return text;
}

bool LedMonoConfigDiag(const LedMonoConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        cli_printf("%s", LedMonoConfigToStr(Config));
    }

    return res;
}

bool LedMonoDiag(LedMonoHandle_t* const Node) {
    bool res = false;
    if(Node) {
        cli_printf("%s", LedMonoNodeToStr(Node));
    }

    return res;
}

bool led_mono_diag(void) {
    bool res = false;
    LOG_INFO(LED, "LedDiag");
    res = true;
    uint32_t i = 0;
    static const table_col_t cols[] = {
        {4, "No"},      {6, "group"},  {7, "mode"}, {8, "periodMs"}, {6, "duty"}, {8, "Freq"},
        {6, "phaseMs"}, {6, "active"}, {6, "val"},  {7, "Pad"},      {7, "name"},
#ifdef HAS_LED_DIAG
        {7, "color"},
#endif
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t cnt = led_mono_get_cnt();
    for(i = 0; i <= cnt; i++) {
        LedMonoHandle_t* Node = LedMonoGetNode(i);
        if(Node) {
            GpioLogicLevel_t logic_level = GPIO_LVL_UNDEF;
            gpio_get_state(Node->pad, &logic_level);
            const LedMonoConfig_t* Config = LedMonoGetConfig(i);

            char log_line[150] = {0};
            strcpy(log_line, "");
            memset(log_line, 0, sizeof(log_line));
            snprintf(log_line, sizeof(log_line), TSEP "%s%2u " TSEP, log_line, i);
            snprintf(log_line, sizeof(log_line), " %s %4u " TSEP, log_line, Node->group);
#ifdef HAS_LED_DIAG
            snprintf(log_line, sizeof(log_line), "%s %5s " TSEP, log_line, LedModeToStr(Node->mode));
#else  /*HAS_LED_DIAG*/
            snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, Node->mode);
#endif /*HAS_LED_DIAG*/
            snprintf(log_line, sizeof(log_line), "%s %6u " TSEP, log_line, Node->period_ms);
            snprintf(log_line, sizeof(log_line), "%s %4.1f " TSEP, log_line, Node->duty);
            snprintf(log_line, sizeof(log_line), "%s %6.3f " TSEP, log_line,
                     math_period_ms_to_freq_hz(Node->period_ms));
            snprintf(log_line, sizeof(log_line), "%s %4u " TSEP, log_line, Node->phase_ms);
            snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, GpioLevelToStr(Node->active));
            snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, GpioLevelToStr(logic_level));
            snprintf(log_line, sizeof(log_line), "%s %5s " TSEP, log_line, GpioPadToStr(Node->pad));
            if(Config) {
                snprintf(log_line, sizeof(log_line), "%s %5s " TSEP, log_line, Config->name);
            }
#ifdef HAS_LED_DIAG
            snprintf(log_line, sizeof(log_line), "%s %5s " TSEP, log_line, ColorToStr(Node->color));
#endif
            cli_printf("%s" CRLF, log_line);
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
