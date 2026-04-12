#include "ext_int_mcal.h"

#include <stdio.h>
#include <string.h>

#include "byte_utils.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"
#include "microcontroller_const.h"
#include "std_includes.h"

COMPONENT_GET_NODE(ExtInt, ext_int)
COMPONENT_GET_CONFIG(ExtInt, ext_int)

_WEAK_FUN_
bool ext_int_init_custom(void) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool ext_int_proc_one(uint8_t num) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool ext_int_init_one(uint8_t num) {
    bool res = false;
    return res;
}

PinIntEdge_t gpio_logic_level_to_edge(const GpioLogicLevel_t logic_level) {
    PinIntEdge_t edge = PIN_INT_EDGE_UNDEF;
    switch(logic_level) {
    case GPIO_LVL_LOW:
        edge = PIN_INT_EDGE_FALLING;
        break;
    case GPIO_LVL_HI:
        edge = PIN_INT_EDGE_RISING;
        break;
    default:
        edge = PIN_INT_EDGE_UNDEF;
        break;
    }
    return edge;
}

COMPONENT_INIT_PATTERT_CNT(EXT_INT, EXT_INT, ext_int, EXT_INT_COUNT)
COMPONENT_PROC_PATTERT_CNT(EXT_INT, EXT_INT, ext_int, EXT_INT_COUNT)
