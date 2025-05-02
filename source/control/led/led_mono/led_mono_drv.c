#include "led_mono_drv.h"

#include <stddef.h>
#include <string.h>

#include "std_includes.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_LED_MONO_DIAG
#include "led_mono_diag.h"
#endif

#ifdef HAS_GPIO_DIAG
#include "gpio_diag.h"
#endif

#ifdef HAS_MATH
#include "utils_math.h"
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#ifdef HAS_LED_DIAG
#include "led_diag.h"
#endif

#ifdef HAS_TIMER
#include "timer_mcal.h"
#endif

#ifdef HAS_TEST_LED_MONO
#include "test_led_mono.h"
#endif

#ifdef HAS_CLOCK
#include "clock.h" //TODO DEL
#endif
#include "data_utils.h"
#include "gpio_mcal.h"
#ifdef HAS_TIME
#include "none_blocking_pause.h"
#endif
#ifdef HAS_HEALTH_MONITOR
#include "health_monitor.h"
#endif /*HAS_HEALTH_MONITOR*/
#include "sys_config.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif

#include "code_generator.h"

COMPONENT_GET_NODE(LedMono, led_mono)
COMPONENT_GET_CONFIG(LedMono, led_mono)

static GpioLogicLevel_t LedLogicLevelZero2Voltage(GpioLogicLevel_t active) {
    GpioLogicLevel_t voltage = GPIO_LVL_UNDEF;
    switch((uint32_t)active) {
    case GPIO_LVL_LOW:
        voltage = GPIO_LVL_HI;
        break;
    case GPIO_LVL_HI:
        voltage = GPIO_LVL_LOW;
        break;
    }
    return voltage;
}

static GpioLogicLevel_t LedLogicLevelHi2Voltage(GpioLogicLevel_t active) {
    GpioLogicLevel_t voltage = active;
    return voltage;
}

static GpioLogicLevel_t LedLogicLevel2Voltage(uint8_t val, GpioLogicLevel_t active) {
    GpioLogicLevel_t voltage = GPIO_LVL_UNDEF;
    switch((uint32_t)val) {
    case GPIO_LVL_LOW:
        voltage = LedLogicLevelZero2Voltage(active);
        break;
    case GPIO_LVL_HI:
        voltage = LedLogicLevelHi2Voltage(active);
        break;
    }
    return voltage;
}

#ifdef HAS_LED_EXT
static GpioLogicLevel_t VoltageLow2LogicLevel(GpioLogicLevel_t active) {
    GpioLogicLevel_t LogicLevel = GPIO_LVL_UNDEF;
    switch((uint32_t)active) {
    case GPIO_LVL_LOW:
        LogicLevel = GPIO_LVL_HI;
        break;
    case GPIO_LVL_HI:
        LogicLevel = GPIO_LVL_LOW;
        break;
    }
    return LogicLevel;
}
#endif

#ifdef HAS_LED_EXT
static GpioLogicLevel_t VoltageHi2LogicLevel(GpioLogicLevel_t active) {
    GpioLogicLevel_t LogicLevel = GPIO_LVL_UNDEF;
    switch((uint32_t)active) {
    case GPIO_LVL_LOW:
        LogicLevel = GPIO_LVL_LOW;
        break;
    case GPIO_LVL_HI:
        LogicLevel = GPIO_LVL_HI;
        break;
    }
    return LogicLevel;
}
#endif

#ifdef HAS_LED_EXT
static GpioLogicLevel_t Voltage2LedLogicLevel(uint8_t voltage, GpioLogicLevel_t active) {
    GpioLogicLevel_t level = GPIO_LVL_UNDEF;
    switch((uint32_t)voltage) {
    case GPIO_LVL_LOW:
        level = VoltageLow2LogicLevel(active);
        break;
    case GPIO_LVL_HI:
        level = VoltageHi2LogicLevel(active);
        break;
    }
    return level;
}
#endif

#ifdef HAS_LED_EXT
LedMonoHandle_t* LedPad2Node(uint8_t pad_num) {
    LedMonoHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = led_mono_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(pad_num == LedMonoInstance[i].pad.byte) {
            if(LedMonoInstance[i].valid) {
                Node = &LedMonoInstance[i];
                break;
            }
        }
    }
    return Node;
}
#endif

