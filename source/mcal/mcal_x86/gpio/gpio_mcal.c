#include "gpio_mcal.h"

/*
  That file contain binding functions
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "bit_utils.h"
#include "board_config.h"
#include "data_utils.h"
#include "gpio_custom_drv.h"
#include "gpio_isr.h"
#include "module_driver_port.h"
#include "std_includes.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_DEBUGGER
#include "debugger.h" //For assert
#endif

static const GpioPortInfo_t GpioPortInfo[] = {
    {
        .GPIOx = GPIOA,
        //  .PINx = PCTRLA,
        .port = GPIO_PORT_A,
        .instance_type = PORT_A,
        .gpio_instance_type = GPIO_A,
        .valid = true,
    },
    {
        .GPIOx = GPIOB,
        // .PINx = PCTRLB,
        .port = GPIO_PORT_B,
        .instance_type = PORT_B,
        .gpio_instance_type = GPIO_B,
        .valid = true,
    },
    {
        .GPIOx = GPIOC,
        //  .PINx = PCTRLC,
        .port = GPIO_PORT_C,
        .instance_type = PORT_C,
        .gpio_instance_type = GPIO_C,
        .valid = true,
    },
    {
        .GPIOx = GPIOD,
        //  .PINx = PCTRLD,
        .port = GPIO_PORT_D,
        .instance_type = PORT_D,
        .gpio_instance_type = GPIO_D,
        .valid = true,
    },
    {
        .GPIOx = GPIOE,
        //  .PINx = PCTRLE,
        .port = GPIO_PORT_E,
        .instance_type = PORT_E,
        .gpio_instance_type = GPIO_E,
        .valid = true,
    },
};

const GpioPortInfo_t* GpioGetPortInfo(GpioPort_t port) {
    const GpioPortInfo_t* Node = NULL;
    uint8_t i = 0;
    for(i = 0; i < ARRAY_SIZE(GpioPortInfo); i++) {
        if(GpioPortInfo[i].valid) {
            if(port == GpioPortInfo[i].port) {
                Node = &GpioPortInfo[i];
                break;
            }
        }
    }
    return Node;
}

static PORT_GpioDirType GpioDirToFc7300xDir(GpioDir_t dir) {
    PORT_GpioDirType direction = PORT_GPIO_IN;
    switch(dir) {
    case GPIO_DIR_OUT:
        direction = PORT_GPIO_OUT;
        break;
    case GPIO_DIR_IN:
        direction = PORT_GPIO_IN;
        break;
    case GPIO_DIR_OUT_OPEN_DRAIN:
        direction = PORT_GPIO_OUT;
        break;
    case GPIO_DIR_OUT_PUSH_PULL:
        direction = PORT_GPIO_OUT;
        break;

    case GPIO_DIR_INOUT:
        direction = PORT_GPIO_IN;
        break;
    case GPIO_DIR_INOUT_OPEN_DRAIN:
        direction = PORT_GPIO_IN;
        break;
    case GPIO_DIR_UNDEF:
        direction = PORT_GPIO_IN;
        break;
    case GPIO_DIR_NONE:
        direction = PORT_GPIO_IN;
        break;
    default:
        direction = PORT_GPIO_IN;
        break;
    }
    return direction;
}

static Gpio_LevelType GpioLogicLevelToLevelType(const GpioLogicLevel_t logic_level) {
    Gpio_LevelType e_output = GPIO_LOW;
    switch(logic_level) {
    case GPIO_LVL_LOW:
        e_output = GPIO_LOW;
        break;
    case GPIO_LVL_HI:
        e_output = GPIO_HIGH;
        break;
    default:
        e_output = GPIO_LOW;
        break;
    }
    return e_output;
}

static Gpio_Direction GpioDirToGpioDirection(GpioDir_t direction) {
    Gpio_Direction gpio_dir = GPIO_IN;
    switch(direction) {
    case GPIO_DIR_IN:
        gpio_dir = GPIO_IN;
        break;
    case GPIO_DIR_OUT_OPEN_DRAIN:
        gpio_dir = GPIO_OUT;
        break;
    case GPIO_DIR_OUT_PUSH_PULL:
        gpio_dir = GPIO_OUT;
        break;
    case GPIO_DIR_OUT:
        gpio_dir = GPIO_OUT;
        break;
    case GPIO_DIR_NONE:
        gpio_dir = GPIO_IN;
        break;
    case GPIO_DIR_INOUT_OPEN_DRAIN:
        gpio_dir = GPIO_IN;
        break;
    case GPIO_DIR_INOUT:
        gpio_dir = GPIO_IN;
        break;
    case GPIO_DIR_UNDEF:
        gpio_dir = GPIO_IN;
        break;
    default:
        gpio_dir = GPIO_IN;
        break;
    }
    return gpio_dir;
}

#if 0
static GPIO_Type* GpioPortToFc7300xGpioBase(GpioPort_t port) {
    GPIO_Type* GPIOx = NULL;
    const GpioPortInfo_t* PortInfo = GpioGetPortInfo(port);
    if(PortInfo) {
        GPIOx = PortInfo->GPIOx;
    }

    return GPIOx;
}

static PCTRL_Type* GpioPortToFc7300xBase(GpioPort_t port) {
    PCTRL_Type* PCTRLx = NULL;
    const GpioPortInfo_t* PortInfo = GpioGetPortInfo(port);
    if(PortInfo) {
        PCTRLx = PortInfo->PINx;
    }
    return PCTRLx;
}

#endif

PORT_InstanceType GpioPortTo_eInstance(const GpioPort_t port) {
    PORT_InstanceType instance_type = 0;
    GpioPortInfo_t* Info = GpioGetPortInfo(port);
    if(Info) {
        instance_type = Info->instance_type;
    }

    return instance_type;
}

static PORT_PullStatusType GpioPullToFc7300xPull(GpioPullMode_t pull) {
    PORT_PullStatusType port_pull = 2;
    switch(pull) {
    case GPIO__PULL_DOWN:
        port_pull = PORT_PULL_DOWN;
        break;
    case GPIO__PULL_UP:
        port_pull = PORT_PULL_UP;
        break;
    case GPIO__PULL_AIR:
        port_pull = 2;
        break;
    case GPIO__PULL_BOTH:
        port_pull = 2;
        break;
    default:
        port_pull = 2;
        break;
    }
    return port_pull;
}

#ifdef HAS_PINS
bool gpio_clock_init(void) {
    bool res = false;
#ifdef HAS_LOG
    LOG_WARNING(GPIO, "ClockInit");
#endif

    return res;
}
#endif /*HAS_PINS*/

