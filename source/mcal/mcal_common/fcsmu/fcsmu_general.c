#include "fcsmu_mcal.h"

#include <stdio.h>
#include <string.h>

#include "byte_utils.h"
#include "code_generator.h"
#include "data_types.h"
#include "log.h"
#include "std_includes.h"

COMPONENT_GET_NODE(Fcsmu, fcsmu)
COMPONENT_GET_CONFIG(Fcsmu, fcsmu)

__attribute__((weak)) bool fcsmu_init_one(uint8_t num) {
    bool res = false;
    return res;
}

__attribute__((weak)) bool fcsmu_init_custom(void) {
    bool res = false;
    return res;
}

__attribute__((weak)) bool fcsmu_proc_one(uint8_t num) {
    bool res = false;
    return res;
}

bool FcsmuIsValidConfig(const FcsmuConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        if(res) {
            if(Config->valid) {
                res = true;
            } else {
                res = false;
            }
        }
    }
    return res;
}

bool fcsmu1_mcal_init(void) {
    bool res = fcsmu_init_one(1);
    return res;
}

bool fcsmu2_mcal_init(void) {
    bool res = fcsmu_init_one(2);
    return res;
}

bool fcsmu3_mcal_init(void) {
    bool res = fcsmu_init_one(3);
    return res;
}

bool fcsmu1_proc(void) {
    bool res = fcsmu_proc_one(1);
    return res;
}

bool fcsmu2_proc(void) {
    bool res = fcsmu_proc_one(2);
    return res;
}

bool fcsmu3_proc(void) {
    bool res = fcsmu_proc_one(3);
    return res;
}

// COMPONENT_INIT_PATTERT(LG_FCSMU, FCSMU, fcsmu)
// COMPONENT_PROC_PATTERT(LG_FCSMU, FCSMU, fcsmu)
