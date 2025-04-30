#include "button_drv.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifdef HAS_FREE_RTOS
#include <FreeRTOS.h>
#include <task.h>
#endif /*HAS_FREE_RTOS*/

#include "button_config.h"
#include "code_generator.h"
#include "data_utils.h"
#include "gpio_mcal.h"
#include "log.h"
#include "sys_config.h"
#include "time_mcal.h"

#ifdef HAS_LED_MONO
#include "led_mono_drv.h"
#endif

#ifdef HAS_FLASH
#include "flash_mcal.h"
#endif

COMPONENT_GET_NODE(Button, button)
COMPONENT_GET_CONFIG(Button, button)

static bool button_run_callback(ButtonHandle_t* Node, ButtonPressType_t press_type) {
    bool res = false;
    if(Node) {
        ButtonIsrHandler_t press_handler = NULL;
        switch((uint8_t)press_type) {
        case BUTTON_PRESS_SHORT: {
#ifdef HAS_GPIO_DIAG
            LOG_DEBUG(BUTTON, "%u ShortPressedProc %s, %u ms", Node->num, GpioPad2Str(Node->pad.byte), Node->time_ms);
#endif
            press_handler = Node->press_short_handler;
        } break;

        case BUTTON_PRESS_LONG: {
#ifdef HAS_GPIO_DIAG
            LOG_DEBUG(BUTTON, "%u LongPressedProc %s, %u ms", Node->num, GpioPad2Str(Node->pad.byte), Node->time_ms);
#endif
            press_handler = Node->press_long_handler;
        } break;
        }

        if(press_handler) {
            res = is_flash_addr((uint32_t)press_handler);
            if(res) {
                LOG_DEBUG(BUTTON, "HandlerInOfFlash 0x%p", press_handler);
                res = press_handler();
                Node->handler_cnt++;
            } else {
                LOG_ERROR(BUTTON, "HandlerOutOfFlash 0x%p", press_handler);
                Node->err_cnt++;
            }
        } else {
#ifdef HAS_BUTTON_DIAG
            LOG_ERROR(BUTTON, "NoHandler4 %s", ButtonPressType2Str(press_type));
#endif
        }
    }
    return res;
}

static const ButtonState_t TransferLookUpTable[3][3] = {
    [BUTTON_STATE_UNPRESSED][BUTTON_IN_PASSIVE] = BUTTON_STATE_UNPRESSED,
    [BUTTON_STATE_UNPRESSED][BUTTON_IN_ACTIVE] = BUTTON_STATE_PRESSED,
    [BUTTON_STATE_UNPRESSED][BUTTON_IN_TIME_OUT] = BUTTON_STATE_UNPRESSED,
    [BUTTON_STATE_PRESSED][BUTTON_IN_PASSIVE] = BUTTON_STATE_UNPRESSED,
    [BUTTON_STATE_PRESSED][BUTTON_IN_ACTIVE] = BUTTON_STATE_PRESSED,
    [BUTTON_STATE_PRESSED][BUTTON_IN_TIME_OUT] = BUTTON_STATE_PRESSED_PROCESSED,
    [BUTTON_STATE_PRESSED_PROCESSED][BUTTON_IN_PASSIVE] = BUTTON_STATE_UNPRESSED,
    [BUTTON_STATE_PRESSED_PROCESSED][BUTTON_IN_ACTIVE] = BUTTON_STATE_PRESSED_PROCESSED,
    [BUTTON_STATE_PRESSED_PROCESSED][BUTTON_IN_TIME_OUT] = BUTTON_STATE_PRESSED_PROCESSED,
};

static bool button_action_nop(ButtonHandle_t* Node) {
    bool res = true;
    return res;
}

static bool button_action_stop_timer(ButtonHandle_t* Node) {
    bool res = false;
    if(Node) {
#ifdef HAS_GPIO_DIAG
        LOG_DEBUG(BUTTON, "LongPressEnd %s, %u ms", GpioPad2Str(Node->pad.byte), Node->time_ms);
#endif
        Node->time_ms = 0;
        res = true;
    }
    return res;
}

static bool button_action_reset_timer(ButtonHandle_t* Node) {
    bool res = false;
    if(Node) {
        Node->time_ms = 0;
        res = true;
    }
    return res;
}

