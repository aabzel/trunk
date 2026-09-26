#include "button_config.h"

#ifndef HAS_BUTTON
#error "Add HAS_BUTTON"
#endif

#include "data_utils.h"
#include "test_sw_uart.h"

#ifdef HAS_SONAR
#include "sonar.h"
#endif

#ifdef HAS_REC_PLAY
#include "rec_play_mcal.h"
#endif

#ifdef HAS_BOOTLOADER
#include "bootloader.h"
#endif

#ifdef HAS_SI4703
#include "si4703_drv.h"
#endif

#ifdef HAS_WM8731
#include "wm8731_drv.h"
#endif

static bool button1_proc(void) {
    bool res = false;

    res = test_sw_uart_tx() ;
#ifdef HAS_SONAR
    res = sonar_position_next(SONAR_NUM_CHIRP);
    //res = sonar_position_add(SONAR_NUM_CHIRP,+0.10);
#endif

#if 0
    char file_name[40]={0};
    uint32_t up_time_ms = time_get_ms32();
    snprintf(file_name, sizeof(file_name), "RbUt%u_10s.wav", up_time_ms);
    res = rec_play_start(1,   file_name, 10.0);
#endif
    return res;
}

static bool button2_proc(void) {
    bool res = false;
    res = test_sw_uart_tx() ;
#ifdef HAS_SONAR
    res = sonar_position_prev(SONAR_NUM_CHIRP);
    //res = sonar_position_add(SONAR_NUM_CHIRP,-0.10);
#endif
    return res;
}

static bool button3_proc(void) {
    bool res = false;
    res = test_sw_uart_tx() ;
#ifdef HAS_WM8731
    res = wm8731_mcal_init();
#endif
    return res;
}

/*
https://stm32-base.org/boards/STM32F407ZGT6-STM32F4XX.html
*/
const ButtonConfig_t ButtonConfig[ ] = {
    {
        .debug_led_num = 1,
        .num = 1,
        .proc_handler = NULL,
        .press_long_handler = button1_proc,
        .press_short_handler = button1_proc,
        .pad={.port = PORT_E, .pin = 4,},
        .active = GPIO_LVL_LOW,
        .name = "K0",
        .valid = true,
    },
    {
        .debug_led_num = 1,
        .num = 2,
        .proc_handler = NULL,
        .press_long_handler = button2_proc,
        .press_short_handler = button2_proc,
        .pad={.port = PORT_E, .pin = 3,},
        .active = GPIO_LVL_LOW,
        .name = "K1",
        .valid = true,
    },
    {
        .debug_led_num = 1,
        .num = 3,
        .proc_handler = NULL,
        .press_long_handler = button3_proc,
        .press_short_handler = button3_proc,
        .pad={.port = PORT_A, .pin = 0,},
        .active = GPIO_LVL_HI,
        .name = "WK_UP",
        .valid = true,
    },
};

ButtonHandle_t ButtonInstance[ ] = {
   {    .num = 1,    .valid = true,},
   {    .num = 2,    .valid = true,},
   {    .num = 3,    .valid = true,},
};

COMPONENT_GET_CNT(Button,button)

