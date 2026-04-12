#include "iqueue_config.h"

#include "data_utils.h"
#include "iqueue_types.h"
#include "can_types.h"

#ifdef HAS_ISO_TP_CUSTOM
#include "lib_iso15765.h"
#include "iso_tp_config.h"
#endif

// 5- lost 29
// 6- lost 13
// 7- lost 0
// 8- lost 0
// 11- lost 0
static CanMessage_t ArrayCan1Frames[7] = {0};
static CanMessage_t ArrayCan2Frames[7] = {0};
static uint8_t ArrayU8[5] = {0};
static int16_t ArrayS16[6] = {0};

static iqueue_t iQueueHandleS16 = {0};
static iqueue_t iQueueHandleU8 = {0};
static iqueue_t iQueueHandleCAN1 = {0};
static iqueue_t iQueueHandleCAN2 = {0};

const iQueueConfig_t SECTION_CFG_DATA iQueueConfig[] = {
    { .num = IQUEUE_NUN_U8_5,
      .Interface={.interface_name=INTERFACE_NAME_RAM, .num=1,},
#if 0
      .type=TYPE_UINT8,
#endif
      .pHandle = ( iqueue_t *)(&iQueueHandleU8),
      .storage = (void* ) ArrayU8,
      .element_cnt = ARRAY_SIZE(ArrayU8),
      .element_size = sizeof(uint8_t),
      .name = "U8",
      .valid = true, },

    { .num = IQUEUE_NUN_S16_6,
      .Interface={.interface_name=INTERFACE_NAME_RAM, .num=2,},
#if 0
      .type=TYPE_INT16,
#endif
      .pHandle = ( iqueue_t *)(&iQueueHandleS16),
      .storage = (void* ) ArrayS16,
      .element_cnt = ARRAY_SIZE(ArrayS16),
      .element_size = sizeof(int16_t),
      .name = "S16", .valid = true, },

    {
      .num = IQUEUE_NUN_CAN1,
      .Interface={.interface_name=INTERFACE_NAME_CAN, .num = 1,},
#if 0
      .type=TYPE_STRUCT,
#endif
      .pHandle = ( iqueue_t *) (&iQueueHandleCAN1),
      .storage = (void* ) ArrayCan1Frames,
      .element_cnt = ARRAY_SIZE(ArrayCan1Frames),
      .element_size = sizeof(CanMessage_t),
      .name = "CAN1",
      .valid = true,
    },

    {
        .num = IQUEUE_NUN_CAN2,
        .Interface={.interface_name=INTERFACE_NAME_CAN, .num = 2,},
#if 0
        .type=TYPE_STRUCT,
#endif
        .pHandle = ( iqueue_t *) (&iQueueHandleCAN2),
        .storage = (void* ) ArrayCan2Frames,
        .element_cnt = ARRAY_SIZE(ArrayCan2Frames),
        .element_size = sizeof(CanMessage_t),
        .name = "CAN2",
        .valid = true,
    },
};

iQueueHandle_t iQueueInstance[] = {
    { .num = IQUEUE_NUN_U8_5,  .valid = true,    },
    { .num = IQUEUE_NUN_S16_6, .valid = true,    },
    { .num = IQUEUE_NUN_CAN1,  .valid = true,    },
    { .num = IQUEUE_NUN_CAN2,  .valid = true,    },
};

COMPONENT_GET_CNT(iQueue, iqueue)
