#include "ext_int_config.h"

#include "log_config.h"
#include "data_utils.h"

#ifdef HAS_BIN_ADC
#include "bin_adc_mcal.h"
#endif

#if 0
static ExtIntEvent_t IrSensor[100]={0};
static ExtIntEvent_t MemDcf77[120]={0};
#endif

static ExtIntEvent_t EventMemUartRx[200] = {0};

#ifdef HAS_INC_ENCODER
static ExtIntEvent_t EventMemA[100] = {0};
static ExtIntEvent_t EventMemB[100] = {0};
#endif

bool ExtIntFallingCallBackCustom(void) {
    bool res = false;
#ifdef HAS_BIN_ADC
    //res = bin_adc_start(1);
#endif
    return res;
}

bool ExtIntRisingCallBackCustom(void) {
    return true;
}

#define EXT_INT_SW_UART                               \
    { .num = 1,                                       \
      .event_mem_size = ARRAY_SIZE(EventMemUartRx),   \
      .name = "SwUartRx",                             \
      .Pad = {.port = PORT_A, .pin = 1,},             \
      .edge = PIN_INT_EDGE_NONE,                      \
      .fifo_pull = false,                             \
      .valid = true,                                  \
      .CallBackFalling = ExtIntFallingCallBackCustom, \
      .CallBackRising = ExtIntRisingCallBackCustom,   \
      .irq_priority = 1,                              \
      .EventMem = EventMemUartRx,                     \
    },



#ifdef HAS_INC_ENCODER
#define EXT_INT_INC_ENCODER                          \
    { .num = 1,                          \
      .name = "A",                       \
      .Pad = {.port=PORT_A, .pin=1,},                       \
      .edge = PIN_INT_EDGE_BOTH,                       \
      .valid = true,                       \
      .CallBackFalling = ExtIntCallBack,                       \
      .CallBackRising = ExtIntCallBack,                       \
      .irq_priority = 1,                       \
      .EventMem = EventMemA,                       \
      .event_mem_size = ARRAY_SIZE(EventMemA),                       \
    },                       \
    {                       \
        .num = 2,                       \
        .name = "B",                       \
        .Pad = {.port=PORT_A, .pin=2,},                       \
        .edge = PIN_INT_EDGE_BOTH,                       \
        .valid = true,                       \
        .irq_priority = 1,                       \
        .CallBackRising = ExtIntCallBack,                       \
        .CallBackFalling = ExtIntCallBack,                       \
        .EventMem = EventMemB,                       \
        .event_mem_size = ARRAY_SIZE(EventMemB),                       \
    },
#else
#define EXT_INT_INC_ENCODER
#endif



/*constant compile-time known settings*/
const ExtIntConfig_t ExtIntConfig[] = {
        EXT_INT_SW_UART
        EXT_INT_INC_ENCODER
#if 0
    { .num = 5, .name = "IR_Sensor*",  .Pad = {.port=PORT_A, .pin=5}, .edge = PIN_INT_EDGE_BOTH, .valid = true, .irq_priority = 0,    .interrupt_on = true,    },
    { .num = 2, .name = "--",  .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_BOTH, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 3, .name = "-",  .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_BOTH, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 4, .name = "--",  .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_BOTH, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 6, .name = "--",  .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_BOTH, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 7, .name = "--",  .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_BOTH, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 8, .name = "--",  .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_BOTH, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 9, .name = "--",  .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_BOTH, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 10, .name = "--", .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_BOTH, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 11, .name = "--", .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_BOTH, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 12, .name = "--", .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_BOTH, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 13, .name = "--", .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_BOTH, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 14, .name = "--", .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_BOTH, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
    { .num = 15, .name = "--", .Pad = {.port=PORT_UNDEF, .pin=15}, .edge = PIN_INT_EDGE_BOTH, .valid = true, .irq_priority = 2,    .interrupt_on = false,    },
#endif
};

ExtIntHandle_t ExtIntInstance[] = {
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
    {.num = 0, .valid = true,},
};

COMPONENT_GET_CNT(ExtInt, ext_int)

