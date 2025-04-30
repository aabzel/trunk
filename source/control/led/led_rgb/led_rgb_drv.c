#include "led_rgb_drv.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifdef HAS_FREE_RTOS
#include <FreeRTOS.h>
#include <task.h>
#endif /*HAS_FREE_RTOS*/

#ifdef HAS_TI_RTOS_LED_RGB_TASK
#include <ti/sysbios/knl/Task.h>
#endif /*HAS_TI_RTOS_LED_RGB_TASK*/

#ifdef HAS_LOG
#include "log.h"
#include "log_utils.h"
#endif

#ifdef HAS_LED_DIAG
#include "led_diag.h"
#include "led_rgb_diag.h"
#endif
#include "led_general_const.h"

#ifdef HAS_MATH
#include "utils_math.h"
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#ifdef HAS_CLOCK
#include "clock.h"
#endif

#include "data_utils.h"

#ifdef HAS_GPIO
#include "gpio_drv.h"
#endif

#include "led_rgb_config.h"

#ifdef HAS_TIME
#include "none_blocking_pause.h"
#endif

#ifdef HAS_HEALTH_MONITOR
#include "health_monitor.h"
#endif /*HAS_HEALTH_MONITOR*/

#include "sys_config.h"

const LedRgbInfo_t LedRgbInfoLUT[]={
        {.color=COLOR_BLACK, .gpio_state={.red=0, .green=0, .blue=0,},},
        {.color=COLOR_RED,   .gpio_state={.red=1, .green=0, .blue=0,},},
        {.color=COLOR_YELLOW,.gpio_state={.red=1, .green=1, .blue=0,},},
        {.color=COLOR_GREEN, .gpio_state={.red=0, .green=1, .blue=0,},},
        {.color=COLOR_CYANIC,.gpio_state={.red=0, .green=1, .blue=1,},},
        {.color=COLOR_BLUE,  .gpio_state={.red=0, .green=0, .blue=1,},},
        {.color=COLOR_PURPLE,.gpio_state={.red=1, .green=0, .blue=1,},},
        {.color=COLOR_WHITE, .gpio_state={.red=1, .green=1, .blue=1,},},
};

uint32_t led_rgb_get_color_cnt(void){
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(LedRgbInfoLUT);
    return cnt;
}

uint8_t Color2RgbGpio(Color_t color){
    uint8_t byte = 0;
    uint32_t i = 0;
    uint32_t color_cnt = ARRAY_SIZE(LedRgbInfoLUT);
    for(i=0; i<color_cnt; i++) {
        if(color==LedRgbInfoLUT[i].color){
            byte =  LedRgbInfoLUT[i].gpio_state.byte;
            break;
        }
    }
    return byte;
}

// LedRgbHandle_t LedRgb[LED_RGB_COUNT];
GpioLogicLevel_t LedRgbLogicLevelZero2Voltage(GpioLogicLevel_t active){
    GpioLogicLevel_t voltage;
    switch((uint32_t)active){
    case GPIO_LVL_LOW: voltage=GPIO_LVL_HI; break;
    case GPIO_LVL_HI: voltage=GPIO_LVL_LOW; break;
    }
    return voltage;
}

GpioLogicLevel_t LedRgbLogicLevelHi2Voltage(GpioLogicLevel_t active){
    GpioLogicLevel_t voltage = active;
    return voltage;
}

LedRgbHandle_t* LedRgbGetNode(uint8_t num) {
    LedRgbHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = led_rgb_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(num == LedRgbItem[i].num) {
            if(LedRgbItem[i].valid) {
                Node = &LedRgbItem[i];
            }
        }
    }
    return Node;
}

const LedRgbConfig_t* LedRgbGetConfig(uint8_t num) {
    const LedRgbConfig_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = led_rgb_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(num == LedRgbConfig[i].num) {
            if(LedRgbConfig[i].valid) {
                Node = &LedRgbConfig[i];
                break;
            }
        }
    }
    return Node;
}

