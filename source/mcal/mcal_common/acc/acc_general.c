#include "acc_mcal.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"

COMPONENT_GET_NODE(Acc, acc)
COMPONENT_GET_CONFIG(Acc, acc)

/*ISO-26262 require verify configuration*/
_WEAK_FUN_
bool AccIsValidConfig(const AccConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
    }
    return res;
}

COMPONENT_INIT_PATTERT(ACC, ACC, acc)
