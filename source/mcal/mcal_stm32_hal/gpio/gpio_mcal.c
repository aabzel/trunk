#include "gpio_mcal.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "bit_utils.h"
#include "board_config.h"
#include "data_utils.h"
#include "gpio_config.h"
#include "gpio_custom_drv.h"
#include "gpio_custom_isr.h"
#include "gpio_custom_types.h"
#include "std_includes.h"
#include "stm32fx_hal.h"

#ifdef HAS_DEBUGGER
#include "debugger.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

static GpioDir_t GpioStmDirToDir(GpioStm32Mode_t mode) {
    GpioDir_t dirr = GPIO_DIR_UNDEF;
    switch((uint8_t)mode) {
    case GP_STM32_MODE_ALT_FUN:
        dirr = GPIO_DIR_UNDEF;
        break;
    case GP_STM32_MODE_ANALOG:
        dirr = GPIO_DIR_IN;
        break;
    case GP_STM32_MODE_INPUT:
        dirr = GPIO_DIR_IN;
        break;
    case GP_STM32_MODE_GNRL_PURPOSE_OUT:
        dirr = GPIO_DIR_OUT;
        break;
    default:
        break;
    }
    return dirr;
}

static const GpioPortInfo_t GPIOxInfo[] = {
#ifdef GPIOA
    {
        .valid = true,
        .port = GPIO_PORT_A,
        .GPIOx = GPIOA,
    },
#endif

#ifdef GPIOB
    {
        .valid = true,
        .port = GPIO_PORT_B,
        .GPIOx = GPIOB,
    },
#endif

#ifdef GPIOC
    {
        .valid = true,
        .port = GPIO_PORT_C,
        .GPIOx = GPIOC,
    },
#endif

#ifdef GPIOD
    {
        .valid = true,
        .port = GPIO_PORT_D,
        .GPIOx = GPIOD,
    },
#endif

#ifdef GPIOE
    {
        .valid = true,
        .port = GPIO_PORT_E,
        .GPIOx = GPIOE,
    },
#endif

#ifdef GPIOF
    {
        .valid = true,
        .port = GPIO_PORT_F,
        .GPIOx = GPIOF,
    },
#endif

#ifdef GPIOG
    {
        .valid = true,
        .port = GPIO_PORT_G,
        .GPIOx = GPIOG,
    },
#endif

#ifdef GPIOH
    {
        .valid = true,
        .port = GPIO_PORT_H,
        .GPIOx = GPIOH,
    },
#endif

#ifdef GPIOI
    {
        .valid = true,
        .port = GPIO_PORT_I,
        .GPIOx = GPIOI,
    },
#endif
};

uint8_t gpio_port_cnt_get(void) {
    uint8_t port_cnt = 0;
#ifdef GPIOA
    port_cnt++;
#endif

#ifdef GPIOB
    port_cnt++;
#endif

#ifdef GPIOC
    port_cnt++;
#endif

#ifdef GPIOD
    port_cnt++;
#endif

#ifdef GPIOE
    port_cnt++;
#endif

#ifdef GPIOF
    port_cnt++;
#endif

#ifdef GPIOG
    port_cnt++;
#endif

#ifdef GPIOH
    port_cnt++;
#endif

#ifdef GPIOI
    port_cnt++;
#endif

#ifdef GPIOJ
    port_cnt++;
#endif

#ifdef GPIOK
    port_cnt++;
#endif

#ifdef GPIOL
    port_cnt++;
#endif
    return port_cnt;
}

bool gpio_is_valid_pad(const Pad_t Pad) {
    bool res = false;
    uint8_t port_cnt = gpio_port_cnt_get();
    if(Pad.port < port_cnt) {
        if(Pad.pin <= GPIO_PIN_COUNT) {
            res = true;
        }
    }
    return res;
}

const GpioPortInfo_t* GpioGetPortInfo(const GpioPort_t port) {
    GpioPortInfo_t* Info = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(GPIOxInfo);
    for(i = 0; i < cnt; i++) {
        if(port == GPIOxInfo[i].port) {
            if(GPIOxInfo[i].valid) {
                Info = &GPIOxInfo[i];
                break;
            }
        }
    }
    return Info;
}

