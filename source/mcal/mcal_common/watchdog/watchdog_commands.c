#include "watchdog_commands.h"

#include "convert.h"
#include "log.h"
#include "log_utils.h"
#include "watchdog_mcal.h"

bool watchdog_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        LOG_INFO(WATCHDOG, "%s", WatchDogConfigToStr(&WatchDogConfig));
        uint32_t timeout_ms = 0;
        res = watchdog_timeout_get(&timeout_ms);
        LOG_INFO(WATCHDOG, "Real:%u ms", timeout_ms);
        res = true;
    } else {
        LOG_ERROR(WATCHDOG, "Usage: wdd");
    }
    return res;
}

bool watchdog_ctrl_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(1 == argc) {
        res = try_str2bool(argv[0], &WatchDogInstance.on);
        if(false == res) {
            LOG_ERROR(WATCHDOG, "ParseErr OnOff %s", argv[0]);
        }
    }

    if(res) {
        res = watchdog_ctrl(WatchDogInstance.on);
    } else {
        LOG_ERROR(WATCHDOG, "Usage: wdc OnOff");
    }

    return res;
}

bool watchdog_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t timeout_ms = 0;
    if(1 == argc) {
        res = try_str2uint32(argv[0], &timeout_ms);
        if(false == res) {
            LOG_ERROR(WATCHDOG, "ParseErr period_ms %s", argv[0]);
        }
    }

    if(res) {
        res = watchdog_timeout_set(timeout_ms);
        if(res) {
            LOG_INFO(WATCHDOG, "SetOk");
        } else {
            LOG_ERROR(WATCHDOG, "SetErr");
        }
    } else {
        LOG_ERROR(WATCHDOG, "Usage: wds timeoutMs");
    }
    return res;
}
