#include "button_config.h"

#ifndef HAS_BUTTON
#error "Add HAS_BUTTON"
#endif

#include "data_utils.h"

#ifdef HAS_REC_PLAY
#include "rec_play_mcal.h"
#endif

#ifdef HAS_BOOTLOADER
#include "bootloader.h"
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

#ifdef HAS_REC_PLAY
    char file_name[40]={0};
    uint32_t up_time_ms = time_get_ms32();
    snprintf(file_name, sizeof(file_name), "RbUt%u_10s.wav", up_time_ms);
    res = rec_play_start(1,   file_name, 10.0);
#endif
    return res;
}

const ButtonConfig_t ButtonConfig[ ] = {
    {
        .debug_led_num = 2,
        .num = 1,
        .proc_handler = NULL,
        .press_long_handler = button1_proc,
        .press_short_handler = button1_proc,
        .pad={.port=PORT_A, .pin=0,},
        .active = GPIO_LVL_HI,
        .name = "K1",
        .valid = true,
    },
};

ButtonHandle_t ButtonInstance[ ] = {
   {    .num=1,    .valid=true,},
};

COMPONENT_GET_CNT(Button,button)

