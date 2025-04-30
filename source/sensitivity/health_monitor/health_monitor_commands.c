#include "health_monitor_commands.h"

#include "health_monitor.h"

#include "convert.h"
#include "log.h"
#include "log_utils.h"
#include "table_utils.h"

bool health_monitor_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = health_monitor_reset();
    return res;
}

bool health_monitor_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }
    if(1 <= argc) {
        res = try_str2bool(argv[0], &HealthMon.power);
        if(false == res) {
            LOG_ERROR(SYS, "Unable to extract power %s", argv[0]);
        }
    }

    cli_printf("DiagVoltage %u" CRLF, HealthMon.power);
    cli_printf("InitError %u" CRLF, HealthMon.init_error);
    cli_printf("CrcErrorCode %u" CRLF, HealthMon.crc_error_cnt);
    cli_printf("ErrorCnt %u" CRLF, HealthMon.error_cnt);
    cli_printf("Messege: [%s]" CRLF, HealthMon.error_messege);
    return res;
}
