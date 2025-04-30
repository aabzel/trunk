#include "gpio_mcal.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "bit_utils.h"
#include "board_config.h"
#include "data_utils.h"
#ifdef HAS_DEBUGGER
#include "debugger.h"
#endif
#include "gpio_config.h"

#include "gpio_custom_drv.h"
#include "gpio_custom_isr.h"

#include "gpio_custom_types.h"
#ifdef HAS_LOG
#include "log.h"
#endif
#include "stm32f4xx_hal.h"

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
    }
    return dirr;
}

static PinInt_t PinInt[] = {
    {.gpio_pin = 0, .int_cnt = 0},  {.gpio_pin = 1, .int_cnt = 0},  {.gpio_pin = 2, .int_cnt = 0},
    {.gpio_pin = 3, .int_cnt = 0},  {.gpio_pin = 4, .int_cnt = 0},  {.gpio_pin = 5, .int_cnt = 0},
    {.gpio_pin = 6, .int_cnt = 0},  {.gpio_pin = 7, .int_cnt = 0},  {.gpio_pin = 8, .int_cnt = 0},
    {.gpio_pin = 9, .int_cnt = 0},  {.gpio_pin = 10, .int_cnt = 0}, {.gpio_pin = 11, .int_cnt = 0},
    {.gpio_pin = 12, .int_cnt = 0}, {.gpio_pin = 13, .int_cnt = 0}, {.gpio_pin = 14, .int_cnt = 0},
    {.gpio_pin = 15, .int_cnt = 0},
};

PinInt_t* PinIntGetNode(uint16_t gpio_pin) {
    PinInt_t* Node = NULL;
    uint8_t i = 0;
    for(i = 0; i < ARRAY_SIZE(PinInt); i++) {
        if(gpio_pin == PinInt[i].gpio_pin) {
            Node = &PinInt[i];
            break;
        }
    }
    return Node;
}
#if 0
static bool is_valid_stm_mode(uint32_t stm_mode) {
    bool res = false;
    switch(stm_mode) {
    case GPIO_MODE_INPUT:
        res = true;
        break;
    case GPIO_MODE_OUTPUT_PP:
        res = true;
        break;
    case GPIO_MODE_OUTPUT_OD:
        res = true;
        break;
    case GPIO_MODE_AF_PP:
        res = true;
        break;
    case GPIO_MODE_AF_OD:
        res = true;
        break;
    case GPIO_MODE_ANALOG:
        res = true;
        break;
    case GPIO_MODE_IT_RISING:
        res = true;
        break;
    case GPIO_MODE_IT_FALLING:
        res = true;
        break;
    case GPIO_MODE_IT_RISING_FALLING:
        res = true;
        break;
    case GPIO_MODE_EVT_RISING:
        res = true;
        break;
    case GPIO_MODE_EVT_FALLING:
        res = true;
        break;
    case GPIO_MODE_EVT_RISING_FALLING:
        res = true;
        break;
    }
    return res;
}
#endif

static GpioPullMode_t GpioStm32Pull2GeneralPull(GpioStm32Pull_t stm32_pull_code) {
    GpioPullMode_t general_pull_code = GPIO__PULL_UNDEF;
    switch((uint32_t)stm32_pull_code) {
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
        LOG_ERROR(GPIO, "UndefSTMPullMode %u", stm32_pull_code);
        break;
    }
    return general_pull_code;
}

static GpioStm32Mode_t gpio_stm_mode_get(uint8_t pad_num) {
    GpioStm32Mode_t stm_mode = GP_STM32_MODE_UNDEF;
    Pad_t pad;
    pad.byte = pad_num;
    GPIO_TypeDef* GPIOx = Port2PortPtr(pad.port);
    if(GPIOx) {
        uint32_t code = 0;
        uint32_t reg_mode = GPIOx->MODER;
        LOG_DEBUG(GPIO, "MODER:0x%x", reg_mode);
        code = MASK_2BIT & (reg_mode >> (2 * pad.pin));
        LOG_DEBUG(GPIO, "stm_mode:%u", code);
        stm_mode = (GpioStm32Mode_t)code;
    }
    return stm_mode;
}

