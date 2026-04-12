#ifndef INPUT_CAPTURE_CUSTOM_DRV_H
#define INPUT_CAPTURE_CUSTOM_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "microcontroller_const.h"
#include "input_capture_custom_types.h"

#ifndef HAS_TIMER
#error "+HAS_TIMER"
#endif

#ifndef HAS_INPUT_CAPTURE
#error "+HAS_INPUT_CAPTURE"
#endif

sub_tmr_input_sel_type InputCaptureChannelToTrigger(InputCaptureChannel_t channel);

#endif /* INPUT_CAPTURE_CUSTOM_DRV_H  */
