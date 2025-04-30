#include "button_config.h"

#ifndef HAS_BUTTON
#error "Add HAS_BUTTON"
#endif /*HAS_BUTTON*/

#include "data_utils.h"

#ifdef HAS_SI4703
#include "si4703_drv.h"
#endif

#ifdef HAS_CORE
#include "core_driver.h"
#endif

#include "log.h"

#ifdef HAS_DS_TWR
#include "ds_twr.h"
#endif /*HAS_DS_TWR*/

static bool button1_short_proc(void) {
    bool res = true;
    LOG_WARNING(BUTTON, "BUTTON1 PressShort");
#ifdef HAS_DS_TWR
    //bool on_off = toggle_bool(DsTwrItem.continuous);
    res = ds_twr_enable_continuous(&DsTwrItem, true);
#endif /*HAS_DS_TWR*/
    return res;
}

static bool button1_long_proc(void) {
    bool res = true;
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
        .pad = {.port = PORT_C, .pin = 13},
        .active = GPIO_LVL_LOW,
        .name = "B1",
        .valid = true,
        .debug_led_num = 1,
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
