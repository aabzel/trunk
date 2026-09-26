#include "light_sensor_diag.h"

#include "light_sensor_drv.h"
#include "log.h"
#include "table_utils.h"

bool LightSensorConfigDiag(const LightSensorConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        cli_printf(" %5s " TSEP, Config->name);
        cli_printf(CRLF);
    }

    return res;
}

bool LightSensorDiag(LightSensorHandle_t* const Node) {
    bool res = false;
    if(Node) {
        res = true;
        const LightSensorConfig_t* Config = LightSensorGetConfig(Node->num);
        if(Config) {
            cli_printf(" %5s " TSEP, Config->name);
        }
    }

    return res;
}