static GpioPullMode_t GpioStm32Pull2GeneralPull(GpioStm32Pull_t stm32_pull_code) {
    GpioPullMode_t general_pull_code = GPIO__PULL_UNDEF;
    switch(stm32_pull_code) {
    case STM32_PULL_AIR:
        general_pull_code = GPIO__PULL_AIR;
        break;
    case STM32_PULL_UP:
        general_pull_code = GPIO__PULL_UP;
        break;
    case STM32_PULL_DOWN:
        general_pull_code = GPIO__PULL_DOWN;
        break;
    case STM32_PULL_UNDEF:
        general_pull_code = GPIO__PULL_UNDEF;
        break;
    default:
#ifdef HAS_LOG
        LOG_ERROR(GPIO, "UndefSTMPullMode %u", stm32_pull_code);
#endif
        break;
    }
    return general_pull_code;
}

static GpioStm32Mode_t gpio_stm_mode_get(Pad_t pad) {
    GpioStm32Mode_t stm_mode = GP_STM32_MODE_UNDEF;
    GPIO_TypeDef* GPIOx = GpioPortToPortPtr(pad.port);
    if(GPIOx) {
        uint32_t code = 0;
        uint32_t reg_mode = GPIOx->MODER;
#ifdef HAS_LOG
        LOG_DEBUG(GPIO, "MODER:0x%x", reg_mode);
#endif
        code = MASK_2BIT & (reg_mode >> (2 * pad.pin));
#ifdef HAS_LOG
        LOG_DEBUG(GPIO, "stm_mode:%u", code);
#endif
        stm_mode = (GpioStm32Mode_t)code;
    }
    return stm_mode;
}

#ifdef HAS_PINS
bool gpio_clock_init(void) {
    bool res = false;
#ifdef HAS_LOG
    LOG_WARNING(GPIO, "ClockInit");
#endif
    uint8_t cnt = 0;
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "Clock On");
#endif /*HAS_LOG*/

#ifdef GPIOA
    __HAL_RCC_GPIOA_CLK_ENABLE();
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "A ClkOn");
#endif /*HAS_LOG*/
    cnt++;
#endif

#ifdef GPIOB
    __HAL_RCC_GPIOB_CLK_ENABLE();
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "B ClkOn");
#endif /*HAS_LOG*/
    cnt++;
#endif

#ifdef GPIOC
    __HAL_RCC_GPIOC_CLK_ENABLE();
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "C ClkOn");
#endif /*HAS_LOG*/
    cnt++;
#endif

#ifdef GPIOD
    __HAL_RCC_GPIOD_CLK_ENABLE();
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "D ClkOn");
#endif /*HAS_LOG*/
    cnt++;
#endif

#ifdef GPIOE
    __HAL_RCC_GPIOE_CLK_ENABLE();
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "E ClkOn");
#endif /*HAS_LOG*/
    cnt++;
#endif

#ifdef GPIOF
    __HAL_RCC_GPIOF_CLK_ENABLE();
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "F ClkOn");
#endif /*HAS_LOG*/
    cnt++;
#endif

#ifdef GPIOG
    __HAL_RCC_GPIOG_CLK_ENABLE();
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "G ClkOn");
#endif /*HAS_LOG*/
    cnt++;
#endif

#ifdef GPIOH
    __HAL_RCC_GPIOH_CLK_ENABLE();
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "H ClkOn");
#endif /*HAS_LOG*/
    cnt++;
#endif
    if(cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}
#endif /*HAS_PINS*/

uint32_t PinNum2PinMask(uint8_t pin_num) {
    uint32_t pin_mask = 0;
    pin_mask |= (1 << pin_num);
    return pin_mask;
}

static GpioApiMode_t GpioStmModeToMode(GpioStm32Mode_t stm_mode) {
    GpioApiMode_t mode = GPIO_API_MODE_UNDEF;
    switch(stm_mode) {
    case GP_STM32_MODE_INPUT:
        mode = GPIO_API_MODE_INPUT;
        break;
    case GP_STM32_MODE_GNRL_PURPOSE_OUT:
        mode = GPIO_API_MODE_OUTPUT;
        break;
    case GP_STM32_MODE_ALT_FUN:
        mode = GPIO_API_MODE_ALT1;
        break;
    case GP_STM32_MODE_ANALOG:
        mode = GPIO_API_MODE_ANALOG;
        break;
    default:
        break;
    }
    return mode;
}