LedRgbState_t led_rgb_get_state_ll(LedRgbHandle_t* LedNodePtr){
    LedRgbState_t LedRgbState;
    LedRgbState.byte = 0;
    if(LedNodePtr) {
        bool res = true;

        GpioLogicLevel_t logic_level=GPIO_LVL_UNDEF;
        res= gpio_get_state(LedNodePtr->Pads.red.byte, &logic_level) ;
        if(res){
            LedRgbState.red = logic_level;
        }

        logic_level=GPIO_LVL_UNDEF;
        res= gpio_get_state(LedNodePtr->Pads.green.byte, &logic_level);
        if(res){
            LedRgbState.green = logic_level;
        }

        logic_level=GPIO_LVL_UNDEF;
        res= gpio_get_state(LedNodePtr->Pads.blue.byte, &logic_level);
        if(res){
            LedRgbState.blue = logic_level;
        }
        if(GPIO_LVL_LOW==LedNodePtr->active) {
            LedRgbState.red  =!LedRgbState.red ;
            LedRgbState.green=!LedRgbState.green;
            LedRgbState.blue =!LedRgbState.blue;
        }
    }
    return LedRgbState;
}

bool led_rgb_set_state_ll(LedRgbHandle_t* LedNodePtr, LedRgbState_t gpio_state){
    bool res = false;
    if(LedNodePtr) {
        res = true;
        if(GPIO_LVL_HI==LedNodePtr->active) {
            res = gpio_set_logic_level(LedNodePtr->Pads.red.byte, gpio_state.red) && res;
            res = gpio_set_logic_level(LedNodePtr->Pads.green.byte, gpio_state.green) && res;
            res = gpio_set_logic_level(LedNodePtr->Pads.blue.byte, gpio_state.blue) && res;
        }else {
            res = gpio_set_logic_level(LedNodePtr->Pads.red.byte, !gpio_state.red) && res;
            res = gpio_set_logic_level(LedNodePtr->Pads.green.byte, !gpio_state.green) && res;
            res = gpio_set_logic_level(LedNodePtr->Pads.blue.byte, !gpio_state.blue) && res;
        }
    }
    return res;
}

bool led_rgb_set_color_ll(LedRgbHandle_t* LedNodePtr, Color_t color){
    bool res = false;
    if(LedNodePtr) {
        LedRgbState_t gpio_state;
        gpio_state.byte = 0;
        gpio_state.byte  = Color2RgbGpio(color);
        res = true;
        if(COLOR_BLACK!=color) {
            LedNodePtr->set_color = color;
        }
        res=led_rgb_set_state_ll(LedNodePtr,   gpio_state);
    }
    return res;
}

bool led_rgb_test_one(uint8_t num) {
    bool res = false;
    LedRgbHandle_t* Node = LedRgbGetNode(num);
    if(Node){
        Color_t color=COLOR_UNDEF;
        for(color=0; color<COLOR_CNT; color++){
            res = led_rgb_set_color_ll(Node, color);
#ifdef HAS_TIME
            wait_ms(1000);
#endif
            res = led_rgb_set_color_ll(Node, COLOR_BLACK);
#ifdef HAS_TIME
            wait_ms(1000);
#endif
            res = true;
        }
    }
    return res;
}

bool led_rgb_test(void) {
    uint32_t i = 0;
    bool res = true;
    uint32_t cnt = led_rgb_get_cnt();
    uint32_t ok_cnt = 0;
    LOG_INFO(LED_RGB, "Test: %u", cnt);
    for(i = 1; i <= cnt; i++) {
        res = led_rgb_test_one(i) && res;
        if(res) {
            LOG_INFO(LED_RGB, "Test: LED:%u Ok", i);
            ok_cnt++;
        } else {
            LOG_ERROR(LED_RGB, "Test: LED:%u Err", i);
        }
    }

    if(ok_cnt==cnt) {
        res = true;
    }else{
        res = false;
    }
    LOG_INFO(LED_RGB, "TestDone");
    return res;
}