#ifdef HAS_PINS
bool gpio_clock_init(void) {
    bool res = false;
    LOG_WARNING(GPIO, "ClockInit");
    uint8_t cnt = 0;
#ifdef HAS_GPIO_DIAG
    LOG_INFO(GPIO, "Clock On");
#endif /*HAS_LOG*/

#ifdef GPIOA
    __HAL_RCC_GPIOA_CLK_ENABLE();
#ifdef HAS_GPIO_DIAG
    LOG_INFO(GPIO, "A ClkOn");
#endif /*HAS_LOG*/
    cnt++;
#endif

#ifdef GPIOB
    __HAL_RCC_GPIOB_CLK_ENABLE();
#ifdef HAS_GPIO_DIAG
    LOG_INFO(GPIO, "B ClkOn");
#endif /*HAS_LOG*/
    cnt++;
#endif

#ifdef GPIOC
    __HAL_RCC_GPIOC_CLK_ENABLE();
#ifdef HAS_GPIO_DIAG
    LOG_INFO(GPIO, "C ClkOn");
#endif /*HAS_LOG*/
    cnt++;
#endif

#ifdef GPIOD
    __HAL_RCC_GPIOD_CLK_ENABLE();
#ifdef HAS_GPIO_DIAG
    LOG_INFO(GPIO, "D ClkOn");
#endif /*HAS_LOG*/
    cnt++;
#endif

#ifdef GPIOE
    __HAL_RCC_GPIOE_CLK_ENABLE();
#ifdef HAS_GPIO_DIAG
    LOG_INFO(GPIO, "E ClkOn");
#endif /*HAS_LOG*/
    cnt++;
#endif

#ifdef GPIOF
    __HAL_RCC_GPIOF_CLK_ENABLE();
#ifdef HAS_GPIO_DIAG
    LOG_INFO(GPIO, "F ClkOn");
#endif /*HAS_LOG*/
    cnt++;
#endif

#ifdef GPIOG
    __HAL_RCC_GPIOG_CLK_ENABLE();
#ifdef HAS_GPIO_DIAG
    LOG_INFO(GPIO, "G ClkOn");
#endif /*HAS_LOG*/
    cnt++;
#endif

#ifdef GPIOH
    __HAL_RCC_GPIOH_CLK_ENABLE();
#ifdef HAS_GPIO_DIAG
    LOG_INFO(GPIO, "H ClkOn");
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
    switch((uint8_t)pull_code) {
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
    }
    return stm32_pull_code;
}

GpioDir_t gpio_dir_get(uint8_t pad_num) {
    GpioDir_t dir = GPIO_DIR_UNDEF;
    GpioStm32Mode_t mode = gpio_stm_mode_get(pad_num);
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
    switch((uint32_t)mode) {
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
    case GPIO_API_MODE_INPUT_EXINT:
        stm_mode = GPIO_MODE_IT_RISING;
        break;
    default:
        break;
    } // switch(mode)
    return stm_mode;
}

GPIO_TypeDef* Port2PortPtr(Port_t port_num) {
    GPIO_TypeDef* GpioPort = NULL;
    switch((uint8_t)port_num) {
#ifdef GPIOA
    case PORT_A:
        GpioPort = GPIOA;
        break;
#endif

#ifdef GPIOB
    case PORT_B:
        GpioPort = GPIOB;
        break;
#endif

#ifdef GPIOC
    case PORT_C:
        GpioPort = GPIOC;
        break;
#endif

#ifdef GPIOD
    case PORT_D:
        GpioPort = GPIOD;
        break;
#endif

#ifdef GPIOE
    case PORT_E:
        GpioPort = GPIOE;
        break;
#endif

#ifdef GPIOF
    case PORT_F:
        GpioPort = GPIOF;
        break;
#endif

#ifdef GPIOG
    case PORT_G:
        GpioPort = GPIOG;
        break;
#endif

#ifdef GPIOH
    case PORT_H:
        GpioPort = GPIOH;
        break;
#endif

    default:
        break;
    }
    return GpioPort;
}

bool gpio_get_state(uint8_t pad_num, GpioLogicLevel_t* logic_level) {
    Pad_t pad;
    pad.byte = pad_num;
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "Get,P%s%u", GpioPort2Str(pad.port), pad.pin);
#endif
    GPIO_PinState value = HAL_GPIO_ReadPin(Port2PortPtr(pad.port), 1 << pad.pin);
    (*logic_level) = (uint8_t)value;
    return true;
}

uint32_t gpio_read(uint8_t pad_num) {
    uint32_t ret = 0;
    Pad_t pad;
    pad.byte = pad_num;
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "Get P%s%u", GpioPort2Str(pad.port), pad.pin);
#endif
    GPIO_PinState value = HAL_GPIO_ReadPin(Port2PortPtr(pad.port), 1 << pad.pin);
    ret = (uint32_t)value;
    return ret;
}