static GpioStm32Pull_t GpioPull2Stm32Pull(GpioPullMode_t pull_code) {
    GpioStm32Pull_t stm32_pull_code = STM32_PULL_UNDEF;
    switch(pull_code) {
    case GPIO__PULL_AIR:
        stm32_pull_code = STM32_PULL_AIR;
        break;
    case GPIO__PULL_UP:
        stm32_pull_code = STM32_PULL_UP;
        break;
    case GPIO__PULL_DOWN:
        stm32_pull_code = STM32_PULL_DOWN;
        break;
    case GPIO__PULL_UNDEF:
        stm32_pull_code = STM32_PULL_UNDEF;
        break;
    default:
        break;
    }
    return stm32_pull_code;
}

GpioDir_t gpio_dir_get(Pad_t Pad) {
    GpioDir_t dir = GPIO_DIR_UNDEF;
    GpioStm32Mode_t mode = gpio_stm_mode_get(Pad);
    dir = GpioStmDirToDir(mode);
    return dir;
}

static GpioSpeed_t GpioStmSpeedToSpeed(GpioStm32Speed_t stm_speed) {
    GpioSpeed_t speed = GPIO_SPEED_UNDEF;
    switch(stm_speed) {
    case SPEED_LOW_SPEED:
        speed = GPIO_SPEED_LOW_SPEED;
        break;
    case SPEED_MEDIUM_SPEED:
        speed = GPIO_SPEED_MEDIUM_SPEED;
        break;
    case SPEED_FAST_SPEED:
        speed = GPIO_SPEED_FAST_SPEED;
        break;
    case SPEED_HIGH_SPEED:
        speed = GPIO_SPEED_HIGH_SPEED;
        break;
    default:
        break;
    }
    return speed;
}

static uint32_t GpioModeToStm32Mode(GpioApiMode_t mode) {
    uint32_t stm_mode = 0;
    switch(mode) {

    case GPIO_API_MODE_INPUT_EXINT_BOTH_EDGE:
        stm_mode = GPIO_MODE_IT_RISING_FALLING;
        break;

    case GPIO_API_MODE_INPUT_EXINT_FAILLING:
        stm_mode = GPIO_MODE_IT_FALLING;
        break;

    case GPIO_API_MODE_INPUT_EXINT:
        stm_mode = GPIO_MODE_IT_RISING_FALLING;
        break;

    case GPIO_API_MODE_INPUT_EXINT_RISING:
        stm_mode = GPIO_MODE_IT_RISING;
        break;

    case GPIO_API_MODE_GPIO:
        stm_mode = GPIO_MODE_OUTPUT_PP;
        break;

    case GPIO_API_MODE_OUTPUT:
        stm_mode = GPIO_MODE_OUTPUT_PP;
        break;

    case GPIO_API_MODE_I2C:
        stm_mode = GPIO_MODE_AF_OD;
        break;

    case GPIO_API_MODE_INPUT:
        stm_mode = GPIO_MODE_INPUT;
        break;

    case GPIO_API_MODE_ALT1:
        stm_mode = GPIO_MODE_AF_PP;
        break;

    case GPIO_API_MODE_HW_PWM:
        stm_mode = GPIO_MODE_AF_PP;
        break;

    case GPIO_API_MODE_ANALOG:
        stm_mode = GPIO_MODE_ANALOG;
        break;
    default:
        break;
    } // switch(mode)
    return stm_mode;
}

GPIO_TypeDef* GpioPortToPortPtr(const GpioPort_t port) {
    GPIO_TypeDef* GPIOx = NULL;
    const GpioPortInfo_t* Info = GpioGetPortInfo(port);
    if(Info) {
        GPIOx = Info->GPIOx;
    }
    return GPIOx;
}

