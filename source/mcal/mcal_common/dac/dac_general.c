#include "dac_mcal.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "byte_utils.h"
#include "code_generator.h"
#include "data_types.h"
#include "log.h"
#include "time_mcal.h"

COMPONENT_GET_NODE(Dac, dac)
COMPONENT_GET_CONFIG(Dac, dac)

bool dac_is_init(uint8_t num) {
    bool res = false;
    DacHandle_t* DacNode = DacGetNode(num);
    if(DacNode) {
        res = DacNode->init_done;
    }
    return res;
}

bool dac_is_allowed(uint8_t num) {
    bool res = false;
    DacHandle_t* DacNode = DacGetNode(num);
    if(DacNode) {
        const DacConfig_t* DacConfNode = DacGetConfig(num);
        if(DacConfNode) {
            res = true;
        }
    }

    return res;
}

COMPONENT_INIT_PATTERT_CNT(LG_DAC, DAC, dac, DAC_COUNT)
COMPONENT_PROC_PATTERT_CNT(LG_DAC, DAC, dac, DAC_COUNT)