static bool led_set_state_ll(LedMonoHandle_t* const Node, const GpioLogicLevel_t des_logic_level) {
    bool res = false;
    if(Node) {
#ifdef HAS_LOG
        LOG_DEBUG(LED_MONO, "LED_%u,Set,Val:%u", Node->num, des_logic_level);
#endif
        GpioLogicLevel_t voltage = LedLogicLevel2Voltage(des_logic_level, Node->active);
        res = gpio_logic_level_set(Node->pad, voltage);
        Node->prev = des_logic_level;
    }
    return res;
}

#ifdef HAS_LED_EXT
static GpioLogicLevel_t led_get_state_ll(LedMonoHandle_t* Node) {
    bool res = false;
#ifdef HAS_LOG
    LOG_PARN(LED_MONO, "%u GetLL", Node->num);
#endif
    GpioLogicLevel_t logic_level = GPIO_LVL_UNDEF;
    if(Node) {
        GpioLogicLevel_t voltage_level = GPIO_LVL_UNDEF;
        res = gpio_get_state(Node->pad.byte, &voltage_level);
        if(res) {
            logic_level = Voltage2LedLogicLevel(voltage_level, Node->active);
#ifdef HAS_GPIO_DIAG
            LOG_DEBUG(LED_MONO, "%u GetLL Vol:%s Lev:%s", Node->num, GpioLevel2Str(voltage_level),
                      GpioLevel2Str(logic_level));
#endif
        }
    }
    return logic_level;
}
#endif

bool led_set_state(uint8_t pad_num, GpioLogicLevel_t des_logic_level) {
    bool res = false;
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(LED_MONO, "Set:%s,Val:%u", GpioPad2Str(pad_num), des_logic_level);
#endif
    LedMonoHandle_t* Node = NULL;
    Node = LedPad2Node(pad_num);
    if(Node) {
        res = led_set_state_ll(Node, des_logic_level);
    }
    return res;
}

#ifndef HAS_MATH
static uint8_t led_calc_pwm_sample_num(int32_t time_us, uint32_t period_ms, uint32_t duty) {
    uint8_t val = 0;
    if(100 < duty) {
        duty = 100;
    }

    int32_t time_saw = time_us % period_ms;
    int32_t treshold = (period_ms * duty) / 100;
    if(treshold < time_saw) {
        val = 0;
    } else {
        val = 1;
    }

    return val;
}
#endif

bool led_mono_on(LedMonoHandle_t* const Node) {
    bool res = false;
    if(Node) {
        res = true;
        res = led_set_state_ll(Node, GPIO_LVL_HI); // Error
        Node->mode = LED_MODE_ON;                  // Error
        Node->prev = GPIO_LVL_UNDEF;               // Error
#ifdef HAS_GENERIC
#endif
    } else {
#ifdef HAS_LOG
        LOG_ERROR(LED_MONO, "LED%u OnNodeErr", Node->num);
#endif
    }
    return res;
}

// error
bool led_mono_off(LedMonoHandle_t* const Node) {
    bool res = false;
    if(Node) {
        res = true;
#ifdef HAS_GENERIC
        Node->prev = GPIO_LVL_UNDEF;                // hang-up error in optimization
        Node->mode = LED_MODE_OFF;                  // hang-up error in optimization
        res = led_set_state_ll(Node, GPIO_LVL_LOW); // hang-up error in optimization
#endif
    } else {
#ifdef HAS_LOG
        LOG_ERROR(LED_MONO, "OffNodeErr");
#endif
    }
    return res;
}

bool led_mono_toggle(const uint8_t num) {
    bool res = false;
    LedMonoHandle_t* Node = LedMonoGetNode(num);
    if(Node) {
        res = gpio_toggle(Node->pad);
    }
    return res;
}

#if 1
bool led_mono_ctrl(const uint8_t num, const bool on_off) {
    bool res = false;
    LedMonoHandle_t* Node = LedMonoGetNode(num);
    if(Node) {
        if(on_off) {
            res = led_mono_on(Node); // hang-up error in optimization
        } else {
            res = led_mono_off(Node); // hang-up error in optimization
        }
    }
    return res;
}
#endif

#if 0

static void led_thread(void* arg) {
    for(;;) {
        led_mono_proc();
        vTaskDelay(50 / portTICK_RATE_MS);
    }
}

void led_create_task(void) { xTaskCreate(led_thread, "LED", 5000, NULL, 0, NULL); }
#endif /*HAS_RTOS*/

#ifdef HAS_TI_RTOS_LED_TASK
/* @brief   Application task entry point for the Project Zero.
 *
 * @param   a0, a1 - not used.
 */
static void led_thread(UArg a0, UArg a1) {

    for(;;) {
        proc_led_monos();
        /*Wait 100 ms*/
        Task_sleep(50);
    }
}

