#include "iqueue_config.h"

#include "data_utils.h"
#include "iqueue_types.h"
#ifdef HAS_ISO_TP
#include "lib_iso15765.h"
#include "iso_tp_config.h"
#endif

#ifdef HAS_ISO_TP
static canbus_frame_t ArrayCanBusFrame1[11] = {0};
static canbus_frame_t ArrayCanBusFrame2[7] = {0};
static canbus_frame_t ArrayCanBusFrame3[7] = {0};
#endif
static uint8_t ArrayU8[5] = {0};
static int16_t ArrayS16[6] = {0};

static iqueue_t iQueueHandleS16 = {0};
static iqueue_t iQueueHandleU8  = {0};

const iQueueConfig_t iQueueConfig[] = {
    { .num = IQUEUE_NUN_U8_5,
      .Interface = {.interface_name = INTERFACE_NAME_RAM, .num = 0, },
      .pHandle = ( iqueue_t *)(&iQueueHandleU8),
      .storage = (void* ) ArrayU8,
      .element_cnt = ARRAY_SIZE(ArrayU8),
      .element_size = sizeof(uint8_t),
      .name = "U8", .valid = true,
    },
    { .num = IQUEUE_NUN_S16_6,
      .Interface = {.interface_name = INTERFACE_NAME_RAM, .num = 0, },
      .pHandle = ( iqueue_t *)(&iQueueHandleS16),
      .storage = (void* ) ArrayS16,
      .element_cnt = ARRAY_SIZE(ArrayS16),
      .element_size = sizeof(int16_t),
      .name = "S16", .valid = true,
    },
#ifdef HAS_ISO_TP
    { .num = IQUEUE_NUN_CAN_FRAME_1,
      .Interface = {.interface_name = INTERFACE_NAME_CAN, .num = 0, },
      .pHandle = ( iqueue_t *) (&IsoTpInstance[0].instance.inqueue),
      .storage = (void* ) ArrayCanBusFrame1,
      .element_cnt = ARRAY_SIZE(ArrayCanBusFrame1),
      .element_size = sizeof(canbus_frame_t),
      .name = "CanFrames1",
      .valid = true,
    },
    { .num = IQUEUE_NUN_CAN_FRAME_2,
      .Interface = {.interface_name = INTERFACE_NAME_ISO_TP, .num = 1, },
      .pHandle = ( iqueue_t *) (&IsoTpInstance[1].instance.inqueue),
      .storage = (void* ) ArrayCanBusFrame2,
      .element_cnt = ARRAY_SIZE(ArrayCanBusFrame2),
      .element_size = sizeof(canbus_frame_t),
      .name = "CanFrames2",
      .valid = true,
    },
    { .num = IQUEUE_NUN_CAN_FRAME_3,
      .Interface = {.interface_name = INTERFACE_NAME_ISO_TP, .num = 2, },
      .pHandle = ( iqueue_t *) (&IsoTpInstance[2].instance.inqueue),
      .storage = (void* ) ArrayCanBusFrame3,
      .element_cnt = ARRAY_SIZE(ArrayCanBusFrame3),
      .element_size = sizeof(canbus_frame_t),
      .name = "CanFrames3",
      .valid = true,
    },
#endif
};


iQueueHandle_t iQueueInstance[] = {
    { .num = IQUEUE_NUN_U8_5,        .valid = true,    },
    { .num = IQUEUE_NUN_S16_6,       .valid = true,    },
#ifdef HAS_ISO_TP
    { .num = IQUEUE_NUN_CAN_FRAME_1, .valid = true,    },
    { .num = IQUEUE_NUN_CAN_FRAME_2, .valid = true,    },
    { .num = IQUEUE_NUN_CAN_FRAME_3, .valid = true,    },
#endif
};

COMPONENT_GET_CNT(iQueue, iqueue)