bool led_rgb_blink_ll(LedRgbHandle_t* LedNodePtr, uint32_t duration_ms, Color_t color) {
    bool res = false;
    if(LedNodePtr && (0 < duration_ms)) {
        LedNodePtr->prev.red = 0;
        LedNodePtr->prev.green = 0;
        LedNodePtr->prev.blue = 0;
        LedNodePtr->duration_ms = duration_ms;
        Color_t set_color = color;
        if(LED_MODE_BLINK==LedNodePtr->mode) {
            if(COLOR_YELLOW!=LedNodePtr->temp_color) {
                set_color = COLOR_YELLOW;
            }
        }else {
            LedNodePtr->mode = LED_MODE_BLINK;
        }
        LedNodePtr->temp_color = set_color;
        res = led_rgb_set_color_ll(LedNodePtr, set_color);
#ifdef HAS_TIME
        LedNodePtr->on_time_ms = time_get_ms32();
#endif
    }
    return res;
}

bool led_rgb_blink(uint8_t num, uint32_t duration_ms, Color_t color) {
    bool res = false;
    LedRgbHandle_t* LedRgbNode=LedRgbGetNode(num);
    if(LedRgbNode) {
        res= led_rgb_blink_ll(LedRgbNode, duration_ms, color) ;
    }
    return res;
}

Color_t RgbGpio2Color(uint8_t byte){
    Color_t color = COLOR_UNDEF;
    uint32_t i = 0;
    uint32_t color_cnt = ARRAY_SIZE(LedRgbInfoLUT);
    for(i=0; i<color_cnt; i++) {
        if((MASK_3BIT &LedRgbInfoLUT[i].gpio_state.byte)==(MASK_3BIT &byte)){
            color = LedRgbInfoLUT[i].color;
            break;
        }
    }

    return color;
}

bool led_rgb_set_color(uint8_t num, Color_t color){
    bool res = false;
#ifdef HAS_LED_RGB_DIAG
    LOG_DEBUG(LED_RGB,"%u Set Color %u=%s",num, color, Color2Str(color));
#endif /*HAS_LED_RGB_DIAG*/

    LedRgbHandle_t* LedNodePtr = LedRgbGetNode(num) ;
    if(LedNodePtr) {
        LedNodePtr->set_color = color;
       // res= led_rgb_set_color_ll( LedNodePtr, COLOR_BLACK);
        res= led_rgb_set_color_ll( LedNodePtr, color);
    }
    return res;
}

Color_t  led_rgb_get_color_ll(LedRgbHandle_t* LedNodePtr){
    Color_t color = COLOR_UNDEF;
    LOG_DEBUG(LED_RGB,"%u GetLL Color", LedNodePtr->num);
    if(LedNodePtr) {
        LedRgbState_t LedRgbState;
        LedRgbState.byte = 0;
        LedRgbState= led_rgb_get_state_ll( LedNodePtr);
        color = RgbGpio2Color(LedRgbState.byte);
    }
    return color;
}

Color_t  led_rgb_get_color(uint8_t num) {
    Color_t color = COLOR_UNDEF;
    LOG_DEBUG(LED_RGB,"%u Get Color",num);
    LedRgbHandle_t* LedNodePtr = LedRgbGetNode(num) ;
    if(LedNodePtr) {
        color = led_rgb_get_color_ll(LedNodePtr);
    }

    return color;
}

bool led_rgb_set_state(LedRgbHandle_t* LedNodePtr, GpioLogicLevel_t val){
    bool res = false;
    if(GPIO_LVL_HI==val){
        if(LED_MODE_BLINK==LedNodePtr->mode){
            res=led_rgb_set_color_ll( LedNodePtr, LedNodePtr->temp_color);
        }else{
            res=led_rgb_set_color_ll( LedNodePtr, LedNodePtr->set_color);
        }
    }else{
        res=led_rgb_set_color_ll( LedNodePtr, COLOR_BLACK);
    }
    return res;
}

