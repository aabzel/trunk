#include "led_rgb_drv.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifdef HAS_LOG
#include "log.h"
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
#include "clock_mcal.h"
#endif

#include "data_utils.h"

#ifdef HAS_GPIO
#include "gpio_mcal.h"
#endif

#include "led_rgb_config.h"

#ifdef HAS_TIME
#include "none_blocking_pause.h"
#endif

#ifdef HAS_HEALTH_MONITOR
#include "health_monitor.h"
#endif

//#include "sys_config.h"

COMPONENT_GET_NODE(LedRgb, led_rgb)
COMPONENT_GET_CONFIG(LedRgb, led_rgb)

const LedRgbInfo_t LedRgbInfoLUT[] = {
    {
        .color = COLOR_BLACK,
        .gpio_state =
            {
                .red = 0,
                .green = 0,
                .blue = 0,
            },
    },
    {
        .color = COLOR_RED,
        .gpio_state =
            {
                .red = 1,
                .green = 0,
                .blue = 0,
            },
    },
    {
        .color = COLOR_YELLOW,
        .gpio_state =
            {
                .red = 1,
                .green = 1,
                .blue = 0,
            },
    },
    {
        .color = COLOR_GREEN,
        .gpio_state =
            {
                .red = 0,
                .green = 1,
                .blue = 0,
            },
    },
    {
        .color = COLOR_CYANIC,
        .gpio_state =
            {
                .red = 0,
                .green = 1,
                .blue = 1,
            },
    },
    {
        .color = COLOR_BLUE,
        .gpio_state =
            {
                .red = 0,
                .green = 0,
                .blue = 1,
            },
    },
    {
        .color = COLOR_PURPLE,
        .gpio_state =
            {
                .red = 1,
                .green = 0,
                .blue = 1,
            },
    },
    {
        .color = COLOR_WHITE,
        .gpio_state =
            {
                .red = 1,
                .green = 1,
                .blue = 1,
            },
    },
};

uint32_t led_rgb_get_color_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(LedRgbInfoLUT);
    return cnt;
}

uint8_t Color2RgbGpio(Color_t color) {
    uint8_t byte = 0;
    uint32_t i = 0;
    uint32_t color_cnt = ARRAY_SIZE(LedRgbInfoLUT);
    for(i = 0; i < color_cnt; i++) {
        if(color == LedRgbInfoLUT[i].color) {
            byte = LedRgbInfoLUT[i].gpio_state.byte;
            break;
        }
    }
    return byte;
}

// LedRgbHandle_t LedRgb[LED_RGB_COUNT];
GpioLogicLevel_t LedRgbLogicLevelZero2Voltage(GpioLogicLevel_t active) {
    GpioLogicLevel_t voltage = GPIO_LVL_UNDEF;
    switch(active) {
    case GPIO_LVL_LOW:
        voltage = GPIO_LVL_HI;
        break;
    case GPIO_LVL_HI:
        voltage = GPIO_LVL_LOW;
        break;
    default:
        voltage = GPIO_LVL_UNDEF;
        break;
    }
    return voltage;
}

GpioLogicLevel_t LedRgbLogicLevelHi2Voltage(GpioLogicLevel_t active) {
    GpioLogicLevel_t voltage = active;
    return voltage;
}

