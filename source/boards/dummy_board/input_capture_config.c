#include "input_capture_config.h"

#ifndef HAS_INPUT_CAPTURE
#error "Add HAS_INPUT_CAPTURE"
#endif /*HAS_INPUT_CAPTURE*/

#include "data_utils.h"

const InputCaptureConfig_t InputCaptureConfig[] = {
     {
             .num = INPUT_CAPTURE_NUM_SPK_INT,
             .direction = INPUT_CAPTURE_CNT_DIRR_UP,
             .divider = 1,
             .timer_num = 3,
             .channel = 2,
             .polarity=INPUT_CAPTURE_EDGE_RISING,
             .Pad = {.port=PORT_B, .pin=5,},
             .name = "SpkInt",
             .valid = true,
             .on = true,
             .interrupt_on = true,
     },
};


InputCaptureHandle_t InputCaptureInstance[] = {
    {.num=INPUT_CAPTURE_NUM_SPK_INT, .valid=true, },
};

uint32_t input_capture_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(InputCaptureInstance);
    cnt2 = ARRAY_SIZE(InputCaptureConfig);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
}