static PORT_GpioLevelType GpioLogicLevelTo_ePortGpioLevel(GpioLogicLevel_t logic_level) {
    PORT_GpioLevelType ePortGpioLevel = PORT_GPIO_LOW;
    switch(logic_level) {
    case GPIO_LVL_LOW:
        ePortGpioLevel = PORT_GPIO_LOW;
        break;
    case GPIO_LVL_HI:
        ePortGpioLevel = PORT_GPIO_HIGH;
        break;
    default:
        ePortGpioLevel = PORT_GPIO_LOW;
        break;
    }
    return ePortGpioLevel;
}
#if 0


static port_slew_rate_t GpioRateToFc7300xRate(GpioRate_t rate) {
    port_slew_rate_t rateSelect = PCTRL_SLOW_SLEW_RATE;
    switch(rate) {
    case GPIO_RATE_SLOW:
        rateSelect = PCTRL_SLOW_SLEW_RATE;
 break;
    case GPIO_RATE_FAST:
        rateSelect = PCTRL_FAST_SLEW_RATE;
 break;
    default:
        rateSelect = PCTRL_FAST_SLEW_RATE;
 break;
    }
    return rateSelect;
}

static port_drive_strength_t GpioDriveToFc7300xDrive(GpioDrive_t drive) {
    port_drive_strength_t driveSelect = PCTRL_LOW_DRIVE_STRENGTH;
    switch(drive) {
    case GPIO_DRIVE_STRENGTH_LOW:
        driveSelect = PCTRL_LOW_DRIVE_STRENGTH;
 break;
    case GPIO_DRIVE_STRENGTH_HIGH:
        driveSelect = PCTRL_HIGH_DRIVE_STRENGTH;
 break;
    default:
        driveSelect = GPIO_DRIVE_STRENGTH_HIGH;
 break;
    }
    return driveSelect;
}
#endif

