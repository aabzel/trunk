#include "button_config.h"

#ifndef HAS_BUTTON
#error "Add HAS_BUTTON"
#endif /**/

#include "data_utils.h"

static bool button1_proc(void) {
    bool res = false;
    return res;
}

const ButtonConfig_t SECTION_CFG_DATA ButtonConfig[] = {
    {
        .num = 1,
        .press_short_handler = button1_proc,
        .press_long_handler = NULL,
        .pad = {.port = PORT_I, .pin = 11,},
        .active = GPIO_LVL_LOW,
        .name = "B1",
        .valid = true,
    },
};

ButtonHandle_t ButtonInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

COMPONENT_GET_CNT(Button, button)


