#include "mic2026_config.h"

#ifndef HAS_MIC2026
#error "Add HAS_MIC2026"
#endif /*HAS_MIC2026*/

#include "gpio_custom_const.h"
#include "mic2026_types.h"

const Mic2026Config_t Mic2026Config = {
    .num = 1,
    .valid = true,

    .Chan[0] =
        {
            .CtrlPad = {.port = PORT_A, .pin = 10},
            .FbPad = {.port = PORT_B, .pin = 6},
            .CtrlDflt = GPIO_LVL_HI,
            .ChanId = CHANNEL_A,
            .name = "A",
            .valid = true,
        },

    .Chan[1] =
        {
            .CtrlPad = {.port = PORT_A, .pin = 8},
            .FbPad = {.port = PORT_B, .pin = 5},
            .CtrlDflt = GPIO_LVL_LOW,
            .ChanId = CHANNEL_B,
            .name = "B",
            .valid = true,
        },

};

Mic2026Handle_t Mic2026Item = {
    .num = 1,
    .valid = true,

    .ChanVal[0] = {.ChanId = CHANNEL_A, .valid = true, .FbPadVal = GPIO_LVL_UNDEF, .CtrlPad = GPIO_LVL_UNDEF},
    .ChanVal[1] = {.ChanId = CHANNEL_B, .valid = true, .FbPadVal = GPIO_LVL_UNDEF, .CtrlPad = GPIO_LVL_UNDEF}

};