bool gpio_get_state(Pad_t Pad, GpioLogicLevel_t* const logic_level) {
    bool res = false;
    const GpioPortInfo_t* PortInfo = GpioGetPortInfo(Pad.port);
    if(PortInfo) {
        uint32_t pin_mask = GpioPinNumToPinMask(Pad.pin);
        uint32_t levels = GPIO_ReadPins(PortInfo->gpio_instance_type, pin_mask);
        if(levels == pin_mask) {
            *logic_level = GPIO_LVL_LOW;
        } else {
            *logic_level = GPIO_LVL_HI;
        }
#ifdef HAS_GPIO_DIAG
        LOG_DEBUG(GPIO, "Get,%s=%u", GpioPadToStr(Pad), *logic_level);
#endif
        res = true;
    }

    return res;
}

bool is_edge_irq_en(Pad_t Pad) {
    bool res = false;
    return res;
}

bool pin_get_int(uint8_t pin) {
    bool res = false;

    return res;
}

bool pin_get_int_pend(uint8_t pin) {
    bool res = false;

    return res;
}

#ifdef HAS_EXT_INT
PinIntEdge_t pin_get_edge(uint8_t pin) {
    PinIntEdge_t edge = PIN_INT_EDGE_UNDEF;
    return edge;
}
#endif

GpioOutType_t gpio_get_out_type(Pad_t Pad) {
    GpioOutType_t out_type = OUT_TYPE_UNDEF;
    return out_type;
}

GpioApiMode_t gpio_mode_get(Pad_t Pad) {

    GpioApiMode_t pin_mode = GPIO_API_MODE_UNDEF;

    /*  GPIO configuration register (GPIOx_CFGR)*/
    return pin_mode;
}
static PORT_IrqcConfigurationType GpioModeTo_ePortIsrMode(GpioApiMode_t mode) {
    PORT_IrqcConfigurationType port_isr_mode = PORT_IRQ_DISABLE;
    switch(mode) {
    case GPIO_API_MODE_GPIO:
        port_isr_mode = PORT_IRQ_DISABLE;
        break;
    case GPIO_API_MODE_INPUT_EXINT_RISING:
        port_isr_mode = PORT_IRQ_RISING;
        break;
    case GPIO_API_MODE_INPUT_EXINT_FAILLING:
        port_isr_mode = PORT_IRQ_FALLING;
        break;
    case GPIO_API_MODE_INPUT_EXINT_LOGIC_0:
        port_isr_mode = PORT_IRQ_LOGIC_0;
        break;
    case GPIO_API_MODE_INPUT_EXINT_LOGIC_1:
        port_isr_mode = PORT_IRQ_LOGIC_1;
        break;
    case GPIO_API_MODE_INPUT_EXINT_BOTH_EDGE:
        port_isr_mode = PORT_IRQ_BOTH_EDGE;
        break;
    case GPIO_API_MODE_INPUT_EXINT:
        port_isr_mode = PORT_IRQ_BOTH_EDGE;
        break;
    case GPIO_API_MODE_ALT1:
        port_isr_mode = PORT_IRQ_DISABLE;
        break;
    case GPIO_API_MODE_ALT2:
        port_isr_mode = PORT_IRQ_DISABLE;
        break;
    case GPIO_API_MODE_HW_PWM:
        port_isr_mode = PORT_IRQ_DISABLE;
        break;
    case GPIO_API_MODE_INPUT:
        port_isr_mode = PORT_IRQ_DISABLE;
        break;
    case GPIO_API_MODE_OUTPUT:
        port_isr_mode = PORT_IRQ_DISABLE;
        break;
    case GPIO_API_MODE_ANALOG:
        port_isr_mode = PORT_IRQ_DISABLE;
        break;
    case GPIO_API_MODE_I2C:
        port_isr_mode = PORT_IRQ_DISABLE;
        break;
    case GPIO_API_MODE_DMA_RISING:
        port_isr_mode = PORT_IRQ_DMA_RISING;
        break;
    case GPIO_API_MODE_DMA_FALLING:
        port_isr_mode = PORT_IRQ_DMA_FALLING;
        break;
    case GPIO_API_MODE_DMA_BOTH_EDGE:
        port_isr_mode = PORT_IRQ_DMA_BOTH_EDGE;
        break;
    case GPIO_API_MODE_TOOGLED_WHEN_LOGIC_0:
        port_isr_mode = PORT_IRQ_TOOGLED_WHEN_LOGIC_0;
        break;
    case GPIO_API_MODE_TOOGLED_WHEN_LOGIC_1:
        port_isr_mode = PORT_IRQ_TOOGLED_WHEN_LOGIC_1;
        break;
    default:
        port_isr_mode = PORT_IRQ_DISABLE;
        break;
    }
    return port_isr_mode;
}