#define LED_TASK_STACK_SIZE 2048
#define LED_TASK_PRIORITY 2
uint8_t LedTaskStack[LED_TASK_STACK_SIZE];
Task_Struct ledTask;

bool led_create_tirtos_task(void) {
    bool res = true;
    Task_Params taskParams;

    Task_Params_init(&taskParams);
    taskParams.stack = LedTaskStack;
    taskParams.stackSize = LED_TASK_STACK_SIZE;
    taskParams.priority = LED_TASK_PRIORITY;

    Task_construct(&ledTask, led_thread, &taskParams, NULL);
    return res;
}
#endif /*HAS_TI_RTOS_LED_TASK*/

bool led_mono_pwm(uint8_t num, float freq_hz, float duty) {
    bool res = true;
    LedMonoHandle_t* Node = LedMonoGetNode(num);
    if(Node) {
        Node->prev = GPIO_LVL_UNDEF;
        Node->duty = duty;
        Node->mode = LED_MODE_PWM;
        if(0.0 < freq_hz) {
#ifdef HAS_MATH
            Node->period_ms = freq2period_ms(freq_hz);
#else
            Node->period_ms = 1000;
#endif
        } else {
#ifdef HAS_LOG
            LOG_INFO(LED_MONO, "FreqErr %f Hz", freq_hz);
#endif
        }
        Node->phase_ms = 0;
    }
    return res;
}

bool led_mono_set(uint8_t num, GpioLogicLevel_t level) {
    bool res = false;
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(LED_MONO, "LED_%u Set %s", num, GpioLevel2Str(level));
#endif
    LedMonoHandle_t* Node = LedMonoGetNode(num);
    if(Node) {
        res = led_set_state_ll(Node, level);
    } else {
#ifdef HAS_LOG
        LOG_ERROR(LED_MONO, "LED_%u SetNodeErr", num);
#endif
    }
    return res;
}

#ifdef HAS_LED_EXT
GpioLogicLevel_t led_mono_get(uint8_t num) {
#ifdef HAS_LOG
    LOG_DEBUG(LED_MONO, "%u Get", num);
#endif
    GpioLogicLevel_t level = GPIO_LVL_UNDEF;
    LedMonoHandle_t* Node = LedMonoGetNode(num);
    if(Node) {
        level = led_get_state_ll(Node);
#ifdef HAS_GPIO_DIAG
        LOG_DEBUG(LED_MONO, "LED_%u Set %s", num, GpioLevel2Str(level));
#endif
    } else {
#ifdef HAS_LOG
        LOG_ERROR(LED_MONO, "%u GetNodeErr", num);
#endif
    }
    return level;
}
#endif

#ifdef HAS_LED_EXT
static bool led_mono_blink_ll(LedMonoHandle_t* Node, uint32_t duration_ms) {
    bool res = false;
    if(Node && (0 < duration_ms)) {
        Node->prev = GPIO_LVL_UNDEF;
#ifdef HAS_TIME
        Node->on_time_ms = time_get_ms32();
#endif
        Node->duration_ms = duration_ms;
        Node->prev_mode = Node->mode;
        Node->mode = LED_MODE_BLINK;
        res = led_set_state_ll(Node, GPIO_LVL_HI);
    }
    return res;
}
#endif

#ifdef HAS_LED_EXT
bool led_mono_blink(uint8_t num, uint32_t duration_ms) {
    bool res = false;
#ifdef HAS_LOG
    LOG_DEBUG(LED_MONO, "LED_%u Blink %u ms", num, duration_ms);
#endif
    LedMonoHandle_t* Node = LedMonoGetNode(num);
    if(Node) {
        res = led_mono_blink_ll(Node, duration_ms);
    } else {
#ifdef HAS_LOG
        LOG_DEBUG(LED_MONO, "%u Blink,NodeErr", num);
#endif
    }
    return res;
}
#endif

bool led_mono_mode_set(uint8_t num, LedMode_t mode) {
    bool res = false;
#ifdef HAS_LED_DIAG
    LOG_INFO(LED_MONO, "LED%u,SetMode:%u=%s", num, mode, LedMode2Str(mode));
#endif
    LedMonoHandle_t* Node = LedMonoGetNode(num);
    if(Node) {
        Node->mode = mode;
        res = true;
    } else {
#ifdef HAS_LOG
        LOG_ERROR(LED_MONO, "LED%u,NodeErr", num);
#endif
    }
    return res;
}

