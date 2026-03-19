#include "eim_mcal.h"

#include "std_includes.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"


/*
 Function Safety
 Error Injection Module (EIM) for ECC logic and lock step logic check
 */

COMPONENT_GET_NODE(Eim, eim)
COMPONENT_GET_CONFIG(Eim, eim)

bool EimIsValidConfig(const EimConfig_t* const Config ){
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


_WEAK_FUN_ bool eim_init_common(const EimConfig_t* const Config,
                                EimHandle_t* const Node){
    bool res = false;
    if(Config) {
        if(Node) {
            Node->interrupt_on = Config->interrupt_on;
            Node->num = Config->num;
            Node->name = Config->name;
            Node->valid = true;
            res = true;
        }
    }
    return res;
}

_WEAK_FUN_ bool eim_init_one(uint8_t num){
    bool res = true;
    return res;
}

_WEAK_FUN_ bool eim_proc_one(uint8_t num) {
    bool res = true;
    return res;
}

_WEAK_FUN_ bool eim_init_custom(void){
    bool res = true;
    return res;
}

COMPONENT_INIT_PATTERT(LG_EIM, Eim, eim)
COMPONENT_PROC_PATTERT(LG_EIM, Eim, eim)