static uint32_t gpio_pin_mux_lh_set(const uint32_t afr_lh, const uint8_t pin, const uint8_t mux) {
    GpioRegAFR_LH_t AFR_LH;
    AFR_LH.dword = afr_lh;
    switch(pin) {
    case 0:
        AFR_LH.AFR_LH_0_8 = mux;
        break;
    case 1:
        AFR_LH.AFR_LH_1_9 = mux;
        break;
    case 2:
        AFR_LH.AFR_LH_2_10 = mux;
        break;
    case 3:
        AFR_LH.AFR_LH_3_11 = mux;
        break;
    case 4:
        AFR_LH.AFR_LH_4_12 = mux;
        break;
    case 5:
        AFR_LH.AFR_LH_5_13 = mux;
        break;
    case 6:
        AFR_LH.AFR_LH_6_14 = mux;
        break;
    case 7:
        AFR_LH.AFR_LH_7_15 = mux;
        break;
    default:
        break;
    }
    return AFR_LH.dword;
}

bool gpio_mode_set(const Pad_t Pad, const GpioApiMode_t mode) {
    bool res = false;
    uint32_t stm_mode = GpioModeToStm32Mode(mode);
    const GpioPortInfo_t* Info = GpioGetPortInfo(Pad.port);
    if(Info) {
        GpioRegMODE_t MODE;
        MODE.dword = Info->GPIOx->MODER;
        switch(Pad.pin) {
        case 0:
            MODE.pin0_mode = stm_mode;
            res = true;
            break;
        case 1:
            MODE.pin1_mode = stm_mode;
            res = true;
            break;
        case 2:
            MODE.pin2_mode = stm_mode;
            res = true;
            break;
        case 3:
            MODE.pin3_mode = stm_mode;
            res = true;
            break;
        case 4:
            MODE.pin4_mode = stm_mode;
            res = true;
            break;
        case 5:
            MODE.pin5_mode = stm_mode;
            res = true;
            break;
        case 6:
            MODE.pin6_mode = stm_mode;
            res = true;
            break;
        case 7:
            MODE.pin7_mode = stm_mode;
            res = true;
            break;
        case 8:
            MODE.pin8_mode = stm_mode;
            res = true;
            break;
        case 9:
            MODE.pin9_mode = stm_mode;
            res = true;
            break;
        case 10:
            MODE.pin10_mode = stm_mode;
            res = true;
            break;
        case 11:
            MODE.pin11_mode = stm_mode;
            res = true;
            break;
        case 12:
            MODE.pin12_mode = stm_mode;
            res = true;
            break;
        case 13:
            MODE.pin13_mode = stm_mode;
            res = true;
            break;
        case 14:
            MODE.pin14_mode = stm_mode;
            res = true;
            break;
        case 15:
            MODE.pin15_mode = stm_mode;
            res = true;
            break;
        default:
            res = false;
            break;
        }
        Info->GPIOx->MODER = MODE.dword;
    }
    return res;
}

GpioApiMode_t gpio_pin_mux_to_mode(const uint8_t mux) {
    GpioApiMode_t mode = GPIO_API_MODE_GPIO;
    if(mux) {
        mode = GPIO_API_MODE_ALT1;
    }
    return mode;
}

