#ifndef INPUT_CAPTURE_CONFIG_GENERAL_H
#define INPUT_CAPTURE_CONFIG_GENERAL_H

#include <stdbool.h>
#include <stdint.h>

#include "input_capture_types.h"

#ifndef HAS_INPUT_CAPTURE
#error "Add HAS_INPUT_CAPTURE"
#endif /*HAS_INPUT_CAPTURE*/

typedef enum {
    INPUT_CAPTURE_NUM_SPK_INT = 1,

    INPUT_CAPTURE_NUM_UNDEF =0,
}TeraTestInputCaptureNum_t;

extern const InputCaptureConfig_t InputCaptureConfig[];
extern InputCaptureHandle_t InputCaptureInstance[];

uint32_t input_capture_get_cnt(void);

#endif /* INPUT_CAPTURE_CONFIG_GENERAL_H  */
