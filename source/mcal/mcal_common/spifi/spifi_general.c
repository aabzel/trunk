#include "spifi_mcal.h"

#ifdef HAS_DIAG
#include <stdio.h>
#include <string.h>
#endif

#include "code_generator.h"
#include "std_includes.h"
#include "sys_constants.h"
#ifdef HAS_LOG
#include "log.h"
#endif

COMPONENT_GET_NODE(SpiFi, spifi)
COMPONENT_GET_CONFIG(SpiFi, spifi)

__attribute__((weak)) bool spifi_init_one(uint8_t num) {
    bool res = false;
    return res;
}

__attribute__((weak)) bool spifi_init_custom(void) {
    bool res = false;
    return res;
}

__attribute__((weak)) bool spifi_proc_one(uint8_t num) {
    bool res = false;
    return res;
}

COMPONENT_INIT_PATTERT_CNT(SPIFI, SPIFI, spifi, SPIFI_COUNT)
COMPONENT_PROC_PATTERT_CNT(SPIFI, SPIFI, spifi, SPIFI_COUNT)
