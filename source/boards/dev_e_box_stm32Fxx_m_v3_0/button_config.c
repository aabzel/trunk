#include "button_config.h"

#ifndef HAS_BUTTON
#error "Add HAS_BUTTON"
#endif /*HAS_BUTTON*/

#include "data_utils.h"

#ifdef HAS_BOOTLOADER
#include "boot_driver.h"
#endif

#ifdef HAS_SI4703
#include "si4703_drv.h"
#endif

static bool button1_proc(void) {
    bool res = false;

#ifdef HAS_SI4703
    res = si4703_fm_seek_start( SEEK_DIR_UP, SEEK_END_WRAP);
#endif

#ifdef HAS_BOOTLOADER
    res = boot_launch_app(BOOT_CMD_LAUNCH_APP);
#endif
	return res;
}

const ButtonConfig_t ButtonConfig[ ] = {
    {
    		.num=1,
    		.press_short_handler = button1_proc,
    		.pad={.port=PORT_A, .pin=0,},
			.active = GPIO_LVL_HI,
			.name = "K1",
			.valid = true,
    },
};

ButtonHandle_t ButtonInstance[ ]={
   {
    .num=1,
    .valid=true,},
};

uint32_t button_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(ButtonInstance);
    cnt2 = ARRAY_SIZE(ButtonConfig);
    if (cnt1==cnt2) {
        cnt = cnt1;
    }
    return cnt;
} 
