#include "can_tx_planner_config.h"

#include "data_utils.h"

const CanTxPlannerConfig_t CanTxPlannerConfig[] = {
    {
        .num = 1,
        .on = false,
        .tx_period_ms = 1000,
        .valid = true,
        .name = "Frame1",
        .TxMessage =
            {
                .can_bus_num = 1,
                .identifier.extended = 0xC2,
                .id_type = CAN_FRAME_ID_EXTENDED,
                .size = 8,
                .data = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA},
                .frame_type = CAN_TX_FRAME_DATA,
                .time_stamp = 0,
                .is_fd = false,
            },
    },

    {
        .num = 4,
        .on = false,
        .tx_period_ms = 1000,
        .valid = true,
        .name = "Frame1",
        .TxMessage =
            {
                .can_bus_num = 1,
                .identifier.extended = 0xC2,
                .id_type = CAN_FRAME_ID_EXTENDED,
                .size = 8,
                .data = {0xAA, 0x5A, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA},
                .frame_type = CAN_TX_FRAME_DATA,
                .time_stamp = 0,
                .is_fd = false,
            },
    },

    {
        .num = 2,
        .on = false,
        .tx_period_ms = 1000,
        .valid = true,
        .name = "Frame2",
        .TxMessage =
            {
                .can_bus_num = 2,
                .id_type = CAN_FRAME_ID_EXTENDED,
                .identifier.extended = 0xC2,
                .size = 8,
                .data = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA},
                .time_stamp = 0,
                .frame_type = CAN_TX_FRAME_DATA,
                .is_fd = false,
            },
    },

    {
        .num = 3,
        .on = false,
        .tx_period_ms = 1000,
        .valid = true,
        .name = "Frame2",
        .TxMessage =
            {
                .can_bus_num = 2,
                .id_type = CAN_FRAME_ID_EXTENDED,
                .identifier.extended = 0xC2,
                .size = 8,
                .data = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xEA, 0xAA},
                .time_stamp = 0,
                .frame_type = CAN_TX_FRAME_DATA,
                .is_fd = false,
            },
    },

};

CanTxPlannerHandle_t CanTxPlannerInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
    {
        .num = 2,
        .valid = true,
    },
    {
        .num = 3,
        .valid = true,
    },
    {
        .num = 4,
        .valid = true,
    },
    {
        .num = 5,
        .valid = true,
    },
    {
        .num = 6,
        .valid = true,
    },
    {
        .num = 7,
        .valid = true,
    },
    {
        .num = 8,
        .valid = true,
    },
    {
        .num = 9,
        .valid = true,
    },
    {
        .num = 10,
        .valid = true,
    },
};

uint32_t can_tx_planner_get_cnt(void) {
    uint8_t cnt = 0;
    uint8_t cnt_cfg = 0;
    uint8_t cnt_node = 0;
    cnt_cfg = ARRAY_SIZE(CanTxPlannerConfig);
    cnt_node = ARRAY_SIZE(CanTxPlannerInstance);
    cnt = DATA_MIN(cnt_cfg, cnt_node);
    return cnt;
}

uint32_t can_tx_planner_get_cells(void) {
    uint8_t cnt_node = 0;
    cnt_node = ARRAY_SIZE(CanTxPlannerInstance);
    return cnt_node;
}
