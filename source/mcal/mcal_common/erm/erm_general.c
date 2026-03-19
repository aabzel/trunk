#include "erm_mcal.h"

#include "std_includes.h"
#include "compiler_const.h"
#include "code_generator.h"
#include "log.h"

COMPONENT_GET_NODE(Erm, erm)
COMPONENT_GET_CONFIG(Erm, erm)

bool ErmIsValidConfig(const ErmConfig_t* const Config){
    bool res = false;
    if(Config){
        res = true;
    }
    return res;
}


_WEAK_FUN_ bool erm_init_common(const ErmConfig_t* const Config,
                                ErmHandle_t* const Node) {
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

_WEAK_FUN_ bool erm_init_one(uint8_t num){
    bool res = false;
    return res;
}

_WEAK_FUN_ bool erm_init_custom(void){
    bool res = false;
    return res;
}

_WEAK_FUN_ bool erm_proc_one(uint8_t num){
    bool res = false;
    return res;
}


COMPONENT_INIT_PATTERT(LG_ERM, ERM, erm)
COMPONENT_PROC_PATTERT(LG_ERM, ERM, erm)