bool gpio_pin_mux_set(GpioPort_t port, uint8_t pin, uint8_t mux) {
    bool res = false;
    GpioApiMode_t mode = gpio_pin_mux_to_mode(mux);
    Pad_t Pad = {
        .port = port,
        .pin = pin,
    };
    res = gpio_mode_set(Pad, mode);

    GpioPortInfo_t* Info = GpioGetPortInfo(port);
    if(Info) {
        // 8.3.2 I/O pin multiplexer and mapping
        if(pin <= 7) {
            GpioRegAFRL_t AFRL;
            AFRL.dword = Info->GPIOx->AFR[0];
            AFRL.dword = gpio_pin_mux_lh_set(AFRL.dword, pin, mux);
            Info->GPIOx->AFR[0] = AFRL.dword;
            res = true;
        } else if((8 <= pin) && (pin <= 15)) {
            GpioRegAFRH_t AFRH;
            AFRH.dword = Info->GPIOx->AFR[1];
            AFRH.dword = gpio_pin_mux_lh_set(AFRH.dword, pin - 8, mux);
            Info->GPIOx->AFR[1] = AFRH.dword;
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}

bool gpio_pad_mux_set(const Pad_t Pad, const uint8_t mux) {
    bool res = false;
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "Set,%s,Mux:%u", GpioPadToStr(Pad), mux);
#endif
    res = gpio_pin_mux_set(Pad.port, Pad.pin, mux);
    return res;
}

/* Get Pin Mux */
AltFunc_t gpio_get_alt(Pad_t pad) {
    AltFunc_t alt_fun = {0};
    alt_fun.byte = 0;
    GPIO_TypeDef* GPIOx = GpioPortToPortPtr(pad.port);
    if(GPIOx) {
        uint8_t code = 0, offset = 0;
        uint32_t reg_mode = 0;
        if(pad.pin <= 7) {
            /*see 8.4.9 GPIO alternate function low register (GPIOx_AFRL) (x = A..I/J/K), Address offset: 0x20*/
            reg_mode = GPIOx->AFR[0];
            offset = 4 * pad.pin;
        } else if((8 <= pad.pin) && (pad.pin <= 15)) {
            /*see 8.4.10 GPIO alternate function high register (GPIOx_AFRH), Address offset: 0x24*/
            reg_mode = GPIOx->AFR[1];
            offset = 4 * (pad.pin - 8);
        } else {
            reg_mode = 0;
        }
        code = MASK_4BIT & (reg_mode >> offset);
        alt_fun.code = code;
    }
    return alt_fun;
}

/*can be called from isr*/
bool gpio_get_state(const Pad_t pad, GpioLogicLevel_t* const logic_level) {
#ifdef HAS_GPIO_DIAG
    // LOG_DEBUG(GPIO, "Get,P%s%u", GpioPortToStr(pad.port), pad.pin);
#endif
    GPIO_PinState value = HAL_GPIO_ReadPin(GpioPortToPortPtr(pad.port), 1 << pad.pin);
    (*logic_level) = (uint8_t)value;
    return true;
}

/*can be called from isr*/
GpioLogicLevel_t gpio_get_state_short(const Pad_t pad) {
#ifdef HAS_GPIO_DIAG
    // LOG_DEBUG(GPIO, "Get,P%s%u", GpioPortToStr(pad.port), pad.pin);
#endif
    GpioLogicLevel_t logic_level = GPIO_LVL_UNDEF;
    GPIO_PinState value = HAL_GPIO_ReadPin(GpioPortToPortPtr(pad.port), 1 << pad.pin);
    logic_level = (uint8_t)value;
    return logic_level;
}

uint32_t gpio_read(Pad_t pad) {
    uint32_t ret = 0;
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "Get P%s%u", GpioPortToStr(pad.port), pad.pin);
#endif
    GPIO_PinState value = HAL_GPIO_ReadPin(GpioPortToPortPtr(pad.port), 1 << pad.pin);
    ret = (uint32_t)value;
    return ret;
}

bool gpio_logic_level_set(Pad_t pad, GpioLogicLevel_t logic_level) {
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "Set P%s%u LL:%u", GpioPortToStr(pad.port), pad.pin, logic_level);
#endif
    HAL_GPIO_WritePin(GpioPortToPortPtr(pad.port), 1 << pad.pin, (GPIO_PinState)logic_level);
    return true;
}

bool is_edge_irq_en(Pad_t Pad) {
    bool res = false;
    return res;
}

bool gpio_pin_mux_get(const Pad_t Pad, uint8_t* const mux) {
    bool res = false;
    if(mux) {
        AltFunc_t alt = gpio_get_alt(Pad);
        *mux = alt.code;
        res = true;
    }
    return res;
}

bool pin_get_int(uint8_t pin) {
    bool res = false;
    uint32_t reg_val = EXTI->IMR;
    if(CHECK_BIT_NUM(reg_val, pin)) {
        res = true;
    }
    return res;
}

bool pin_get_int_pend(uint8_t pin) {
    bool res = false;
    uint32_t reg_val = EXTI->PR;
    if(CHECK_BIT_NUM(reg_val, pin)) {
        res = true;
    }
    return res;
}

