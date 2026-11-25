#include "multicore_mcal.h"

#include <stdio.h>
#include <string.h>

#include "byte_utils.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "data_types.h"
#include "log.h"
#include "std_includes.h"

COMPONENT_GET_NODE(MultiCore, multicore)
COMPONENT_GET_CONFIG(MultiCore, multicore)

bool multicore_is_my_core(const int8_t core_num, const ControlCores_t Cores) {
    bool res = false;
    switch(core_num) {
    case 0:
        res = Cores.core0;
        break;
    case 1:
        res = Cores.core1;
        break;
    case 2:
        res = Cores.core2;
        break;
    default:
        res = false;
        break;
    }
    return res;
}

bool multicore_is_my_kernel(const ControlCores_t Cores) {
    bool res = false;
    int8_t core_num = multicore_get_core_num();
    res = multicore_is_my_core(core_num, Cores);
    return res;
}

bool multicore_is_my_nucleus(const uint8_t core_num) {
    bool res = false;
    int8_t my_core_num = multicore_get_core_num();
    if(my_core_num == core_num) {
        res = true;
    } else {
        LOG_PARN(MULTICORE, "NotMyCore,Need:%u,My:%u", core_num, my_core_num);
        res = false;
    }
    return res;
}

_WEAK_FUN_ bool multicore_init_one(uint8_t num) {
    bool res = false;
    return res;
}

_WEAK_FUN_ bool multicore_init_custom(void) {
    bool res = false;
    return res;
}

_WEAK_FUN_ bool multicore_proc_one(uint8_t num) {
    bool res = false;
    return res;
}

bool multicore1_init(void) { return multicore_init_one(0); }

bool multicore2_init(void) { return multicore_init_one(1); }

bool multicore3_init(void) { return multicore_init_one(2); }

COMPONENT_INIT_PATTERT(MULTICORE, MULTICORE, multicore)
COMPONENT_PROC_PATTERT(MULTICORE, MULTICORE, multicore)
