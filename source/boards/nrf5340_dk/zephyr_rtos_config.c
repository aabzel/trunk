#include "zephyr_rtos_config.h"

#include <zephyr/kernel.h>

#include "common_functions.h"
#include "data_utils.h"
#include "led_drv.h"
#include "log.h"
#include "zephyr_rtos_drv.h"
#include "zephyr_rtos_types.h"

k_thread_stack_t BareBoneStackSpace[4096];

const RtosTaskConfig_t RtosTaskConfig[] = {
    {
        .num = 1,
        .TaskCode = bare_bone_task,
        .name = "BareBone",
        .stack_start = BareBoneStackSpace,
        .stack_depth_byte = sizeof(BareBoneStackSpace),
        .priority = ZEPHYR_PRIORITY_LOW,
        .valid = true,
    },
};

RtosTaskHandle_t RtosTaskInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

uint32_t rtos_task_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(RtosTaskConfig);
    cnt2 = ARRAY_SIZE(RtosTaskInstance);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    } else {
        LOG_ERROR(ZEPHYR_RTOS, "ConfigErr %u!=%u", cnt1, cnt2);
    }
    return cnt;
}
