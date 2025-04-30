#include "button_config.h"

#ifndef HAS_BUTTON
#error "Add HAS_BUTTON"
#endif /*HAS_BUTTON*/

#include <stddef.h>

#ifdef HAS_CORE
#include "core_driver.h"
#endif

#include "data_utils.h"

#ifdef HAS_BT1026
#include "bt1026_drv.h"
#endif

#ifdef HAS_DS_TWR
#include "ds_twr.h"
#endif /*HAS_DS_TWR*/

static bool button1_short_proc(void) {
    bool res = false;
#ifdef HAS_DS_TWR
    bool on_off = toggle_bool(DsTwrItem.continuous);
    res = ds_twr_enable_continuous(&DsTwrItem, on_off);
#endif /*HAS_DS_TWR*/
    return res;
}

static bool button2_short_proc(void){
    bool res = false;
#ifdef HAS_BT1026
    res = bt1026_reboot(&Bt1026Item);
#endif /*HAS_BT1026*/
    return res;
}

static bool button3_short_proc(void){
    bool res = false;
    return res;
}

static bool button4_short_proc(void) {
    bool res = false;
    return res;
}

static bool button4_long_proc(void) {
    bool res = false;
#ifdef HAS_CORE
    res = core_reboot();
#endif
    return res;
}

const ButtonConfig_t ButtonConfig[ ] = {
   {.num=1,  .press_short_handler=button1_short_proc, .press_long_handler=NULL, .pad={.port=0, .pin=23}, .active=GPIO_LVL_LOW, .name="SW1", .valid=true, .debug_led_num=3,},
   {.num=2,  .press_short_handler=button2_short_proc, .press_long_handler=NULL, .pad={.port=0, .pin=24}, .active=GPIO_LVL_LOW, .name="SW2", .valid=true,.debug_led_num=3,},
   {.num=3,  .press_short_handler=button3_short_proc, .press_long_handler=NULL, .pad={.port=0, .pin= 8}, .active=GPIO_LVL_LOW, .name="SW3", .valid=true,.debug_led_num=3,},
   {.num=4,  .press_short_handler=button4_short_proc, .press_long_handler=button4_long_proc, .pad={.port=0, .pin= 9}, .active=GPIO_LVL_LOW, .name="SW4", .valid=true,.debug_led_num=3,},
};

ButtonHandle_t ButtonInstance[ ]={
 {.num=1, .valid=true,},
 {.num=2, .valid=true,},
 {.num=3, .valid=true,},
 {.num=4, .valid=true,},
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
