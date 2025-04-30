#include "button_config.h"

#ifndef HAS_BUTTON
#error "Add HAS_BUTTON"
#endif /*HAS_BUTTON*/

#include "data_utils.h"
#include "log.h"

static bool button1_proc(void){
    LOG_INFO(BUTTON, "%s()", __FUNCTION__);
	return true;}

static bool button2_proc(void){
    LOG_INFO(BUTTON, "%s()", __FUNCTION__);
	return true;}
static bool button3_proc(void){
    LOG_INFO(BUTTON, "%s()", __FUNCTION__);
	return true;}
static bool button4_proc(void){
    LOG_INFO(BUTTON, "%s()", __FUNCTION__);
	return true;}

static bool button5_proc(void){
    LOG_INFO(BUTTON, "%s()", __FUNCTION__);
	return true;}

const ButtonConfig_t ButtonConfig[ ] = {
   {.num=1,  .press_short_handler=button1_proc, .pad={.port=0, .pin=2}, .active=GPIO_LVL_LOW, .name="SW1", .valid=true,},
   {.num=2,  .press_short_handler=button2_proc, .pad={.port=0, .pin=3}, .active=GPIO_LVL_LOW, .name="SW2", .valid=true,},
   {.num=3,  .press_short_handler=button3_proc, .pad={.port=0, .pin=4}, .active=GPIO_LVL_LOW, .name="SW3", .valid=true,},
   {.num=4,  .press_short_handler=button4_proc, .pad={.port=0, .pin=6}, .active=GPIO_LVL_LOW, .name="SW4", .valid=true,},
   {.num=5,  .press_short_handler=button5_proc, .pad={.port=0, .pin=5}, .active=GPIO_LVL_LOW, .name="SW5", .valid=true,},
};

ButtonHandle_t ButtonInstance[ ]={
 {.num=1, .valid=true,},
 {.num=2, .valid=true,},
 {.num=3, .valid=true,},
 {.num=4, .valid=true,},
 {.num=5, .valid=true,},
};

uint32_t button_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(ButtonInstance);
    cnt2 = ARRAY_SIZE(ButtonConfig);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
} 
