#include "gpio_drv.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "bit_utils.h"
#include "board_config.h"
#include "data_utils.h"
#include "gpio_config.h"
#include "gpio_const.h"
#include "gpio_isr.h"
#include "gpio_stm32_drv.h"
#ifdef HAS_GPIO_DIAG
#include "gpio_general_diag.h"
#include "gpio_stm32_diag.h"
#endif

#include "gpio_stm_types.h"
#ifdef HAS_LOG
#include "log.h"
#endif
#include "at32f435_437.h"

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

static GpioPullMode_t GpioStm32Pull2GeneralPull(GpioStm32Pull_t stm32_pull_code) {
    GpioPullMode_t general_pull_code = GPIO__PULL_UNDEF;
    switch((uint8_t)stm32_pull_code) {
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
    }
    return general_pull_code;
}

#ifdef HAS_PINS
static bool gpio_clock_init(void) {
    bool res = false;
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
    LOG_DEBUG(GPIO, "Get P%s%u", GpioPort2Str(pad.port), pad.pin);
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

bool gpio_set_state(uint8_t pad_num, GpioLogicLevel_t logic_level) {
    Pad_t pad;
    pad.byte = pad_num;
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

GpioDir_t gpio_get_dir(uint8_t pad_num) {
    GpioDir_t dirr = GPIO_DIR_UNDEF;
    GpioStm32Mode_t mode = gpio_get_mode(pad_num);
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

GpioStm32Mode_t gpio_get_mode(uint8_t pad_num) {
    GpioStm32Mode_t pin_mode = GP_STM32_MODE_UNDEF;
    Pad_t pad;
    pad.byte = pad_num;
    GPIO_TypeDef* GPIOx = Port2PortPtr(pad.port);
    if(GPIOx) {
        uint32_t code = 0;
        uint32_t reg_mode = GPIOx->MODER;
        code = MASK_2BIT & (reg_mode >> (2 * pad.pin));
        pin_mode = (GpioStm32Mode_t)code;
    }
    return pin_mode;
}

GpioStm32Speed_t gpio_get_speed(uint8_t pad_num) {
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

static GpioStm32Pull_t GpioPull2Stm32Pull(GpioPullMode_t pull_code) {
    GpioStm32Pull_t stm32_pull_code = GPIO__PULL_UNDEF;
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

GpioPullMode_t gpio_get_pull(uint8_t pad_num) {
    GpioStm32Pull_t mode = STM32_PULL_UNDEF;
    Pad_t pad;
    pad.byte = pad_num;
    GPIO_TypeDef* GPIOx = Port2PortPtr(pad.port);
    if(GPIOx) {
        uint32_t code = 0;
        uint32_t reg_mode = GPIOx->PUPDR;
        code = MASK_2BIT & (reg_mode >> (2 * pad.pin));
        mode = GpioStm32Pull2GeneralPull((GpioStm32Pull_t)code);
    } else {
#ifdef HAS_GPIO_DIAG
        LOG_ERROR(GPIO, "PortErr P%s", GpioPort2Str(pad.port));
#endif
    }
    return mode;
}

bool gpio_set_pull(uint8_t pad_num, GpioPullMode_t pull_mode) {
    bool res = false;
    Pad_t pad;
    GpioStm32Pull_t stm_pull_mode = GpioPull2Stm32Pull(pull_mode);
    pad.byte = pad_num;
    GPIO_TypeDef* GPIOx = Port2PortPtr(pad.port);
    if(GPIOx) {
        uint32_t reg_mode = GPIOx->PUPDR;
        uint32_t new_reg_mode = GPIOx->PUPDR;
        uint8_t min_bit = 2 * pad.pin;
        new_reg_mode = insert_subval_in_32bit(reg_mode, (uint32_t)stm_pull_mode, min_bit + 1, min_bit);
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
#if 0
bool gpio_is_pin_single(uint8_t byte) {
    bool res = false;
    uint32_t i = 0, pin_cnt = 0;
    uint32_t pin_real_cnt = 0;
    pin_cnt = pin_get_cnt();
    for(i = 0; i < pin_cnt; i++) {
        if(byte == GpioConfigLut[i].pad.byte) {
            pin_real_cnt++;
        }
    }
    if(1 == pin_real_cnt) {
        res = true;
    } else {
        res = false;
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
        LOG_INFO(GPIO, "InitPad %s", GpioPad2Str(pad.byte));
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

bool gpio_init_one(const GpioConfig_t* Inst) {
    bool res = false;
    if(Inst) {
        res = gpio_is_pin_single(Inst->pad.byte);
        if(res) {
            res = false;
            GPIO_InitTypeDef GPIO_InitStruct = {0};
            GPIO_TypeDef* GpioPort = Port2PortPtr(Inst->pad.port);
            if(GpioPort) {
                /*Configure GPIO pin Output Level */
                uint32_t pin_mask = PinNum2PinMask(Inst->pad.pin);
                GPIO_PinState pin_state = LogicLevel2PinState(Inst->logic_level);
                HAL_GPIO_WritePin(GpioPort, pin_mask, pin_state);

                /*Configure GPIO pin : PtPin */
                GPIO_InitStruct.Pin = pin_mask;
                GPIO_InitStruct.Mode = Inst->mode;
                GPIO_InitStruct.Pull = GpioPull2Stm32Pull(Inst->gpio_pull);
                GPIO_InitStruct.Speed = Inst->speed;
                GPIO_InitStruct.Alternate = Inst->alternate;
                HAL_GPIO_Init(GpioPort, &GPIO_InitStruct);
                res = true;
            }
        } else {
#ifdef HAS_GPIO_DIAG
            LOG_ERROR(GPIO, "ReDefine P%s%u", GpioPort2Str(Inst->pad.port), Inst->pad.pin);
#endif
        }
    }
    return res;
}

bool gpio_init(void) {
    bool res = false;
#ifdef HAS_GPIO_DIAG
    LOG_INFO(GPIO, "Init");
#endif
#ifdef HAS_PINS
    gpio_clock_init();
    gpio_int_cnt = 0;
    uint32_t i = 0, cnt_ok = 0;
    uint32_t pin_cnt = gpio_get_cnt();
    for(i = 0; i < pin_cnt; i++) {
        res = gpio_init_one(&GpioConfigLut[i]);
        if(res) {
            cnt_ok++;
        }
    }
    if(pin_cnt == cnt_ok) {
        res = true;
    }
#endif /*HAS_PINS*/
    return res;
}

bool gpio_set_dir(uint8_t pad_num, GpioDir_t dir) {
    bool res = false;
    return res;
}

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