bool gpio_logic_level_set(Pad_t pad, GpioLogicLevel_t logic_level) {
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "Set P%s%u LL:%u", GpioPort2Str(pad.port), pad.pin, logic_level);
#endif
    HAL_GPIO_WritePin(Port2PortPtr(pad.port), 1 << pad.pin, (GPIO_PinState)logic_level);
    return true;
}

bool is_edge_irq_en(uint8_t dio_pin) {
    bool res = false;
    return res;
}

AltFunc_t gpio_get_alt(uint8_t pad_num) {
    AltFunc_t alt_fun;
    alt_fun.byte = 0;
    Pad_t pad;
    pad.byte = pad_num;
    GPIO_TypeDef* GPIOx = Port2PortPtr(pad.port);
    if(GPIOx) {
        uint8_t code = 0, offset = 0;
        uint32_t reg_mode = 0;
        if(pad.pin <= 7) {
            reg_mode = GPIOx->AFR[0];
            offset = 4 * pad.pin;
        } else if((8 <= pad.pin) && (pad.pin <= 15)) {
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

bool gpio_pin_mux_get(uint8_t port, uint8_t pin, uint8_t* const mux) {
    Pad_t Pad = {
        .port = port,
        .pin = pin,
    };
    bool res = false;
    if(mux) {
        res = true;
        AltFunc_t alt = gpio_get_alt(Pad.byte);
        *mux = alt.code;
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
    }

    return edge;
}
#endif

OutType_t gpio_get_out_type(uint8_t pad_num) {
    OutType_t out_type = OUT_TYPE_UNDEF;
    Pad_t pad;
    pad.byte = pad_num;
    GPIO_TypeDef* GPIOx = Port2PortPtr(pad.port);
    if(GPIOx) {
        uint32_t code = 0;
        uint32_t reg_mode = GPIOx->OTYPER;
        code = MASK_1BIT & (reg_mode >> (pad.pin));
        out_type = (OutType_t)code;
    }
    return out_type;
}

GpioApiMode_t gpio_mode_get(uint8_t pad_num) {
    GpioApiMode_t mode = GPIO_API_MODE_UNDEF;
    GpioStm32Mode_t stm_mode = gpio_stm_mode_get(pad_num);
    mode = GpioStmModeToMode(stm_mode);
    LOG_DEBUG(GPIO, "mode:%u", mode);
    return mode;
}

static GpioStm32Speed_t gpio_stm_speed_get(uint8_t pad_num) {
    GpioStm32Speed_t mode = SPEED_UNDEF;
    Pad_t pad;
    pad.byte = pad_num;
    GPIO_TypeDef* GPIOx = Port2PortPtr(pad.port);
    if(GPIOx) {
        uint32_t code = 0;
        uint32_t reg_mode = GPIOx->OSPEEDR;
        code = MASK_2BIT & (reg_mode >> (2 * pad.pin));
        mode = (GpioStm32Speed_t)code;
    }
    return mode;
}

GpioSpeed_t gpio_speed_get(uint8_t pad_num) {
    GpioSpeed_t speed = GPIO_SPEED_UNDEF;
    GpioStm32Speed_t stm_speed = gpio_stm_speed_get(pad_num);
    speed = GpioStmSpeedToSpeed(stm_speed);
    return speed;
}

GpioPullMode_t gpio_pull_get(uint8_t pad_num) {
    GpioPullMode_t mode = GPIO__PULL_UNDEF;
    Pad_t pad;
    pad.byte = pad_num;
    GPIO_TypeDef* GPIOx = Port2PortPtr(pad.port);
    if(GPIOx) {
        uint32_t code = 0;
        uint32_t reg_mode = GPIOx->PUPDR;
        LOG_DEBUG(GPIO, "PUPDR 0x%x", reg_mode);
        code = MASK_2BIT & (reg_mode >> (2 * pad.pin));
        LOG_DEBUG(GPIO, "STMPullCode 0x%x", code);
        mode = GpioStm32Pull2GeneralPull((GpioStm32Pull_t)code);
        LOG_DEBUG(GPIO, "mode 0x%x", mode);
    } else {
#ifdef HAS_GPIO_DIAG
        LOG_ERROR(GPIO, "PortErr P%s", GpioPort2Str(pad.port));
#endif
    }
    return mode;
}

bool gpio_pull_set(Pad_t pad, GpioPullMode_t pull_mode) {
    bool res = false;


#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "Set Pad %s, Pull %s", GpioPad2Str(pad.byte), GpioPull2Str(pull_mode));
#endif
    GpioStm32Pull_t stm_pull_mode = GpioPull2Stm32Pull(pull_mode);
    volatile GPIO_TypeDef* GPIOx = Port2PortPtr(pad.port);
    if(GPIOx) {
        uint32_t reg_mode = GPIOx->PUPDR;
        uint32_t new_reg_mode = GPIOx->PUPDR;
        LOG_DEBUG(GPIO, "Old PUPDR 0x%x", new_reg_mode);
        LOG_DEBUG(GPIO, "pin %u", pad.pin);
        uint8_t min_bit = 2 * pad.pin;
        LOG_DEBUG(GPIO, "min_bit %u,  StmPullCode %u", min_bit, stm_pull_mode);
        new_reg_mode = insert_subval_in_32bit(reg_mode, (uint32_t)stm_pull_mode, min_bit + 1, min_bit);
        LOG_DEBUG(GPIO, "New PUPDR 0x%x", new_reg_mode);
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

#if 0
bool gpio_toggle(uint8_t pad_num) {
    bool res = false;
    Pad_t pad;
    pad.byte = pad_num;
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "Toggle P%s%u", GpioPort2Str(pad.port), pad.pin);
#endif
    GPIO_PinState value = HAL_GPIO_ReadPin(Port2PortPtr(pad.port), 1 << pad.pin);
    switch(value) {
    case GPIO_PIN_RESET:
        HAL_GPIO_WritePin(Port2PortPtr(pad.port), 1 << pad.pin, GPIO_PIN_SET);
        res = true;
        break;
    case GPIO_PIN_SET:
        HAL_GPIO_WritePin(Port2PortPtr(pad.port), 1 << pad.pin, GPIO_PIN_RESET);
        res = true;
        break;
    default:
        break;
    }
    return res;
}

#endif

bool gpio_config_one(Pad_t pad, uint32_t Mode, uint32_t Pull, uint32_t Speed, uint32_t Alternate,
                     GPIO_PinState PinState) {
    bool res = false;
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_TypeDef* GpioPort = Port2PortPtr(pad.port);
    if(GpioPort) {
#ifdef HAS_GPIO_DIAG
        LOG_WARNING(GPIO, "InitPad %s", GpioPad2Str(pad.byte));
#endif
        /*Configure GPIO pin Output Level */
        uint32_t pin_mask = PinNum2PinMask(pad.pin);
        HAL_GPIO_WritePin(GpioPort, pin_mask, PinState);

        /*Configure GPIO pin : PtPin */
        GPIO_InitStruct.Pin = pin_mask;
        GPIO_InitStruct.Mode = Mode;
        GPIO_InitStruct.Pull = Pull;
        GPIO_InitStruct.Speed = Speed;
        GPIO_InitStruct.Alternate = Alternate;
        HAL_GPIO_Init(GpioPort, &GPIO_InitStruct);
        res = true;
    } else {
        LOG_ERROR(GPIO, "NoPad");
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
bool gpio_dir_set(uint8_t pad_num, GpioDir_t dir) {
    bool res = false;
    return res;
}
#endif

bool gpio_is_valid_pad(uint8_t pad_num) {
    bool res = false;
    Pad_t Pad = {.byte = pad_num};
    if(Pad.pin <= GPIO_PIN_COUNT) {
        if(Pad.port <= PORT_H) {
            res = true;
        }
    }
    return res;
}

bool gpio_init_one(const GpioConfig_t* const Config) {
    bool res = false;
    if(Config) {
#ifdef HAS_GPIO_DIAG
        // gpio_diag_conf(Config);
#endif
        res = gpio_is_valid_pad(Config->pad.byte);
#ifdef HAS_DEBUGGER
        ASSERT_CRITICAL(true == res);
#endif
        if(res) {
            res = gpio_is_pin_single(Config->pad.byte);
            if(res) {
                res = false;
                GPIO_TypeDef* GpioPort = Port2PortPtr(Config->pad.port);
                if(GpioPort) {
                    /*Configure GPIO pin Output Level */
                    uint32_t pin_mask = PinNum2PinMask(Config->pad.pin);
                    GPIO_PinState pin_state = LogicLevel2PinState(Config->logic_level);
                    HAL_GPIO_WritePin(GpioPort, pin_mask, pin_state);
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
                        HAL_GPIO_Init(GpioPort, &GPIO_InitStruct);
                    } else {
                        res = false;
                    }
                }
            } else {
#ifdef HAS_GPIO_DIAG
                LOG_ERROR(GPIO, "ReDefine P%s%u", GpioPort2Str(Config->pad.port), Config->pad.pin);
#endif
            }
        }
    }
    return res;
}
