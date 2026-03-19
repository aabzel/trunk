#include "lockstep_mcal.h"

#include <stdio.h>
#include <string.h>

#include "code_generator.h"
#include "log.h"
#include "std_includes.h"

COMPONENT_GET_NODE(LockStep, lockstep)
COMPONENT_GET_CONFIG(LockStep, lockstep)

__attribute__((weak)) bool lockstep_init_one(uint8_t num) {
    bool res = false;
    return res;
}

__attribute__((weak)) bool lockstep_init_custom(void) {
    bool res = false;
    return res;
}

__attribute__((weak)) bool lockstep_proc_one(uint8_t num) {
    bool res = false;
    return res;
}

bool LockStepIsValidConfig(const LockStepConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
    }

    if(res) {
        res = Config->valid;
    }

    return res;
}

bool lockstep_init_common(const LockStepConfig_t* const Config, LockStepHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->interrupt_on = Config->interrupt_on;
            Node->name = Config->name;
            Node->num = Config->num;
            Node->valid = true;
            res = true;
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(LOCKSTEP, LOCKSTEP, lockstep)
COMPONENT_PROC_PATTERT(LOCKSTEP, LOCKSTEP, lockstep)