#ifdef HAS_EXT_INT
PinIntEdge_t pin_get_edge(uint8_t pin) {
    PinIntEdge_t edge = PIN_INT_EDGE_UNDEF;
    uint32_t rreg_val = EXTI->RTSR; // 0200
    uint32_t freg_val = EXTI->FTSR;
    Type8Union_t code;
    code.u8 = 0;
    if(CHECK_BIT_NUM(freg_val, pin)) {
        code.bits8.bit0 = 1;
    }
    if(CHECK_BIT_NUM(rreg_val, pin)) {
        code.bits8.bit1 = 1;
    }

    switch(MASK_2BIT & code.u8) {
    case 0:
        edge = PIN_INT_EDGE_NONE;
        break;
    case 1:
        edge = PIN_INT_EDGE_FALLING;
        break;
    case 2:
        edge = PIN_INT_EDGE_RISING;
        break;
    case 3:
        edge = PIN_INT_EDGE_BOTH;
        break;
    default:
        break;
    }

    return edge;
}
#endif

OutType_t gpio_get_out_type(Pad_t pad) {
    OutType_t out_type = OUT_TYPE_UNDEF;
    GPIO_TypeDef* GPIOx = GpioPortToPortPtr(pad.port);
    if(GPIOx) {
        uint32_t code = 0;
        uint32_t reg_mode = GPIOx->OTYPER;
        code = MASK_1BIT & (reg_mode >> (pad.pin));
        out_type = (OutType_t)code;
    }
    return out_type;
}

GpioApiMode_t gpio_mode_get(Pad_t Pad) {
    GpioApiMode_t mode = GPIO_API_MODE_UNDEF;
    GpioStm32Mode_t stm_mode = gpio_stm_mode_get(Pad);
    mode = GpioStmModeToMode(stm_mode);
#ifdef HAS_LOG
    LOG_DEBUG(GPIO, "mode:%u", mode);
#endif
    return mode;
}

static GpioStm32Speed_t gpio_stm_speed_get(Pad_t pad) {
    GpioStm32Speed_t mode = SPEED_UNDEF;
    GPIO_TypeDef* GPIOx = GpioPortToPortPtr(pad.port);
    if(GPIOx) {
        uint32_t code = 0;
        uint32_t reg_mode = GPIOx->OSPEEDR;
        code = MASK_2BIT & (reg_mode >> (2 * pad.pin));
        mode = (GpioStm32Speed_t)code;
    }
    return mode;
}

GpioSpeed_t gpio_speed_get(Pad_t Pad) {
    GpioSpeed_t speed = GPIO_SPEED_UNDEF;
    GpioStm32Speed_t stm_speed = gpio_stm_speed_get(Pad);
    speed = GpioStmSpeedToSpeed(stm_speed);
    return speed;
}

GpioPullMode_t gpio_pull_get(Pad_t pad) {
    GpioPullMode_t mode = GPIO__PULL_UNDEF;
    GPIO_TypeDef* GPIOx = GpioPortToPortPtr(pad.port);
    if(GPIOx) {
        uint32_t code = 0;
        uint32_t reg_mode = GPIOx->PUPDR;
#ifdef HAS_LOG
        LOG_DEBUG(GPIO, "PUPDR 0x%x", reg_mode);
#endif
        code = MASK_2BIT & (reg_mode >> (2 * pad.pin));
#ifdef HAS_LOG
        LOG_DEBUG(GPIO, "STMPullCode 0x%x", code);
#endif
        mode = GpioStm32Pull2GeneralPull((GpioStm32Pull_t)code);
#ifdef HAS_LOG
        LOG_DEBUG(GPIO, "mode 0x%x", mode);
#endif
    } else {
#ifdef HAS_GPIO_DIAG
        LOG_ERROR(GPIO, "PortErr P%s", GpioPortToStr(pad.port));
#endif
    }
    return mode;
}

bool gpio_pull_set(Pad_t pad, GpioPullMode_t pull_mode) {
    bool res = false;

#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "Set Pad %s, Pull %s", GpioPadToStr(pad), GpioPullToStr(pull_mode));
#endif
    GpioStm32Pull_t stm_pull_mode = GpioPull2Stm32Pull(pull_mode);
    volatile GPIO_TypeDef* GPIOx = GpioPortToPortPtr(pad.port);
    if(GPIOx) {
        uint32_t reg_mode = GPIOx->PUPDR;
        uint32_t new_reg_mode = GPIOx->PUPDR;
#ifdef HAS_LOG
        LOG_DEBUG(GPIO, "Old PUPDR 0x%x", new_reg_mode);
        LOG_DEBUG(GPIO, "pin %u", pad.pin);
#endif
        uint8_t min_bit = 2 * pad.pin;
#ifdef HAS_LOG
        LOG_DEBUG(GPIO, "min_bit %u,  StmPullCode %u", min_bit, stm_pull_mode);
#endif
        new_reg_mode = insert_subval_in_32bit(reg_mode, (uint32_t)stm_pull_mode, min_bit + 1, min_bit);
#ifdef HAS_LOG
        LOG_DEBUG(GPIO, "New PUPDR 0x%x", new_reg_mode);
#endif
        GPIOx->PUPDR = new_reg_mode;
        res = true;
    }
    return res;
}

