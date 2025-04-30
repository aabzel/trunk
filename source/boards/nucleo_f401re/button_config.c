#include "button_config.h"

#ifndef HAS_BUTTON
#error "Add HAS_BUTTON"
#endif /*HAS_BUTTON*/

#include "data_utils.h"

#ifdef HAS_SI4703
#include "si4703_drv.h"
#endif

static bool button1_proc(void) {
    bool res = false;
    return res;
}

const ButtonConfig_t ButtonConfig[] = {
    {
        .num = 1,
        .press_short_handler = button1_proc,
        .press_long_handler = NULL,
        .pad = {.port = PORT_C, .pin = 13},
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

uint32_t button_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(ButtonInstance);
    cnt2 = ARRAY_SIZE(ButtonConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
