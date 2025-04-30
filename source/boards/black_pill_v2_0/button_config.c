#include "button_config.h"

#ifndef HAS_BUTTON
#error "Add HAS_BUTTON"
#endif /*HAS_BUTTON*/

#ifdef HAS_CORE
#include "core_driver.h"
#endif

#include "data_utils.h"
#ifdef HAS_DS_TWR
#include "ds_twr.h"
#endif /*HAS_DS_TWR*/
#include "log.h"

static bool button1_short_proc(void) {
    bool res = false;
    LOG_WARNING(BUTTON, "BUTTON1 PressShort");
#ifdef HAS_DS_TWR
    bool on_off = toggle_bool(DsTwrItem.continuous);
    res = ds_twr_enable_continuous(&DsTwrItem, on_off);
#endif /*HAS_DS_TWR*/

    return res;
}

static bool button1_long_proc(void) {
    bool res = false;
    LOG_WARNING(BUTTON, "BUTTON1 PressLong");
#ifdef HAS_CORE
    res = core_reboot();
#endif
    return res;
}

const ButtonConfig_t ButtonConfig[] = {
    {
        .num = 1,
        .press_short_handler = button1_short_proc,
        .press_long_handler = button1_long_proc,
        .pad = {.port = PORT_A, .pin = 0},
        .active = GPIO_LVL_LOW,
        .name = "KEY",
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