#if 0
LedRgbHandle_t* LedRgbGetNode(uint8_t num) {
    LedRgbHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = led_rgb_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(num == LedRgbInstance[i].num) {
            if(LedRgbInstance[i].valid) {
                Node = &LedRgbInstance[i];
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
#endif

static LedRgbState_t led_rgb_get_state_ll(LedRgbHandle_t* Node) {
    LedRgbState_t LedRgbState;
    LedRgbState.byte = 0;
    if(Node) {
        bool res = true;

        GpioLogicLevel_t logic_level = GPIO_LVL_UNDEF;
        res = gpio_get_state(Node->Pads.red, &logic_level);
        if(res) {
            LedRgbState.red = logic_level;
        }

        logic_level = GPIO_LVL_UNDEF;
        res = gpio_get_state(Node->Pads.green, &logic_level);
        if(res) {
            LedRgbState.green = logic_level;
        }

        logic_level = GPIO_LVL_UNDEF;
        res = gpio_get_state(Node->Pads.blue, &logic_level);
        if(res) {
            LedRgbState.blue = logic_level;
        }
        if(GPIO_LVL_LOW == Node->active) {
            LedRgbState.red = !LedRgbState.red;
            LedRgbState.green = !LedRgbState.green;
            LedRgbState.blue = !LedRgbState.blue;
        }
    }
    return LedRgbState;
}

static bool led_rgb_set_state_ll(LedRgbHandle_t* Node, LedRgbState_t gpio_state) {
    bool res = false;
    if(Node) {
        res = true;
        if(GPIO_LVL_HI == Node->active) {
            res = gpio_logic_level_set(Node->Pads.red, gpio_state.red) && res;
            res = gpio_logic_level_set(Node->Pads.green, gpio_state.green) && res;
            res = gpio_logic_level_set(Node->Pads.blue, gpio_state.blue) && res;
        } else {
            res = gpio_logic_level_set(Node->Pads.red, !gpio_state.red) && res;
            res = gpio_logic_level_set(Node->Pads.green, !gpio_state.green) && res;
            res = gpio_logic_level_set(Node->Pads.blue, !gpio_state.blue) && res;
        }
    }
    return res;
}

static bool led_rgb_set_color_ll(LedRgbHandle_t* Node, Color_t color) {
    bool res = false;
    if(Node) {
        LedRgbState_t gpio_state;
        gpio_state.byte = 0;
        gpio_state.byte = Color2RgbGpio(color);
        res = true;
        if(COLOR_BLACK != color) {
            Node->set_color = color;
        }
        res = led_rgb_set_state_ll(Node, gpio_state);
    }
    return res;
}

bool led_rgb_test_one(uint8_t num) {
    bool res = false;
    LedRgbHandle_t* Node = LedRgbGetNode(num);
    if(Node) {
        Color_t color = COLOR_UNDEF;
        for(color = 0; color < COLOR_CNT; color++) {
            res = led_rgb_set_color_ll(Node, color);
#ifdef HAS_TIME
            wait_ms(300);
#endif
            res = led_rgb_set_color_ll(Node, COLOR_BLACK);
#ifdef HAS_TIME
            wait_ms(300);
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

    if(ok_cnt == cnt) {
        res = true;
    } else {
        res = false;
    }
    LOG_INFO(LED_RGB, "TestDone");
    return res;
}

bool led_rgb_blink_ll(LedRgbHandle_t* Node, uint32_t duration_ms, Color_t color) {
    bool res = false;
    if(Node && (0 < duration_ms)) {
        Node->prev.red = 0;
        Node->prev.green = 0;
        Node->prev.blue = 0;
        Node->duration_ms = duration_ms;
        Color_t set_color = color;
        if(LED_MCAL_MODE_BLINK == Node->mode) {
            if(COLOR_YELLOW != Node->temp_color) {
                set_color = COLOR_YELLOW;
            }
        } else {
            Node->mode = LED_MCAL_MODE_BLINK;
        }
        Node->temp_color = set_color;
        res = led_rgb_set_color_ll(Node, set_color);
#ifdef HAS_TIME
        Node->on_time_ms = time_get_ms32();
#endif
    }
    return res;
}

bool led_rgb_blink(uint8_t num, uint32_t duration_ms, Color_t color) {
    bool res = false;
    LedRgbHandle_t* LedRgbNode = LedRgbGetNode(num);
    if(LedRgbNode) {
        res = led_rgb_blink_ll(LedRgbNode, duration_ms, color);
    }
    return res;
}

static Color_t RgbGpio2Color(uint8_t byte) {
    Color_t color = COLOR_UNDEF;
    uint32_t i = 0;
    uint32_t color_cnt = ARRAY_SIZE(LedRgbInfoLUT);
    for(i = 0; i < color_cnt; i++) {
        if((MASK_3BIT & LedRgbInfoLUT[i].gpio_state.byte) == (MASK_3BIT & byte)) {
            color = LedRgbInfoLUT[i].color;
            break;
        }
    }

    return color;
}

bool led_rgb_init_custom(void) {
    bool res = true;
    return res;
}

bool led_rgb_set_color(uint8_t num, Color_t color) {
    bool res = false;
#ifdef HAS_LED_RGB_DIAG
    LOG_DEBUG(LED_RGB, "%u Set Color %u=%s", num, color, ColorToStr(color));
#endif

    LedRgbHandle_t* Node = LedRgbGetNode(num);
    if(Node) {
        Node->set_color = color;
        // res= led_rgb_set_color_ll( Node, COLOR_BLACK);
        res = led_rgb_set_color_ll(Node, color);
    }
    return res;
}

Color_t led_rgb_get_color_ll(LedRgbHandle_t* Node) {
    Color_t color = COLOR_UNDEF;
    LOG_DEBUG(LED_RGB, "%u GetLL Color", Node->num);
    if(Node) {
        LedRgbState_t LedRgbState;
        LedRgbState.byte = 0;
        LedRgbState = led_rgb_get_state_ll(Node);
        color = RgbGpio2Color(LedRgbState.byte);
    }
    return color;
}

Color_t led_rgb_get_color(uint8_t num) {
    Color_t color = COLOR_UNDEF;
    LOG_DEBUG(LED_RGB, "%u Get Color", num);
    LedRgbHandle_t* Node = LedRgbGetNode(num);
    if(Node) {
        color = led_rgb_get_color_ll(Node);
    }

    return color;
}

static bool led_rgb_set_state(LedRgbHandle_t* Node, GpioLogicLevel_t val) {
    bool res = false;
    if(GPIO_LVL_HI == val) {
        if(LED_MCAL_MODE_BLINK == Node->mode) {
            res = led_rgb_set_color_ll(Node, Node->temp_color);
        } else {
            res = led_rgb_set_color_ll(Node, Node->set_color);
        }
    } else {
        res = led_rgb_set_color_ll(Node, COLOR_BLACK);
    }
    return res;
}

static bool proc_led_rgb(LedRgbHandle_t* Node) {
    bool res = false;
#ifdef HAS_LOG
    LOG_DEBUG(LED_RGB, "Proc %u", Node->num);
#endif
    if(Node) {
#ifdef HAS_TIME
        Node->cur_time_ms = time_get_ms32();
#else
        Node->cur_time_ms++;
#endif /*HAS_TIME*/
        uint8_t val = 0;
        switch(Node->mode) {
        case LED_MCAL_MODE_ON: {
            val = 1;
            res = true;
            // Node->prev = GPIO_LVL_UNDEF;
        } break;
        case LED_MCAL_MODE_OFF: {
            val = 0;
            // Node->prev = GPIO_LVL_UNDEF;
            res = true;
        } break;
        case LED_MCAL_MODE_BLINK: {
            uint32_t cur_duration_ms = 0;
            cur_duration_ms = Node->cur_time_ms - Node->on_time_ms;
            if(Node->duration_ms < cur_duration_ms) {
                val = 0;
                const LedRgbConfig_t* LedConfNode = LedRgbGetConfig(Node->num);
                Node->mode = LedConfNode->mode;
                Node->set_color = LedConfNode->set_color;
            } else {
                val = 1;
            }
            res = true;
        } break;
        case LED_MCAL_MODE_PWM: {
            val = calc_pwm_sample_num(Node->cur_time_ms * 1000, Node->period_ms, (uint8_t)Node->duty, Node->phase_ms);
            res = true;
        } break;
        default: {
            res = false;
        } break;
        }

        if(res) {
            res = led_rgb_set_state(Node, val);
        } else {
        }
    }
    return res;
}

bool led_rgb_proc_one(uint32_t num) {
    bool res = false;
    LedRgbHandle_t* Node = LedRgbGetNode(num);
    if(Node) {
        res = proc_led_rgb(Node);
    }
    return res;
}

#if 0
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
#endif

bool led_rgb_on(LedRgbHandle_t* Node) {
    bool res = false;
    if(Node) {
        res = true;
        Node->prev.red = 0;
        Node->prev.green = 0;
        Node->prev.blue = 0;
        Node->mode = LED_MCAL_MODE_ON;
    }
    return res;
}

bool led_rgb_off(LedRgbHandle_t* Node) {
    bool res = false;
    if(Node) {
        res = true;
        Node->prev.red = 0;
        Node->prev.green = 0;
        Node->prev.blue = 0;
        Node->mode = LED_MCAL_MODE_OFF;
    }
    return res;
}

bool led_rgb_pwm(uint8_t num, float freq_hz, uint8_t duty) {
    bool res = true;
    LedRgbHandle_t* Node = LedRgbGetNode(num);
    if(Node) {
        Node->prev.red = 0;
        Node->prev.green = 0;
        Node->prev.blue = 0;
        Node->duty = duty;
        Node->mode = LED_MCAL_MODE_PWM;
        Node->period_ms = freq2period_ms(freq_hz);
        Node->phase_ms = 0;
    }
    return res;
}

static bool led_rgb_init_common(const LedRgbConfig_t* const Config, LedRgbHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->duty = Config->duty;
            Node->period_ms = Config->period_ms;
            Node->phase_ms = Config->phase_ms;
            Node->mode = Config->mode;
            Node->Pads = Config->Pads;
            Node->set_color = Config->set_color;
            Node->active = Config->active;
            res = true;
        }
    }
    return res;
}

bool led_rgb_init_one(uint32_t num) {
#ifdef HAS_LOG
    LOG_INFO(LED_RGB, "TryInit %u", num);
#endif
    bool res = false;
    LedRgbHandle_t* Node = LedRgbGetNode(num);
    if(Node) {
        const LedRgbConfig_t* Config = LedRgbGetConfig(num);
        if(Config) {
            LOG_INFO(LED_RGB, "Init %u", num);
            res = led_rgb_init_common(Config, Node);
            Node->prev.red = 0;
            Node->prev.green = 0;
            Node->prev.blue = 0;

            res = led_rgb_set_color_ll(Node, Config->set_color);
#ifdef HAS_LED_RGB_TEST
            led_rgb_test_one(num);
#endif
            Node->init = true;
            res = true;
        }
    }

    return res;
}

bool led_rgb_mcal_init(void) {
    bool res = true;
    uint32_t ok = 0;
    res = led_rgb_init_custom();
    uint32_t cnt = led_rgb_get_cnt();
    (void)cnt;
    uint8_t num = 0;
    for(num = 0; num <= cnt; num++) {
        res = led_rgb_init_one(num);
        if(res) {
            ok++;
        }
    }
    if(cnt == ok) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

// COMPONENT_INIT_PATTERT(LED_RGB, LED_RGB, led_rgb)
COMPONENT_PROC_PATTERT(LED_RGB, LED_RGB, led_rgb)
