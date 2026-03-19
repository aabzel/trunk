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


static bool button3_proc(void) {
    bool res = false;
    return res;
}


const ButtonConfig_t ButtonConfig[ ] = {
    {
            .num = 1,
            .press_short_handler = button1_proc,
            .pad = {.port = PORT_E, .pin = 10,},
            .active = GPIO_LVL_LOW,
            .name = "SW1",
            .valid = true,
    },
    {
            .num = 2,
            .press_short_handler = button2_proc,
            .pad = {.port = PORT_E, .pin = 11,},
            .active = GPIO_LVL_LOW,
            .name = "SW2",
            .valid = true,
    },
    {
            .num = 3,
            .press_short_handler = button3_proc,
            .pad = {.port = PORT_E, .pin = 12,},
            .active = GPIO_LVL_LOW,
            .name = "SW3",
            .valid = true,
    },
};

ButtonHandle_t ButtonInstance[ ] = {
   {    .num = 1,    .valid = true,},
   {    .num = 2,    .valid = true,},
   {    .num = 3,    .valid = true,},
};

COMPONENT_GET_CNT(Button, button)