GpioDir_t gpio_dir_get(Pad_t Pad) {
    GpioDir_t direction = GPIO_DIR_UNDEF;
    GpioPortInfo_t* Info = GpioGetPortInfo(Pad.port);
    if(Info) {
        // TODO
    }
    return direction;
}

GpioPullMode_t gpio_pull_get(Pad_t Pad) {
    GpioPullMode_t pull_mode = GPIO__PULL_UNDEF;
    // TODO
    return pull_mode;
}

bool gpio_pin_fun_get(Pad_t Pad, GpioPinFunction_t* const function) {
    bool res = true;
    // TODO
    return res;
}

bool ext_int_set_mask(uint32_t mask) {
    bool res = true;
    // TODO
    return res;
}

bool ext_int_reset_mask(uint32_t mask) {
    bool res = true;
    // TODO
    return res;
}

bool gpio_pull_set(Pad_t Pad, GpioPullMode_t pull_mode) {
    bool res = false;
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "Set,Pad:%s,Pull:%s", GpioPadToStr(Pad), GpioPull2Str(pull_mode));
#endif
    res = gpio_is_valid_pull(pull_mode);
    if(res) {
        res = false;
    }

    return res;
}

#if 0
uint8_t LogicLevel2PinState(GpioLogicLevel_t logic_level) {
    uint8_t pin_state = 0;
    switch((uint8_t)logic_level) {
    case GPIO_LVL_LOW:
        pin_state = 0;
 break;
    case GPIO_LVL_HI:
        pin_state = 1;
 break;
    default:
 break;
    }
    return pin_state;
}
#endif

bool gpio_init_custom(void) {
    bool res = true;
    return res;
}

bool gpio_deinit_one(Pad_t Pad) {
    bool res = false;
    const GpioPortInfo_t* Info = GpioGetPortInfo(Pad.port);
    if(Info) {
#ifdef HAS_GPIO_DIAG
        LOG_INFO(GPIO, "%s,ClkOn", GpioPortToStr(Pad.port));
#endif
    }
    // uint32_t pin_mask = PinNum2PinMask(Pad.pin);
    res = gpio_logic_level_set(Pad, GPIO_LVL_LOW);

    // res = true;

    return res;
}

bool gpio_pin_mux_set(uint8_t port, uint8_t pin, uint8_t mux) {
    bool res = false;

    return res;
}

bool gpio_pin_mux_get(uint8_t port, uint8_t pin, uint8_t* const mux) {
    bool res = false;
    uint8_t mux_val = 0xFF;

    if(res) {
        *mux = mux_val;
    } else {
#ifdef HAS_LOG
        LOG_DEBUG(GPIO, "GetPinMuxErr");
#endif
    }
    return res;
}

bool gpio_toggle(const Pad_t Pad) {
    bool res = false;
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "Toggle,%s", GpioPadToStr(Pad));
#endif
    const GpioPortInfo_t* PortInfo = GpioGetPortInfo(Pad.port);
    if(PortInfo) {
        uint32_t pin_mask = GpioPinNumToPinMask(Pad.pin);
        GPIO_Toggle(PortInfo->gpio_instance_type, pin_mask);
        res = true;
    }

    return res;
}

uint32_t gpio_read(Pad_t Pad) {
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "Get P%s%u", GpioPortToStr(Pad.port), Pad.pin);
#endif
    uint32_t levels = (uint32_t)0;
    const GpioPortInfo_t* PortInfo = GpioGetPortInfo(Pad.port);
    if(PortInfo) {
        levels = GPIO_ReadPins(PortInfo->gpio_instance_type, 0xFFFFFFFF);
    }
    return levels;
}

