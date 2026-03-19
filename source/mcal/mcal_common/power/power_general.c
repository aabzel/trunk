#include "power_mcal.h"

#include <stdbool.h>
#include <stdint.h>

//#include "c_defines_generated.h"

#include "data_utils.h"
#include "log.h"
#include "compiler_const.h"
#include "code_generator.h"


COMPONENT_GET_NODE(Power, power)
COMPONENT_GET_CONFIG(Power, power)

bool power_init_common(const PowerConfig_t* const Config, PowerHandle_t* const Node){
    bool res = false;
    if(Config) {
        if(Node) {
            res = true;
        }
    }
    return res;
}

_WEAK_FUN_ bool power_init_custom(void) {
    return false;
}

bool PowerIsValidConfig(const PowerConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        if(res) {
            if(0<Config->mode) {
                res = true;
            }else{
                res = false;
            }
        }
    }
    return res;
}


COMPONENT_INIT_PATTERT(POWER, POWER, power)
COMPONENT_PROC_PATTERT(POWER, POWER, power)
