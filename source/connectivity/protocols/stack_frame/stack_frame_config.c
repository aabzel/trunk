#include "stack_frame_config.h"

#include <stddef.h>

#include "data_utils.h"

const StackFrameConfig_t StackFrameConfig[]={
    {
     .num=1,
    },
};

StackFrameHandle_t StackFrameInstance[]={
    {.num = 1,  },
};

uint32_t stack_frame_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(StackFrameConfig);
    uint32_t cnt_ints = ARRAY_SIZE(StackFrameInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
