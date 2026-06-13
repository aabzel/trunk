#include "input_capture_config.h"

#ifndef HAS_INPUT_CAPTURE
#error "Add HAS_INPUT_CAPTURE"
#endif /**/

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

COMPONENT_GET_CNT(InputCapture, input_capture)


