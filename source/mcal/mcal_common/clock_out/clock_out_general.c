#include "clock_out_mcal.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"

COMPONENT_GET_NODE(ClockOut, clock_out)
COMPONENT_GET_CONFIG(ClockOut, clock_out)

_WEAK_FUN_
bool clock_out_get(ClockOutChannel_t ch, ClockOutBus_t clock_bus, uint32_t* freq_hz) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool clock_out_set(ClockOutChannel_t ch, ClockOutBus_t clock_bus, uint32_t divider) {
    bool res = false;
    return res;
}

_WEAK_FUN_ bool clock_out_init_custom(void) { return false; }

_WEAK_FUN_ bool clock_out_init_one(uint8_t num) { return false; }

COMPONENT_INIT_PATTERT(CLOCK_OUT, CLOCK_OUT, clock_out)

// COMPONENT_PROC_PATTERT(CLOCK_OUT, CLOCK_OUT, clock_out)
