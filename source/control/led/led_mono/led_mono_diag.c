#include "led_mono_diag.h"

#include "gpio_diag.h"
#include "gpio_mcal.h"
#include "led_diag.h"
#include "led_mono_drv.h"
#include "table_utils.h"
#include "writer_config.h"

bool LedMonoConfigDiag(const LedMonoConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        cli_printf(" %5s " TSEP, GpioPad2Str(Config->pad.byte));
        cli_printf(" %5s " TSEP, LedMode2Str(Config->mode));
        cli_printf(" %4u " TSEP, Config->period_ms);
        cli_printf(" %3u " TSEP, Config->duty);
        cli_printf(" %4u " TSEP, Config->phase_ms);
        cli_printf(" %5s " TSEP, Config->name);
        cli_printf(CRLF);
    }

    return res;
}

bool LedMonoDiag(LedMonoHandle_t* const LedNode) {
    bool res = false;
    if(LedNode) {
        res = true;
        cli_printf(" %5s " TSEP, GpioPad2Str(LedNode->pad.byte));
        cli_printf(" %5s " TSEP, LedMode2Str(LedNode->mode));
        cli_printf(" %4u " TSEP, LedNode->period_ms);
        cli_printf(" %3u " TSEP, LedNode->duty);
        cli_printf(" %4u " TSEP, LedNode->phase_ms);
        const LedMonoConfig_t* Config = LedMonoGetConfig(LedNode->num);
        if(Config) {
            cli_printf(" %5s " TSEP, Config->name);
        }
        cli_printf(CRLF);
    }

    return res;
}

bool led_mono_diag(void) {
    bool res = false;

    res = true;
    uint32_t i = 0;
    static const table_col_t cols[] = {
        {4, "No"},      {7, "mode"},   {8, "periodMs"}, {6, "duty"}, {8, "Freq"},
        {6, "phaseMs"}, {6, "active"}, {6, "val"},      {7, "Pad"},  {7, "name"},
#ifdef HAS_LED_DIAG
        {7, "color"},
#endif
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t cnt = led_mono_get_cnt();
    for(i = 0; i <= cnt; i++) {
        LedMonoHandle_t* Node = LedMonoGetNode(i);
        if(Node) {
            cli_printf(TSEP " %2u " TSEP, i);
#ifdef HAS_LED_DIAG
            cli_printf(" %5s " TSEP, LedMode2Str(Node->mode));
#else  /*HAS_LED_DIAG*/
            cli_printf(" %5u " TSEP, Node->mode);
#endif /*HAS_LED_DIAG*/
            cli_printf(" %6u " TSEP, Node->period_ms);
            cli_printf(" %3.1f " TSEP, Node->duty);
            cli_printf(" %6.3f " TSEP, 1000.0 / ((double)Node->period_ms));
            cli_printf(" %4u " TSEP, Node->phase_ms);
            cli_printf(" %4s " TSEP, GpioLevel2Str(Node->active));

            GpioLogicLevel_t logic_level = GPIO_LVL_UNDEF;
            gpio_get_state(Node->pad.byte, &logic_level);
            cli_printf(" %4s " TSEP, GpioLevel2Str(logic_level));
            cli_printf(" %5s " TSEP, GpioPad2Str(Node->pad.byte));
            const LedMonoConfig_t* Config = LedMonoGetConfig(i);
            if(Config) {
                cli_printf(" %5s " TSEP, Config->name);
            }
#ifdef HAS_LED_DIAG
            cli_printf(" %5s " TSEP, Color2Str(Node->color));
#endif
            cli_printf(CRLF);
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
