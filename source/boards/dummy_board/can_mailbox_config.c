#include "can_mailbox_config.h"

#include "log_config.h"
#include "data_utils.h"

#define CAN_MESSAGE_BUFFER_CAN_RX                                                        \
    { .num = 1, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 1, .direction = CONNECT_DIR_TRANSMIT,  .frame_id = 1, .id_type = CAN_FRAME_ID_STANDARD,  .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 2, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 3, .direction = CONNECT_DIR_TRANSMIT,  .frame_id = 3, .id_type = CAN_FRAME_ID_STANDARD,   .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 3, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 5, .direction = CONNECT_DIR_TRANSMIT,  .frame_id = 5, .id_type = CAN_FRAME_ID_STANDARD,   .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 4, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 7, .direction = CONNECT_DIR_TRANSMIT,  .frame_id = 7, .id_type = CAN_FRAME_ID_STANDARD,   .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 5, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 9, .direction = CONNECT_DIR_TRANSMIT,  .frame_id = 9, .id_type = CAN_FRAME_ID_STANDARD,   .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 6, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 11,.direction = CONNECT_DIR_TRANSMIT,  .frame_id = 11, .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 7, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 13,.direction = CONNECT_DIR_TRANSMIT,  .frame_id = 13, .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 8, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 15,.direction = CONNECT_DIR_TRANSMIT,  .frame_id = 15, .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 9, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 17,.direction = CONNECT_DIR_TRANSMIT,  .frame_id = 17, .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 10, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 19,.direction = CONNECT_DIR_TRANSMIT, .frame_id = 19, .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 11, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 21,.direction = CONNECT_DIR_TRANSMIT, .frame_id = 21, .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 12, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 23,.direction = CONNECT_DIR_TRANSMIT, .frame_id = 23, .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 13, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 25, .direction = CONNECT_DIR_TRANSMIT,.frame_id = 25, .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 14, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 27,.direction = CONNECT_DIR_TRANSMIT, .frame_id = 27, .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 15, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 29,.direction = CONNECT_DIR_TRANSMIT, .frame_id = 29, .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 16, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 31,.direction = CONNECT_DIR_TRANSMIT, .frame_id = 31, .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },

#define CAN_MESSAGE_BUFFER_CAN_TX                                                    \
    { .num = 17, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 0,  .direction = CONNECT_DIR_RECEIVER, .frame_id = 0, .id_type = CAN_FRAME_ID_STANDARD,   .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 17, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 2,  .direction = CONNECT_DIR_RECEIVER, .frame_id = 2, .id_type = CAN_FRAME_ID_STANDARD,   .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 17, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 4,  .direction = CONNECT_DIR_RECEIVER, .frame_id = 4, .id_type = CAN_FRAME_ID_STANDARD,   .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 18, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 6,  .direction = CONNECT_DIR_RECEIVER, .frame_id = 6, .id_type = CAN_FRAME_ID_STANDARD,  .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 19, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 8,  .direction = CONNECT_DIR_RECEIVER, .frame_id = 8, .id_type = CAN_FRAME_ID_STANDARD,   .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 20, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 10, .direction = CONNECT_DIR_RECEIVER, .frame_id = 10, .id_type = CAN_FRAME_ID_STANDARD,  .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 21, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 12, .direction = CONNECT_DIR_RECEIVER, .frame_id = 12, .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 22, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 14, .direction = CONNECT_DIR_RECEIVER, .frame_id = 14, .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 23, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 16, .direction = CONNECT_DIR_RECEIVER, .frame_id = 16, .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 24, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 18, .direction = CONNECT_DIR_RECEIVER, .frame_id = 18, .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 25, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 20, .direction = CONNECT_DIR_RECEIVER, .frame_id = 20, .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 26, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 22, .direction = CONNECT_DIR_RECEIVER, .frame_id = 22, .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 27, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 24, .direction = CONNECT_DIR_RECEIVER, .frame_id = 24, .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 28, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 26, .direction = CONNECT_DIR_RECEIVER, .frame_id = 26, .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 29, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 28, .direction = CONNECT_DIR_RECEIVER, .frame_id = 28, .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \
    { .num = 30, .cans = {.can0=1, .can1=1,  .can2=1,  .can3=1, }, .mb_index = 30, .direction = CONNECT_DIR_RECEIVER, .frame_id = 30, .id_type = CAN_FRAME_ID_STANDARD, .interrupt_on = true,  .name = "", .valid = true, },         \

#define CAN_MESSAGE_BUFFER_CAN                             \
    CAN_MESSAGE_BUFFER_CAN_TX                              \
    CAN_MESSAGE_BUFFER_CAN_RX

const CanMessageBufferConfig_t CanMessageBufferConfig[] = {
        CAN_MESSAGE_BUFFER_CAN                                  \
};


uint32_t can_mailbox_get_cnt(void) {
    uint32_t cnt_conf = ARRAY_SIZE(CanMessageBufferConfig);
    return cnt_conf;
}


