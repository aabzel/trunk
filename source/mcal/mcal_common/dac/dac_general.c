#include "dac_mcal.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "byte_utils.h"
#include "code_generator.h"
#include "data_types.h"
#include "log.h"
#include "compiler_const.h"
#include "time_mcal.h"

COMPONENT_GET_NODE(Dac, dac)
COMPONENT_GET_CONFIG(Dac, dac)


_WEAK_FUN_
bool dac_init_custom(void){
    bool res = true;
    return res;
}

_WEAK_FUN_
bool dac_is_init(uint8_t num) {
    bool res = false;
    DacHandle_t* Node = DacGetNode(num);
    if(Node) {
        res = Node->init_done;
    }
    return res;
}

_WEAK_FUN_
bool dac_is_allowed(uint8_t num) {
    bool res = false;
    DacHandle_t* Node = DacGetNode(num);
    if(Node) {
        const DacConfig_t* DacConfNode = DacGetConfig(num);
        if(DacConfNode) {
            res = true;
        }
    }

    return res;
}

uint32_t dac_get_clock(uint8_t num) {
    uint32_t clock = 0;
    return clock;
}

COMPONENT_INIT_PATTERT_CNT(LG_DAC, DAC, dac, DAC_COUNT)
COMPONENT_PROC_PATTERT_CNT(LG_DAC, DAC, dac, DAC_COUNT)
