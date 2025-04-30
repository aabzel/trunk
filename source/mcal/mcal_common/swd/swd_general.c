#include "swd_mcal.h"

#include <stdbool.h>
#include <stdint.h>

#include "code_generator.h"
#include "data_utils.h"
#include "log.h"

COMPONENT_GET_CONFIG(Swd, swd)
COMPONENT_GET_NODE(Swd, swd)

__attribute__((weak)) bool swd_init_custom(void) {
    bool res = true;
    return res;
}

__attribute__((weak)) bool swd_proc_one(uint8_t num) {
    bool res = false;
    return res;
}
