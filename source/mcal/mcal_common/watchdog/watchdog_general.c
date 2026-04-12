#include "watchdog_mcal.h"

#include "compiler_const.h"

_WEAK_FUN_
bool watchdog_timeout_set( uint32_t timeout_ms) {
    bool res = false;
    return res;
}


_WEAK_FUN_
bool watchdog_mcal_init(void){
    bool res = false;
    return res;
}

_WEAK_FUN_
bool watchdog_ctrl(bool on_off) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool watchdog_proc(void){
    bool res = false;
    return res;
}

_WEAK_FUN_
bool watchdog_timeout_get( uint32_t* const timeout_ms){
    bool res = false;
    return res;
}