static bool proc_led_rgb(LedRgbHandle_t* LedNodePtr) {
    bool res = false;
#ifdef HAS_LOG
    LOG_DEBUG(LED_RGB, "Proc %u", LedNodePtr->num);
#endif
    if(LedNodePtr) {
#ifdef HAS_TIME
        LedNodePtr->cur_time_ms = time_get_ms32();
#else
        LedNodePtr->cur_time_ms++;
#endif /*HAS_TIME*/
        uint8_t val = 0;
        switch((uint8_t)LedNodePtr->mode) {
        case LED_MODE_ON: {
            val = 1;
            res = true;
            //LedNodePtr->prev = GPIO_LVL_UNDEF;
        } break;
        case LED_MODE_OFF: {
            val = 0;
            //LedNodePtr->prev = GPIO_LVL_UNDEF;
            res = true;
        } break;
        case LED_MODE_BLINK: {
            uint32_t cur_duration_ms = 0;
            cur_duration_ms = LedNodePtr->cur_time_ms - LedNodePtr->on_time_ms;
            if(LedNodePtr->duration_ms < cur_duration_ms) {
                val = 0;
                const LedRgbConfig_t* LedConfNode = LedRgbGetConfig(LedNodePtr->num);
                LedNodePtr->mode = LedConfNode->mode;
                LedNodePtr->set_color= LedConfNode->set_color;
            } else {
                val = 1;
            }
            res = true;
        } break;
        case LED_MODE_PWM: {
            val = calc_pwm_sample_num(LedNodePtr->cur_time_ms * 1000, LedNodePtr->period_ms, LedNodePtr->duty, LedNodePtr->phase_ms);
            res = true;
        } break;
        default: {
            res = false;
        } break;
        }

        if(res) {
            res = led_rgb_set_state(LedNodePtr, val);
        } else {
        }
    }
    return res;
}

bool proc_led_rgbs(void) {
    uint32_t cnt = led_rgb_get_cnt();
#ifdef HAS_LOG
    LOG_DEBUG(LED_RGB, "LedProc Cnt: %u", cnt);
#endif
    bool res = true;
    uint16_t i = 0;
    for(i = 1; i <= cnt; i++) {
        LedRgbHandle_t* Node = LedRgbGetNode(i);
        if(Node) {
            res = proc_led_rgb(Node) && res;
        } else {
            res = false;
        }
    }
    return res;
}

bool led_rgb_on(LedRgbHandle_t* LedNodePtr) {
    bool res = false;
    if(LedNodePtr) {
        res = true;
        LedNodePtr->prev.red = 0;
        LedNodePtr->prev.green = 0;
        LedNodePtr->prev.blue = 0;
        LedNodePtr->mode = LED_MODE_ON;
    }
    return res;
}

bool led_rgb_off(LedRgbHandle_t* LedNodePtr) {
    bool res = false;
    if(LedNodePtr) {
        res = true;
        LedNodePtr->prev.red = 0;
        LedNodePtr->prev.green = 0;
        LedNodePtr->prev.blue = 0;
        LedNodePtr->mode = LED_MODE_OFF;
    }
    return res;
}

#ifdef HAS_FREE_RTOS

static void led_rgb_thread(void* arg) {
    for(;;) {
        proc_led_rgbs();
        vTaskDelay(50 / portTICK_RATE_MS);
    }
}

void led_rgb_create_task(void) { xTaskCreate(led_rgb_thread, "LED_RGB", 5000, NULL, 0, NULL); }
#endif /*HAS_FREE_RTOS*/

#ifdef HAS_TI_RTOS_LED_RGB_TASK
/*
 *
 * @brief   Application task entry point for the Project Zero.
 *
 * @param   a0, a1 - not used.
 */
static void led_rgb_thread(UArg a0, UArg a1) {

    for(;;) {
        proc_led_rgbs();
        /*Wait 100 ms*/
        Task_sleep(50);
    }
}

