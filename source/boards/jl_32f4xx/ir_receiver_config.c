#include "ir_receiver_config.h"

#include "data_utils.h"

#define SIGNAL_MAX_SIZE 128
static IrReceiverEvent_t signalArrayCur[SIGNAL_MAX_SIZE]={0};
static IrReceiverEvent_t signalArrayFix[SIGNAL_MAX_SIZE]={0};

#define FRAME_PREAMBPLE_BITS 1
#define FRAME_STOP_BITS 1
#define FRAME_SIZE 4
#define FRAME_PAYLOAD_BITS (FRAME_SIZE*8)
#define FRAME_SIZE_BITS (FRAME_PAYLOAD_BITS+FRAME_PREAMBPLE_BITS + FRAME_STOP_BITS)
#define FRAME_SIZE_EVENTS (FRAME_SIZE_BITS*2)

const IrReceiverConfig_t IrReceiverConfig[] = {
    {
        .num = 1,
        .timer_num = 2,
        .exp_size = FRAME_SIZE_EVENTS,
        .signal_cur = signalArrayCur,
        .signal_fix = signalArrayFix,
        .signal_size = ARRAY_SIZE(signalArrayCur),
        .valid = true,
        .IrPad = {.port=PORT_A,
                  .pin=5,
                  },
        .name = "IrSamsung",
    },
};

IrReceiverHandle_t IrReceiverInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

COMPONENT_GET_CNT(IrReceiver, ir_receiver)


