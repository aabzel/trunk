#include "multicore_mcal.h"

#include <stdio.h>
#include <string.h>

#include "byte_utils.h"
#include "code_generator.h"
#include "data_types.h"
#include "log.h"
#include "std_includes.h"

COMPONENT_GET_NODE(MultiCore, multicore)
COMPONENT_GET_CONFIG(MultiCore, multicore)

__attribute__((weak)) bool multicore_init_one(uint8_t num) {
    bool res = false;
    return res;
}

__attribute__((weak)) bool multicore_init_custom(void) {
    bool res = false;
    return res;
}

__attribute__((weak)) bool multicore_proc_one(uint8_t num) {
    bool res = false;
    return res;
}

bool multicore1_init(void) { return multicore_init_one(1); }

bool multicore2_init(void) { return multicore_init_one(2); }

bool multicore3_init(void) { return multicore_init_one(3); }

COMPONENT_INIT_PATTERT(MULTICORE, MULTICORE, multicore)