#define LED_RGB_TASK_STACK_SIZE 2048
#define LED_RGB_TASK_PRIORITY 2
uint8_t LedRgbTaskStack[LED_RGB_TASK_STACK_SIZE];
Task_Struct led_rgbTask;

bool led_rgb_create_tirtos_task(void) {
    bool res = true;
    Task_Params taskParams;

    Task_Params_init(&taskParams);
    taskParams.stack = LedRgbTaskStack;
    taskParams.stackSize = LED_RGB_TASK_STACK_SIZE;
    taskParams.priority = LED_RGB_TASK_PRIORITY;

    Task_construct(&led_rgbTask, led_rgb_thread, &taskParams, NULL);
    return res;
}
#endif /*HAS_TI_RTOS_LED_RGB_TASK*/

bool led_rgb_pwm(uint8_t num, double freq_hz, uint8_t duty) {
    bool res = true;
    LedRgbHandle_t* Node = LedRgbGetNode(num);
    if(Node) {
        Node->prev.red = 0;
        Node->prev.green = 0;
        Node->prev.blue = 0;
        Node->duty = duty;
        Node->mode = LED_MODE_PWM;
        Node->period_ms = freq2period_ms(freq_hz);
        Node->phase_ms = 0;
    }
    return res;
}

bool led_rgb_init_one(uint32_t num ) {
    bool res = true;

#ifdef HAS_LOG
    LOG_INFO(LED_RGB, "TryInit %u", num);
#endif /*HAS_LOG*/

    LedRgbHandle_t* Node = LedRgbGetNode(num);
    if(Node) {
        const LedRgbConfig_t* Config = LedRgbGetConfig(num);
        if(Config) {
            LOG_INFO(LED_RGB, "Init %u", num);
            Node->active = Config->active;
            Node->prev.red = 0;
            Node->prev.green = 0;
            Node->prev.blue = 0;
            Node->duty = Config->duty;
            Node->period_ms = Config->period_ms;
            Node->phase_ms = Config->phase_ms;
            Node->mode = Config->mode;
            Node->Pads = Config->Pads;
            Node->set_color = Config->set_color;

            res = led_rgb_set_color_ll(Node, Config->set_color);
            led_rgb_test_one(num);
        }
        Node->init = true;
        res = true;
    }

#ifdef HAS_FREE_RTOS
   // led_rgb_create_task();
#endif
#ifdef HAS_TI_RTOS_LED_RGB_TASK
    //led_rgb_create_tirtos_task();
#endif /*HAS_TI_RTOS*/
    return res;
}

bool led_rgb_init(void) {
    bool res = true;
    uint32_t cnt = led_rgb_get_cnt();
#ifdef HAS_LOG
    LOG_INFO(LED_RGB, "Init Cnt:%u", cnt);
#endif /*HAS_LOG*/
    uint32_t num = 0;

    for(num = 1; num <= cnt; num++) {
        LedRgbHandle_t* Node = LedRgbGetNode(num);
        if(Node) {
            const LedRgbConfig_t* Config = LedRgbGetConfig(num);
            if(Config) {
                LOG_INFO(LED_RGB, "Init %u", num);
                Node->active = Config->active;
                Node->prev.red = 0;
                Node->prev.green = 0;
                Node->prev.blue = 0;
                Node->duty = Config->duty;
                Node->period_ms = Config->period_ms;
                Node->phase_ms = Config->phase_ms;
                Node->mode = Config->mode;
                Node->Pads = Config->Pads;
                Node->set_color = Config->set_color;
                res = led_rgb_set_color_ll(Node, Config->set_color);
            }
            Node->init = true;
            res = true;
        }
    }
#ifdef HAS_FREE_RTOS
   // led_rgb_create_task();
#endif
#ifdef HAS_TI_RTOS_LED_RGB_TASK
    //led_rgb_create_tirtos_task();
#endif /*HAS_TI_RTOS*/
    return res;
}