static bool button_short_press_timer(ButtonHandle_t* Node) {
    bool res = false;
    if(Node) {
#ifdef HAS_LED_MONO
        led_mono_blink(Node->debug_led_num, 50);
#endif
        Node->short_pres_cnt++;
#ifdef HAS_GPIO_DIAG
        LOG_DEBUG(BUTTON, "ShortPress %s, %u ms", GpioPad2Str(Node->pad.byte), Node->time_ms);
#endif
        // res=Node->press_short_handler();
        res = button_run_callback(Node, BUTTON_PRESS_SHORT);
        Node->time_ms = 0;
    }
    return res;
}

static bool button_long_press_timer(ButtonHandle_t* Node) {
    bool res = false;
    if(Node) {
#ifdef HAS_LED_MONO
        led_mono_blink(Node->debug_led_num, 100);
#endif
        Node->long_pres_cnt++;
#ifdef HAS_GPIO_DIAG
        LOG_DEBUG(BUTTON, "LongPress %s, %u ms", GpioPad2Str(Node->pad.byte), Node->time_ms);
#endif
        res = button_run_callback(Node, BUTTON_PRESS_LONG);
        // res=Node->press_long_handler();
    }
    return res;
}

static const ButtonActionHandler_t ActionLookUpTable[3][3] = {
    [BUTTON_STATE_UNPRESSED][BUTTON_IN_PASSIVE] = button_action_nop,
    [BUTTON_STATE_UNPRESSED][BUTTON_IN_ACTIVE] = button_action_reset_timer,
    [BUTTON_STATE_UNPRESSED][BUTTON_IN_TIME_OUT] = button_action_nop,

    [BUTTON_STATE_PRESSED][BUTTON_IN_PASSIVE] = button_short_press_timer,
    [BUTTON_STATE_PRESSED][BUTTON_IN_ACTIVE] = button_action_nop,
    [BUTTON_STATE_PRESSED][BUTTON_IN_TIME_OUT] = button_long_press_timer,

    [BUTTON_STATE_PRESSED_PROCESSED][BUTTON_IN_PASSIVE] = button_action_stop_timer,
    [BUTTON_STATE_PRESSED_PROCESSED][BUTTON_IN_ACTIVE] = button_action_nop,
    [BUTTON_STATE_PRESSED_PROCESSED][BUTTON_IN_TIME_OUT] = button_action_nop,
};

bool ButtonStateToOnOff(ButtonState_t state) {
    bool res = false;
    switch((uint8_t)state) {
    case BUTTON_STATE_UNPRESSED:
        res = false;
        break;
    case BUTTON_STATE_PRESSED:
        res = true;
        break;
    case BUTTON_STATE_PRESSED_PROCESSED:
        res = true;
        break;
    }
    return res;
}

ButtonState_t button_get(uint8_t num) {
    ButtonState_t state = BUTTON_STATE_UNDEF;
    ButtonHandle_t* Node = ButtonGetNode(num);
    if(Node) {
        GpioLogicLevel_t logic_level = GPIO_LVL_UNDEF;
        bool res = false;
        res = gpio_get_state(Node->pad.byte, &logic_level);
        if(res) {
            if(Node->active == logic_level) {
                state = BUTTON_STATE_PRESSED;
            } else {
                state = BUTTON_STATE_UNPRESSED;
            }
        }
    }
    return state;
}

static bool button_get_input_ll(ButtonHandle_t* const Node) {
    bool res = false;
    GpioLogicLevel_t logic_level = GPIO_LVL_UNDEF;
    res = gpio_get_state(Node->pad.byte, &logic_level);
    if(res) {
#ifdef HAS_GPIO_DIAG
        LOG_DEBUG(BUTTON, "Read %s %s", GpioPad2Str(Node->pad.byte), GpioLevel2Str(logic_level));
#endif
        res = false;
        if(logic_level == Node->active) {
#ifdef HAS_GPIO_DIAG
            LOG_DEBUG(BUTTON, "Pressed %s %s", GpioPad2Str(Node->pad.byte), GpioLevel2Str(logic_level));
#endif
            Node->input = BUTTON_IN_ACTIVE;
            res = true;
            Node->time_ms += (uint32_t)USEC_2_MSEC(BUTTON_POLL_PERIOD_US);
            if(BUTTON_LONG_PRESS_TIMEOUT_MS < Node->time_ms) {
                Node->input = BUTTON_IN_TIME_OUT;
                res = true;
            }
        } else {
            Node->input = BUTTON_IN_PASSIVE;
            res = true;
        }
    } else {
#ifdef HAS_BUTTON_DIAG
        LOG_ERROR(BUTTON, "GpioGetErr %s %s", GpioPad2Str(Node->pad.byte), ButtonInput2Str(Node->input));
#endif
    }
#ifdef HAS_BUTTON_DIAG
    LOG_DEBUG(BUTTON, "Pad:%s Input %s", GpioPad2Str(Node->pad.byte), ButtonInput2Str(Node->input));
#endif
    return res;
}

