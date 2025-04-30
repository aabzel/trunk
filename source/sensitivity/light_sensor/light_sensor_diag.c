
#include "light_sensor_diag.h"

#include "led_diag.h"
#include "light_sensor_drv.h"
#include "table_utils.h"
#include "gpio_diag.h"

bool LedMonoConfigDiag(const LedConfig_t* const  ConfigNode) {
    bool res = false;
    if(ConfigNode) {
        res = true;
        cli_printf(" %5s " TSEP, GpioPad2Str(ConfigNode->pad.byte));
        cli_printf(" %5s " TSEP, LedMode2Str(ConfigNode->mode));
        cli_printf(" %4u " TSEP, ConfigNode->period_ms);
        cli_printf(" %3u " TSEP, ConfigNode->duty);
        cli_printf(" %4u " TSEP, ConfigNode->phase_ms);
        cli_printf(" %5s " TSEP, ConfigNode->name);
        cli_printf(CRLF);
    }

    return res;
}

bool LedMonoDiag(LedHandle_t* const  LedNode) {
    bool res = false;
    if(LedNode) {
        res = true;
        cli_printf(" %5s " TSEP, GpioPad2Str(LedNode->pad.byte));
        cli_printf(" %5s " TSEP, LedMode2Str(LedNode->mode));
        cli_printf(" %4u " TSEP, LedNode->period_ms);
        cli_printf(" %3u " TSEP, LedNode->duty);
        cli_printf(" %4u " TSEP, LedNode->phase_ms);
        const LedConfig_t* ConfigNode = LedGetConfigNode(LedNode->num);
        if(ConfigNode) {
            cli_printf(" %5s " TSEP, ConfigNode->name);
        }
        cli_printf(CRLF);
    }

    return res;
}