bool generate_sw_int(uint32_t mask) {
    bool res = true;
    __HAL_GPIO_EXTI_GENERATE_SWIT(mask);
    return res;
}

bool ext_int_set_mask(uint32_t mask) {
    bool res = true;
    EXTI->IMR |= mask;
    return res;
}

bool ext_int_reset_mask(uint32_t mask) {
    bool res = true;
    EXTI->IMR &= ~mask;
    return res;
}

bool gpio_toggle(const Pad_t Pad) {
    bool res = false;
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "Toggle,%s", GpioPadToStr(Pad));
#endif

    HAL_GPIO_TogglePin(GpioPortToPortPtr(Pad.port), 1 << Pad.pin);
    res = true;
    return res;
}

bool gpio_toggle_slow(Pad_t Pad) {
    bool res = false;
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "Toggle,%s", GpioPadToStr(Pad));
#endif
    GPIO_PinState value = HAL_GPIO_ReadPin(GpioPortToPortPtr(Pad.port), 1 << Pad.pin);
    switch(value) {
    case GPIO_PIN_RESET:
        HAL_GPIO_WritePin(GpioPortToPortPtr(Pad.port), 1 << Pad.pin, GPIO_PIN_SET);
        res = true;
        break;
    case GPIO_PIN_SET:
        HAL_GPIO_WritePin(GpioPortToPortPtr(Pad.port), 1 << Pad.pin, GPIO_PIN_RESET);
        res = true;
        break;
    default:
        break;
    }
    return res;
}

bool gpio_config_one(Pad_t pad, uint32_t Mode, uint32_t Pull, uint32_t Speed, uint32_t Alternate,
                     GPIO_PinState PinState) {
    bool res = false;
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_TypeDef* GPIOx = GpioPortToPortPtr(pad.port);
    if(GPIOx) {
#ifdef HAS_GPIO_DIAG
        LOG_WARNING(GPIO, "InitPad %s", GpioPadToStr(pad));
#endif
        /*Configure GPIO pin Output Level */
        uint32_t pin_mask = PinNum2PinMask(pad.pin);
        HAL_GPIO_WritePin(GPIOx, pin_mask, PinState);

        /*Configure GPIO pin : PtPin */
        GPIO_InitStruct.Pin = pin_mask;
        GPIO_InitStruct.Mode = Mode;
        GPIO_InitStruct.Pull = Pull;
        GPIO_InitStruct.Speed = Speed;
        GPIO_InitStruct.Alternate = Alternate;
        HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
        res = true;
    } else {
#ifdef HAS_LOG
        LOG_ERROR(GPIO, "NoPad");
#endif
    }

    return res;
}

static GPIO_PinState LogicLevel2PinState(GpioLogicLevel_t logic_level) {
    GPIO_PinState pin_state = GPIO_PIN_RESET;
    switch(logic_level) {
    case GPIO_LVL_LOW:
        pin_state = GPIO_PIN_RESET;
        break;
    case GPIO_LVL_HI:
        pin_state = GPIO_PIN_SET;
        break;
    default:
        break;
    }
    return pin_state;
}

#if 0
bool gpio_dir_set(Pad_t Pad, GpioDir_t dir) {
    bool res = false;
    return res;
}
#endif

bool gpio_init_out_pad(const Pad_t Pad) {
    bool res = false;
#ifdef HAS_GPIO_DIAG
    LOG_INFO(GPIO, "Init,%s,ADC", GpioPadToStr(Pad));
#endif
    GPIO_TypeDef* GPIOx = GpioPortToPortPtr(Pad.port);
    if(GPIOx) {
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        uint32_t pin_mask = PinNum2PinMask(Pad.pin);
        GPIO_InitStruct.Pin = pin_mask;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = 0;
        HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
        res = true;
    }
    return res;
}