static bool button_proc_one(uint8_t num) {
    bool res = false;
    ButtonHandle_t* Node = ButtonGetNode(num);
    if(Node) {
        ButtonState_t new_state = BUTTON_STATE_UNDEF;
        res = button_get_input_ll(Node);
        if(res) {
            new_state = TransferLookUpTable[Node->state][Node->input];
            if(new_state != Node->state) {
#ifdef HAS_BUTTON_DIAG
                LOG_DEBUG(BUTTON, "BTN%u %s %s->%s", Node->num, GpioPad2Str(Node->pad.byte),
                          ButtonState2Str(Node->state), ButtonState2Str(new_state));
#endif
            }

            if(Node->proc_handler) {
                /*some buttons has back light. Here a handler for it*/
                res = Node->proc_handler();
            }
            ButtonActionHandler_t ActionHandler = ActionLookUpTable[Node->state][Node->input];
            res = ActionHandler(Node);
            Node->state = new_state;
        } else {
            LOG_ERROR(BUTTON, "%BTNu GetErr", num);
        }
    } else {
        LOG_DEBUG(BUTTON, "BTN_%u NodeErr", num);
    }
    return res;
}

static GpioPullMode_t ButtonActiveToPull(GpioLogicLevel_t active) {
    GpioPullMode_t button_pull = GPIO__PULL_UNDEF;
    switch(active) {
    case GPIO_LVL_LOW: {
        button_pull = GPIO__PULL_UP;
    } break;

    case GPIO_LVL_HI: {
        button_pull = GPIO__PULL_DOWN;
    } break;
    default:
        break;
    }

    return button_pull;
}

static bool button_init_custom(void) {
    bool res = true;
    return res;
}

static bool button_init_one(uint32_t num) {
    bool res = true;

    const ButtonConfig_t* Config = ButtonGetConfig(num);
    if(Config) {
#ifdef HAS_BUTTON_DIAG
        ButtonConfigDiag(Config);
#endif
        ButtonHandle_t* Node = ButtonGetNode(num);
        if(Node) {
            LOG_INFO(BUTTON, "%u Init", num);
            Node->debug_led_num = Config->debug_led_num;
            Node->press_short_handler = Config->press_short_handler;
            Node->press_long_handler = Config->press_long_handler;
            Node->proc_handler = Config->proc_handler;
            Node->active = Config->active;
            Node->pad.byte = Config->pad.byte;

            Node->short_pres_cnt = 0;
            Node->long_pres_cnt = 0;
            Node->err_cnt = 0;
            Node->state = BUTTON_STATE_UNPRESSED;
            Node->input = BUTTON_IN_UNDEF;
            res = gpio_dir_set(Node->pad.byte, GPIO_DIR_IN);

            GpioPullMode_t button_pull = ButtonActiveToPull(Config->active);
            res = gpio_pull_set(Node->pad, button_pull);

#if 0
                switch(Config->active){
                    case GPIO_LVL_LOW: {
                        res = gpio_pull_set(Node->pad.byte, GPIO__PULL_UP);
                    }break;

                    case GPIO_LVL_HI: {
                        res = gpio_pull_set(Node->pad.byte, GPIO__PULL_DOWN);
                    }break;
                default: break;
                }
#endif
        }
        Node->init = true;
        res = true;
    }

    return res;
}

bool button_press(uint8_t num, ButtonPressType_t press_type) {
    bool res = true;
    ButtonHandle_t* Node = ButtonGetNode(num);
    if(Node) {
        res = button_run_callback(Node, press_type);
    }
    return res;
}

#ifdef HAS_FREE_RTOS
void button_thread(void* arg) {
    for(;;) {
        button_proc();
        vTaskDelay(50 / portTICK_RATE_MS);
    }
}
#endif /*HAS_FREE_RTOS*/

COMPONENT_INIT_PATTERT(BUTTON, BUTTON, button)
COMPONENT_PROC_PATTERT(BUTTON, BUTTON, button)
