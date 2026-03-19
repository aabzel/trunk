#ifndef INPUT_CAPTURE_TYPES_H
#define INPUT_CAPTURE_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "input_capture_const.h"
#include "gpio_types.h"

#ifdef HAS_INPUT_CAPTURE_CUSTOM
#include "input_capture_custom_types.h"
#else
#define INPUT_CAPTURE_CUSTON_VARIABLES
#endif

#ifndef HAS_INPUT_CAPTURE
#error "Add HAS_INPUT_CAPTURE"
#endif

#define INPUT_CAPTURE_COMMON_VARIABLES                \
    bool valid;                                       \
    uint8_t num;                                      \
    uint8_t divider;                                  \
    bool interrupt_on;                                \
    uint8_t timer_num;                                \
    InputCaptureChannel_t channel; /*TimerChannel*/   \
    InputCaptureCountDirection_t direction;           \
    InputCapturePolarity_t polarity;                  \
    Pad_t Pad;                                        \
    bool on;

typedef struct {
    INPUT_CAPTURE_COMMON_VARIABLES
    char* name;
} InputCaptureConfig_t;

#define INPUT_CAPTURE_ISR_VARIABLES                 \
    volatile uint32_t int_cnt;


typedef struct {
    INPUT_CAPTURE_COMMON_VARIABLES

    INPUT_CAPTURE_CUSTON_VARIABLES
    INPUT_CAPTURE_ISR_VARIABLES
    uint32_t error_cnt;
    bool init_done;
} InputCaptureHandle_t;

#endif /* INPUT_CAPTURE_TYPES_H */
