#include "ext_int_config.h"

#include "log_config.h"
#include "data_utils.h"

static bool CallBackRising1(void) {
    bool res = true;
    return res;
}

static bool CallBackFalling1(void) {
    bool res = true;
    return res;
}


static bool CallBackRising2(void) {
    bool res = true;
    return res;
}

static bool CallBackFalling2(void) {
    bool res = true;
    return res;
}


static bool CallBackRising3(void) {
    bool res = true;
    return res;
}

static bool CallBackFalling3(void) {
    bool res = true;
    return res;
}


static bool CallBackRising4(void) {
    bool res = true;
    return res;
}

static bool CallBackFalling4(void) {
    bool res = true;
    return res;
}


static bool CallBackRising5(void) {
    bool res = true;
    return res;
}

static bool CallBackFalling5(void) {
    bool res = true;
    return res;
}


static bool CallBackRising6(void) {
    bool res = true;
    return res;
}

static bool CallBackFalling6(void) {
    bool res = true;
    return res;
}


static bool CallBackRising7(void) {
    bool res = true;
    return res;
}
;
static bool CallBackFalling7(void) {
    bool res = true;
    return res;
}


static bool CallBackRising8(void) {
    bool res = true;
    return res;
}

static bool CallBackFalling8(void) {
    bool res = true;
    return res;
}

static ExtIntEvent_t EventArray1[5]={0};
static ExtIntEvent_t EventArray2[5]={0};
static ExtIntEvent_t EventArray3[5]={0};
static ExtIntEvent_t EventArray4[5]={0};
static ExtIntEvent_t EventArray5[5]={0};
static ExtIntEvent_t EventArray6[5]={0};
static ExtIntEvent_t EventArray7[5]={0};
static ExtIntEvent_t EventArray8[5]={0};

/* constant compile-time known settings */
const ExtIntConfig_t ExtIntConfig[] = {
    { .num = 1,
            .EventMem=EventArray3,
                  .event_mem_size=ARRAY_SIZE(EventArray3),
            .name = "DIAG1_3/4",
            .CallBackRising=CallBackRising3,
            .CallBackFalling=CallBackFalling3,
            .Pad = {.port=PORT_D, .pin=1,},
            .edge = PIN_INT_EDGE_FALLING, .valid = true, .irq_priority = 0,     },

   { .num = 2,
            .EventMem=EventArray6,
                     .event_mem_size=ARRAY_SIZE(EventArray6),
            .name = "DIAG3_3/4",
            .CallBackRising=CallBackRising6,
            .CallBackFalling=CallBackFalling6,
            .Pad = {.port=PORT_D, .pin=12,},
            .edge = PIN_INT_EDGE_FALLING, .valid = true, .irq_priority = 0,     },

    { .num = 3,
            .EventMem=EventArray5,
                  .event_mem_size=ARRAY_SIZE(EventArray5),
            .name = "DIAG3_1/2",
            .CallBackRising=CallBackRising5,
            .CallBackFalling=CallBackFalling5,
            .Pad = {.port=PORT_D, .pin=15,},
            .edge = PIN_INT_EDGE_FALLING, .valid = true, .irq_priority = 0,     },

    { .num = 4,
      .EventMem=EventArray1,
      .event_mem_size=ARRAY_SIZE(EventArray1),
            .name = "DIAG1_1/2",
            .CallBackRising=CallBackRising1,
            .CallBackFalling=CallBackFalling1,
            .Pad = {.port=PORT_D, .pin=4,},
            .edge = PIN_INT_EDGE_FALLING, .valid = true, .irq_priority = 0,     },

     { .num = 5,
            .EventMem=EventArray7,
                     .event_mem_size=ARRAY_SIZE(EventArray7),
            .name = "DIAG4_1/2",
            .CallBackRising=CallBackRising7,
            .CallBackFalling=CallBackFalling7,
            .Pad = {.port=PORT_D, .pin=9,},
            .edge = PIN_INT_EDGE_FALLING, .valid = true, .irq_priority = 0,     },

    { .num = 6,
            .EventMem=EventArray8,
                     .event_mem_size=ARRAY_SIZE(EventArray8),
            .name = "DIAG4_3/4",
            .CallBackRising=CallBackRising8,
            .CallBackFalling=CallBackFalling8,
            .Pad = {.port=PORT_D, .pin=6,},
            .edge = PIN_INT_EDGE_FALLING, .valid = true,
            .irq_priority = 0,     },

    { .num = 7,
            .EventMem=EventArray4,
                  .event_mem_size=ARRAY_SIZE(EventArray4),
            .name = "DIAG2_3/4",
            .CallBackRising=CallBackRising4,
            .CallBackFalling=CallBackFalling4,
            .Pad = {.port=PORT_C, .pin=9,},
            .edge = PIN_INT_EDGE_FALLING, .valid = true, .irq_priority = 0,     },

    { .num = 8,
      .EventMem=EventArray2,
      .event_mem_size=ARRAY_SIZE(EventArray2),
      .name = "DIAG2_1/2",
      .CallBackRising=CallBackRising2,
      .CallBackFalling=CallBackFalling2,
      .Pad = {.port=PORT_C, .pin=8,},
      .edge = PIN_INT_EDGE_FALLING, .valid = true, .irq_priority = 0,     },
};

ExtIntHandle_t ExtIntInstance[16] = {
    {.num = 1, .valid = true,},
    {.num = 2, .valid = true,},
    {.num = 3, .valid = true,},
    {.num = 4, .valid = true,},
    {.num = 5, .valid = true,},
    {.num = 6, .valid = true,},
    {.num = 7, .valid = true,},
    {.num = 8, .valid = true,},
};

COMPONENT_GET_CNT(ExtInt, ext_int)