bool led_mono_init_custom(void) {
    bool res = true;
#ifdef HAS_LOG
    log_level_get_set(LED_MONO, LOG_LEVEL_INFO);
#endif
    return res;
}

static bool led_mono_init_common(const LedMonoConfig_t* const Config, LedMonoHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->active = Config->active;
            Node->color = Config->color;
            Node->prev = GPIO_LVL_UNDEF;
            Node->duty = Config->duty;
            Node->period_ms = Config->period_ms;
            Node->phase_ms = Config->phase_ms;
            Node->mode = Config->mode;
            Node->pad.byte = Config->pad.byte;
            res = true;
        }
    }
    return res;
}

bool led_mono_init_one(uint32_t num) {
    bool res = true;
#ifdef HAS_LOG
    LOG_WARNING(LED_MONO, "TryInit :%u", num);
#endif
    LedMonoHandle_t* Node = LedMonoGetNode(num);
    if(Node) {
        const LedMonoConfig_t* Config = LedMonoGetConfig(num);
        if(Config) {
#ifdef HAS_LED_MONO_DIAG
            LedMonoConfigDiag(Config);
#endif
            led_mono_init_common(Config, Node);
            /*TODO Init GPIO for LED*/
#ifdef HAS_TEST_LED_MONO
            res = led_mono_on(Node);
#endif
#ifdef HAS_LOG
            log_level_get_set(LED_MONO, LOG_LEVEL_INFO);
#endif
        } else {
#ifdef HAS_LOG
            LOG_ERROR(LED_MONO, "ConfErr :%u", num);
#endif
        }
        Node->init = true;
        res = true;
    } else {
#ifdef HAS_LOG
        LOG_ERROR(LED_MONO, "InitNodeErr :%u", num);
#endif
    }

    return res;
}

bool led_mono_proc_one(uint32_t num) {
    bool res = false;
#ifdef HAS_LOG
    LOG_PARN(LED_MONO, "Proc:%u", num);
#endif
    led_mono_fix();
    LedMonoHandle_t* Node = LedMonoGetNode(num);
    if(Node) {

#ifdef HAS_LOG
        log_level_t ll = log_level_get(LED_MONO);
        if(LOG_LEVEL_PARANOID == ll) {
#ifdef HAS_LED_MONO_DIAG
            LedMonoDiag(Node);
#endif
        }
#endif

        uint64_t time_us = 0;
#ifdef HAS_TIME
        time_us = time_get_us();
        Node->cur_time_ms = (uint32_t)(time_us / 1000);
#else
        Node->cur_time_ms++;
        time_us = Node->cur_time_ms;
#endif /*HAS_TIME*/
        uint8_t val = 0;
        switch((uint8_t)Node->mode) {
        case LED_MODE_ON: {
            val = 1;
            res = true;
            // Node->prev = GPIO_LVL_UNDEF;
        } break;
        case LED_MODE_OFF: {
            val = 0;
            // Node->prev = GPIO_LVL_UNDEF;
            res = true;
        } break;
#ifdef HAS_LED_EXT
        case LED_MODE_BLINK: {
            uint32_t cur_duration_ms = 0;
            cur_duration_ms = Node->cur_time_ms - Node->on_time_ms;
            if(Node->duration_ms < cur_duration_ms) {
                res = true;
                val = 0;
                const LedMonoConfig_t* Config = LedMonoGetConfig(Node->num);
                if(Config) {
                    Node->mode = Config->mode;
                }
            } else {
                val = 1;
            }
        } break;
#endif
        case LED_MODE_PWM: {
#ifdef HAS_MATH
            val = calc_pwm_sample_num(time_us, Node->period_ms, (uint8_t)Node->duty, Node->phase_ms);
#else
            val = led_calc_pwm_sample_num((int32_t)time_us, Node->period_ms, Node->duty);
#endif
            res = true;
        } break;
        default: {
            res = false;
        } break;
        }

        if(res) {
            if(Node->prev != val) {
#ifdef HAS_GPIO_DIAG
                LOG_NOTICE(LED_MONO, "%s NewVal: %u", GpioPad2Str(Node->pad.byte), val);
#endif
                res = led_set_state_ll(Node, (GpioLogicLevel_t)val);
            }
        } else {
        }
        Node->prev = val;
    }
    return res;
}

COMPONENT_INIT_PATTERT(LED_MONO, LED_MONO, led_mono)
COMPONENT_PROC_PATTERT(LED_MONO, LED_MONO, led_mono)
