#include "button_config.h"

#include "data_utils.h"

#ifndef HAS_BUTTON
#error "Add HAS_BUTTON"
#endif

static bool button1_proc(void) {
    bool res = false;
    return res;
}

static bool button2_proc(void) {
    bool res = false;
    return res;
}

const ButtonConfig_t ButtonConfig[ ] = {
    {
            .num = 1,
            .press_short_handler = button1_proc,
            .pad = {.port = PORT_F, .pin = 14,},
            .active = GPIO_LVL_LOW,
            .name = "TamperSensor",
            .valid = true,
    },
    {
            .num = 2,
            .press_short_handler = button2_proc,
            .pad = {.port = PORT_C, .pin = 13,},
            .active = GPIO_LVL_LOW,
            .name = "TAMPER",
            .valid = true,
    },
};

ButtonHandle_t ButtonInstance[ ] = {
   {    .num = 1,    .valid = true,},
   {    .num = 2,    .valid = true,},
};

COMPONENT_GET_CNT(Button, button)