bool gpio_is_valid_pad(Pad_t Pad) {
    bool res = false;
    if(Pad.pin <= GPIO_PIN_COUNT) {
        if(Pad.port <= GPIO_PORT_E) {
            res = true;
        }
    }
    return res;
}

static bool GpioPullOnOffToFc7300xPull(const GpioPullMode_t pull) {
    bool pull_en = false;
    switch(pull) {
    case GPIO__PULL_UP:
    case GPIO__PULL_DOWN:
        pull_en = true;
        break;
    case GPIO__PULL_BOTH:
    case GPIO__PULL_AIR:
        pull_en = false;
        break;
    default:
        pull_en = false;
        break;
    }
    return pull_en;
}

/*can be called from isr*/
bool gpio_logic_level_set(Pad_t Pad, GpioLogicLevel_t logic_level) {
    bool res = false;
    GpioPortInfo_t* PortInfo = GpioGetPortInfo(Pad.port);
    if(PortInfo) {
#ifdef HAS_GPIO_DIAG
        LOG_DEBUG(GPIO, "Set,%s,Lev:%u", GpioPadToStr(Pad), logic_level);
#endif
        uint32_t pin_mask = GpioPinNumToPinMask(Pad.pin);
        Gpio_LevelType e_output = GpioLogicLevelToLevelType(logic_level);
        GPIO_WritePins(PortInfo->gpio_instance_type, pin_mask, e_output);
        res = true;
    }

    return res;
}

bool gpio_dir_set(Pad_t Pad, GpioDir_t direction) {
    bool res = false;
    GpioPortInfo_t* PortInfo = (GpioPortInfo_t*)GpioGetPortInfo(Pad.port);
    if(PortInfo) {
        Gpio_Direction e_pin_dir = GpioDirToGpioDirection(direction);
        uint32_t pin_mask = GpioPinNumToPinMask(Pad.pin);
        GPIO_SetPinsDir(PortInfo->gpio_instance_type, pin_mask, e_pin_dir);
        res = true;
    }
    return res;
}

static bool gpio_compose_init(const GpioConfig_t* const Config, PORT_InitType* const init) {
    bool res = false;
    if(Config) {
        if(init) {
            /* Port pin mode */
            init->uPortPinMux.u32PortPinMode = Config->mux;
            /* Port pin, 0~31 bit indicates the pin 0~31 */
            init->u32PortPins = GpioPinNumToPinMask(Config->pad.pin);
            /* Gpio direction */
            init->ePortGpioDir = GpioDirToFc7300xDir(Config->dir);
            /* pull status, pull up or pull down */
            init->ePullSel = GpioPullToFc7300xPull(Config->pull);
            /* whether to pull the port pin */
            init->bPullEn = GpioPullOnOffToFc7300xPull(Config->pull);
            /* Gpio level */
            init->ePortGpioLevel = GpioLogicLevelTo_ePortGpioLevel(Config->logic_level);
            /* Port interrupt config */
            init->tInterruptCfg.ePortIsrMode = GpioModeTo_ePortIsrMode(Config->mode);
            /* whether to enable pad drive strength, only hs PAD used */
            init->bDrvStrengthEn = false;
            /* whether to use passive filter, please refer to reference manual for details */
            init->bPassiveFilterEn = false;
            res = true;
        }
    }
    return res;
}

bool gpio_init_one(const GpioConfig_t* const Config) {
    bool res = false;
    if(Config) {
#ifdef HAS_GPIO_DIAG
        GpioConfigDiag(Config);
#endif
        res = gpio_is_pin_single(Config->pad.byte);
        if(res) {
#ifdef HAS_GPIO_DIAG
            LOG_DEBUG(GPIO, "Single P%s%u", GpioPadToStr(Config->pad));
#endif
            PORT_HandleType PortHandle = {0};
            PortHandle.eInstance = GpioPortTo_eInstance(Config->pad.port);

            PORT_InitType InitStruct = {0};
            res = gpio_compose_init(Config, &InitStruct);

            PORT_InitPins(&PortHandle, &InitStruct);
            res = true;
        } else {
#ifdef HAS_GPIO_DIAG
            LOG_ERROR(GPIO, "ReDefine P%s%u", GpioPortToStr(Config->pad.port), Config->pad.pin);
#endif
        }
    }
    return res;
}
