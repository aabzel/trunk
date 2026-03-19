#include "can_mailbox_config.h"

#include "log_config.h"
#include "data_utils.h"

#define CAN_MESSAGE_BUFFER_CAN_TX                                                        \
    { .num = 1,  .frame_id = 0x1,   .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, },  .mb_index = 16, .direction = CONNECT_DIR_TRANSMIT,  .id_type = CAN_FRAME_ID_STANDARD,  .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 2,  .frame_id = 0x3,   .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, },  .mb_index = 17, .direction = CONNECT_DIR_TRANSMIT,  .id_type = CAN_FRAME_ID_STANDARD,  .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 3,  .frame_id = 0x5,   .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, },  .mb_index = 18, .direction = CONNECT_DIR_TRANSMIT,  .id_type = CAN_FRAME_ID_STANDARD,  .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 4,  .frame_id = 0x7,   .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, },  .mb_index = 19, .direction = CONNECT_DIR_TRANSMIT,  .id_type = CAN_FRAME_ID_STANDARD,  .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 5,  .frame_id = 0x9,   .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, },  .mb_index = 20, .direction = CONNECT_DIR_TRANSMIT,  .id_type = CAN_FRAME_ID_STANDARD,  .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 6,  .frame_id = 0x11,  .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, },  .mb_index = 21,.direction = CONNECT_DIR_TRANSMIT,  .id_type = CAN_FRAME_ID_STANDARD,  .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 7,  .frame_id = 0x13,  .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, },  .mb_index = 22,.direction = CONNECT_DIR_TRANSMIT,  .id_type = CAN_FRAME_ID_STANDARD,  .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 8,  .frame_id = 0x15,  .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, },  .mb_index = 23,.direction = CONNECT_DIR_TRANSMIT,  .id_type = CAN_FRAME_ID_STANDARD,  .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 9,  .frame_id = 0x17,  .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, },  .mb_index = 24,.direction = CONNECT_DIR_TRANSMIT,  .id_type = CAN_FRAME_ID_STANDARD,  .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 10, .frame_id = 0x19,  .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, },  .mb_index = 25,.direction = CONNECT_DIR_TRANSMIT,  .id_type = CAN_FRAME_ID_STANDARD,  .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 11, .frame_id = 0x21,  .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, },  .mb_index = 26,.direction = CONNECT_DIR_TRANSMIT,  .id_type = CAN_FRAME_ID_STANDARD,  .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 12, .frame_id = 0x23,  .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, },  .mb_index = 27,.direction = CONNECT_DIR_TRANSMIT,  .id_type = CAN_FRAME_ID_STANDARD,  .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 13, .frame_id = 0x25,  .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, },  .mb_index = 28, .direction = CONNECT_DIR_TRANSMIT, .id_type = CAN_FRAME_ID_STANDARD,  .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 14, .frame_id = 0x27,  .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, },  .mb_index = 29,.direction = CONNECT_DIR_TRANSMIT,  .id_type = CAN_FRAME_ID_STANDARD,  .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 15, .frame_id = 0x29,  .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, },  .mb_index = 30,.direction = CONNECT_DIR_TRANSMIT,  .id_type = CAN_FRAME_ID_STANDARD,  .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 16, .frame_id = 0x31,  .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, },  .mb_index = 31,.direction = CONNECT_DIR_TRANSMIT,  .id_type = CAN_FRAME_ID_STANDARD,  .interrupt_on = true,  .name = "", .valid = true, },

#define CAN_MESSAGE_BUFFER_CAN_RX                                                    \
    { .num = 17, .frame_id = 0x0,  .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 0,  .direction = CONNECT_DIR_RECEIVER, .id_type = CAN_FRAME_ID_STANDARD,   .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 18, .frame_id = 0x2,  .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 1,  .direction = CONNECT_DIR_RECEIVER, .id_type = CAN_FRAME_ID_STANDARD,   .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 19, .frame_id = 0x4,  .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 2,  .direction = CONNECT_DIR_RECEIVER, .id_type = CAN_FRAME_ID_STANDARD,   .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 20, .frame_id = 0x6,  .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 3,  .direction = CONNECT_DIR_RECEIVER, .id_type = CAN_FRAME_ID_STANDARD,  .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 21, .frame_id = 0x8,  .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 4,  .direction = CONNECT_DIR_RECEIVER, .id_type = CAN_FRAME_ID_STANDARD,   .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 22, .frame_id = 0x10, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 5, .direction = CONNECT_DIR_RECEIVER,  .id_type = CAN_FRAME_ID_STANDARD,  .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 23, .frame_id = 0x12, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 6, .direction = CONNECT_DIR_RECEIVER,  .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 24, .frame_id = 0x14, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 7, .direction = CONNECT_DIR_RECEIVER,  .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 25, .frame_id = 0x16, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 8, .direction = CONNECT_DIR_RECEIVER,  .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 26, .frame_id = 0x18, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 9, .direction = CONNECT_DIR_RECEIVER,  .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 27, .frame_id = 0x20, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 10, .direction = CONNECT_DIR_RECEIVER,  .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 28, .frame_id = 0x22, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 11, .direction = CONNECT_DIR_RECEIVER,  .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 29, .frame_id = 0x24, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 12, .direction = CONNECT_DIR_RECEIVER,  .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 30, .frame_id = 0x26, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 13, .direction = CONNECT_DIR_RECEIVER,  .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 31, .frame_id = 0x28, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 14, .direction = CONNECT_DIR_RECEIVER,  .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 32, .frame_id = 0x30, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 15, .direction = CONNECT_DIR_RECEIVER,  .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \

#define CAN_MESSAGE_BUFFER_CAN                             \
    CAN_MESSAGE_BUFFER_CAN_RX                              \
    CAN_MESSAGE_BUFFER_CAN_TX

const CanMessageBufferConfig_t CanMessageBufferConfig[] = {
        CAN_MESSAGE_BUFFER_CAN                                  \
};


uint32_t can_mailbox_get_cnt(void) {
    uint32_t cnt_conf = ARRAY_SIZE(CanMessageBufferConfig);
    return cnt_conf;
}