bool gpio_init_input(const Pad_t Pad) {
    bool res = false;
#ifdef HAS_GPIO_DIAG
    LOG_INFO(GPIO, "Init,%s,IN", GpioPadToStr(Pad));
#endif
    GPIO_TypeDef* GPIOx = GpioPortToPortPtr(Pad.port);
    if(GPIOx) {
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        uint32_t pin_mask = PinNum2PinMask(Pad.pin);
        GPIO_InitStruct.Pin = pin_mask;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = 0;
        HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
        res = true;
    }
    return res;
}

bool gpio_init_adc_pad(const Pad_t Pad) {
    bool res = false;
#ifdef HAS_GPIO_DIAG
    LOG_INFO(GPIO, "Init,%s,ADC", GpioPadToStr(Pad));
#endif
    GPIO_TypeDef* GPIOx = GpioPortToPortPtr(Pad.port);
    if(GPIOx) {
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        uint32_t pin_mask = PinNum2PinMask(Pad.pin);
        GPIO_InitStruct.Pin = pin_mask;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
        GPIO_InitStruct.Alternate = 0;
        HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
        res = true;
    }
    return res;
}

bool gpio_init_ext_int(const Pad_t Pad) {
    bool res = false;
#ifdef HAS_GPIO_DIAG
    LOG_INFO(GPIO, "Init,%s,ExtInt", GpioPadToStr(Pad));
#endif
    GPIO_TypeDef* GPIOx = GpioPortToPortPtr(Pad.port);
    if(GPIOx) {
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        uint32_t pin_mask = PinNum2PinMask(Pad.pin);
        GPIO_InitStruct.Pin = pin_mask;
        GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = 0;
        HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
        res = true;
    }
    return res;
}

bool gpio_deinit_pad(const Pad_t Pad) {
    bool res = false;
    GPIO_TypeDef* GPIOx = GpioPortToPortPtr(Pad.port);
    if(GPIOx) {
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        uint32_t pin_mask = PinNum2PinMask(Pad.pin);
        GPIO_InitStruct.Pin = pin_mask;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = STM32_PULL_UP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = 0;
        HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
        res = true;
    }
    return res;
}

bool gpio_init_one(const GpioConfig_t* const Config) {
    bool res = false;
    if(Config) {
#ifdef HAS_GPIO_DIAG
        LOG_WARNING(GPIO, "%s", GpioConfigToStr(Config));
#endif
        res = gpio_is_valid_pad(Config->Pad);
#ifdef HAS_DEBUGGER
        ASSERT_CRITICAL(true == res);
#endif
        if(res) {
            res = gpio_is_pin_single(Config->Pad);
            if(res) {
                res = false;
                GPIO_TypeDef* GPIOx = GpioPortToPortPtr(Config->Pad.port);
                if(GPIOx) {
                    /*Configure GPIO pin Output Level */
                    uint32_t pin_mask = PinNum2PinMask(Config->Pad.pin);
                    GPIO_PinState pin_state = LogicLevel2PinState(Config->logic_level);
                    HAL_GPIO_WritePin(GPIOx, pin_mask, pin_state);
                    /*Configure GPIO pin : PtPin */
                    res = gpio_is_valid_mode(Config->mode);
#ifdef HAS_DEBUGGER
                    ASSERT_CRITICAL(true == res);
#endif
                    if(res) {
                        GPIO_InitTypeDef GPIO_InitStruct = {0};
                        GPIO_InitStruct.Pin = pin_mask;
                        GPIO_InitStruct.Mode = GpioModeToStm32Mode(Config->mode);
                        GPIO_InitStruct.Pull = GpioPull2Stm32Pull(Config->pull);
                        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH; // Config->speed;
                        GPIO_InitStruct.Alternate = Config->mux;
                        HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
                    } else {
                        res = false;
                    }
                }
            } else {
#ifdef HAS_GPIO_DIAG
                LOG_ERROR(GPIO, "ReDefine,P%s%u", GpioPortToStr(Config->Pad.port), Config->Pad.pin);
#endif
            }
        }
    }
    return res;
}
