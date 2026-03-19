#include "ext_int_config.h"

#include "log_config.h"
#include "data_utils.h"

/*constant compile-time known settings*/
const ExtIntConfig_t ExtIntConfig[] = {
    { .num = 0, .name = "-",  .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 1, .name = "--",  .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 2, .name = "--",  .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 3, .name = "IR_Sensor",  .Pad = {.port=PORT_F, .pin=3},      .edge = PIN_INT_EDGE_BOTH, .valid = true, .irq_priority = 2,    .interrupt_on = true,    },
    { .num = 4, .name = "--",  .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 5, .name = "--",  .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 6, .name = "--",  .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 7, .name = "--",  .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 8, .name = "--",  .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 9, .name = "--",  .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 10, .name = "--", .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 11, .name = "--", .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 12, .name = "--", .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 13, .name = "--", .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 14, .name = "--", .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 15, .name = "--", .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
};

ExtIntHandle_t ExtIntInstance[] = {
    {.num = 0, .valid = true,},
    {.num = 1, .valid = true,},
    {.num = 2, .valid = true,},
    {.num = 3, .valid = true,},
    {.num = 4, .valid = true,},
    {.num = 5, .valid = true,},
    {.num = 6, .valid = true,},
    {.num = 7, .valid = true,},
    {.num = 8, .valid = true,},
    {.num = 9, .valid = true,},
    {.num = 10, .valid = true,},
    {.num = 11, .valid = true,},
    {.num = 12, .valid = true,},
    {.num = 13, .valid = true,},
    {.num = 14, .valid = true,},
    {.num = 15, .valid = true,},
};

COMPONENT_GET_CNT(ExtInt, ext_int)



