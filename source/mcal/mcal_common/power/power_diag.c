#include "power_diag.h"

#include <stdio.h>
#include <string.h>

#include "log.h"
#include "power_custom_diag.h"
#include "power_mcal.h"
#include "table_utils.h"
#include "writer_config.h"


const char* PowerModeToStr(PowerMode_t power_mode) {
    const char* name = "?";
    switch((uint8_t)power_mode) {
    case POWER_MODE_ACTIVE:        name = "Active";        break;
    case POWER_MODE_SLEEP:        name = "Sleep";        break;
    case POWER_MODE_DEEPSLEEP:        name = "DeepSleep";        break;
    case POWER_MODE_STANDBY:        name = "StandBy";        break;
    case POWER_MODE_POWER_DOWN:        name = "PowerDown";        break;
    default:        name = "?";        break;
    }
    return name;
}


static bool PowerDiagNode(const PowerHandle_t* const Node) {
    bool res = false;
    if(Node) {
        res = true;
        char log_line[150];
        static const table_col_t cols[] = {
            {3, "Num"},
        };
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s %1u " TSEP, log_line, Node->num);
        cli_printf("%s" CRLF, log_line);

        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    return res;
}

bool power_diag_one(uint8_t num) {
    bool res = false;
    const PowerInfo_t* Info = PowerGetInfo(num);
    if(Info) {
    //    PowerStaticInfoDiag(Info);
        const PowerConfig_t* Config = PowerGetConfig(num);
        if(Config) {
            PowerDiagConfig(Config);
            PowerHandle_t* Node = PowerGetNode(num);
            if(Node) {
                res = PowerDiagNode(Node);
            }
        }
    }

    return res;
}

const char* PowerConfigToStr(const PowerConfig_t* const Config){
	    static char name[150] = "";
	    if(Config) {
	        strcpy(name, "");
	        snprintf(name, sizeof(name), "%s%s,", name, PowerModeToStr(Config->mode));
	        snprintf(name, sizeof(name), "%s%s", name, Config->name);
	    }
	    return name;
}


bool power_diag(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {3, "Num"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint16_t power_cnt = power_get_cnt();
    uint8_t i = 0;
    for(i = 0; i < power_cnt; i++) {
        PowerHandle_t* Node = PowerGetNode(i);
        if(Node) {
            char log_line[150];
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %1u " TSEP, log_line, Node->num);
            cli_printf("%s" CRLF, log_line);
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
