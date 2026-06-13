#include "ext_int_config.h"

#include "log_config.h"
#include "data_utils.h"

static ExtIntEvent_t EventMemA[100]={0};
static ExtIntEvent_t EventMemB[100]={0};
static ExtIntEvent_t IrSensor[100]={0};

/*constant compile-time known settings*/
const ExtIntConfig_t ExtIntConfig[] = {
    { .num = 0,
      .name = "A",
      .Pad = {.port=PORT_E, .pin=0,},
      .edge = PIN_INT_EDGE_BOTH,
      .valid = true,
      .CallBackFalling = NULL,
      .CallBackRising = NULL,
      .irq_priority = 0,
      .EventMem = EventMemA,
      .event_mem_size = ARRAY_SIZE(EventMemA),
    },
    {
        .num = 1,
        .name = "B",
        .Pad = {.port=PORT_E, .pin=1,},
        .edge = PIN_INT_EDGE_BOTH,
        .valid = true,
        .irq_priority = 0,
        .CallBackRising = NULL,
        .CallBackFalling = NULL,
        .EventMem = EventMemB,
        .event_mem_size = ARRAY_SIZE(EventMemB),
    },
    { .num = 6,
      .name = "IrSensor",
      .Pad = {.port=PORT_A, .pin=6,},
      .edge = PIN_INT_EDGE_BOTH,
      .valid = true,
      .irq_priority = 1,
      .CallBackRising = NULL,
      .CallBackFalling = NULL,
      .EventMem = IrSensor,
      .event_mem_size = ARRAY_SIZE(IrSensor),
    },
#if 0
    { .num = 2, .name = "--",  .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,       },
    { .num = 3, .name = "--",  .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,       },
    { .num = 4, .name = "--",  .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,       },
    { .num = 5, .name = "--",  .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,       },
    { .num = 7, .name = "--",  .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,       },
    { .num = 8, .name = "--",  .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,       },
    { .num = 9, .name = "--",  .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,       },
    { .num = 10, .name = "--", .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,       },
    { .num = 11, .name = "--", .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,       },
    { .num = 12, .name = "--", .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,       },
    { .num = 13, .name = "--", .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,       },
    { .num = 14, .name = "--", .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,       },
    { .num = 15, .name = "--", .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_NONE, .valid = true, .irq_priority = 2,       },
#endif
};

ExtIntHandle_t ExtIntInstance[] = {
    {.num = 0, .valid = true,},
    {.num = 1, .valid = true,},
    {.num = 6, .valid = true,},
#if 0
    {.num = 2, .valid = true,},
    {.num = 3, .valid = true,},
    {.num = 4, .valid = true,},
    {.num = 5, .valid = true,},
    {.num = 7, .valid = true,},
    {.num = 8, .valid = true,},
    {.num = 9, .valid = true,},
    {.num = 10, .valid = true,},
    {.num = 11, .valid = true,},
    {.num = 12, .valid = true,},
    {.num = 13, .valid = true,},
    {.num = 14, .valid = true,},
    {.num = 15, .valid = true,},
#endif
};

COMPONENT_GET_CNT(ExtInt, ext_int)



