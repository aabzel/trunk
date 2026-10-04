#include "watchdog_mcal.h"

#include "code_generator.h"
#include "compiler_const.h"

/*ISO-26262 require verify configuration*/
_WEAK_FUN_
bool WatchDogIsValidConfig(const WatchDogConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(1.0f < Config->timeout_s) {
            LOG_ERROR(WATCHDOG, "timeoutS,Err");
            res = false;
        }
        ifn(0 < Config->bitness) {
            LOG_ERROR(WATCHDOG, "bitness,Err");
            res = false;
        }
    }
    return res;
}

_WEAK_FUN_
bool watchdog_timeout_set(uint32_t timeout_ms) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool watchdog_mcal_init(void) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool watchdog_ctrl(bool on_off) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool watchdog_proc(void) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool watchdog_timeout_get(uint32_t* const timeout_ms) {
    bool res = false;
    return res;
}
