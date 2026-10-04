#include "ext_int_config.h"

#include "log_config.h"
#include "data_utils.h"

/*constant compile-time known settings*/
const ExtIntConfig_t ExtIntConfig[] = {
    { .num = 0,
      .name = "PA0",
      .Pad={.port=PORT_A, .pin=0},
      .edge=PIN_INT_EDGE_RISING,
      .valid=true,
      .irq_priority=2,
      .interrupt_on =true,
    },
};

ExtIntHandle_t ExtIntInstance[] = {
    {.num=0, .valid=true,},
};

COMPONENT_GET_CNT(ExtInt, ext_int)

