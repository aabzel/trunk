#include "gpio_mcal.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

//#include "c_defines_generated.h"
#include "bit_utils.h"

#include "board_config.h"
#include "data_utils.h"
#ifdef HAS_DEBUGGER
#include "debugger.h" //For assert
#endif
#include "artery_at32f4xx.h"
#include "gpio_custom_drv.h"
#include "gpio_isr.h"
#include "log.h"
#ifdef HAS_AT32F413
#include "gpio_at32f413_mcal.h"
#endif

#ifdef HAS_SCFG
#define GPIO_SCFG_PORT_SOURCE_NUM(LETTER) .port_source = SCFG_PORT_SOURCE_GPIO##LETTER,
#else
#define GPIO_SCFG_PORT_SOURCE_NUM(LETTER)
#endif

#define GPIO_INFO_COMPOSE(XXXX)                                                                                         \
    {                                                                                                                   \
        GPIO_SCFG_PORT_SOURCE_NUM(XXXX).valid = true, .port = PORT_##XXXX, .clock_type = CRM_GPIO##XXXX##_PERIPH_CLOCK, \
        .clock_type = CRM_GPIO##XXXX##_PERIPH_CLOCK,  .GPIOx = GPIO##XXXX,                                              \
    },

#ifdef GPIOE
#define GPIOE_INFO_COMPOSE GPIO_INFO_COMPOSE(E)
#else
// some MCU does not have GPIO PORT E
#define GPIOE_INFO_COMPOSE
#endif

#ifdef GPIOH
#define GPIOH_INFO_COMPOSE GPIO_INFO_COMPOSE(H)
#else
// some MCU does not have GPIO PORT H
#define GPIOH_INFO_COMPOSE
#endif

#ifdef GPIOG
#define GPIOG_INFO_COMPOSE GPIO_INFO_COMPOSE(G)
#else
// some MCU does not have GPIO PORT G
#define GPIOG_INFO_COMPOSE
#endif

#define GPIO_INFO_ALL                                                                                                  \
    GPIO_INFO_COMPOSE(A)                                                                                               \
    GPIO_INFO_COMPOSE(B)                                                                                               \
    GPIO_INFO_COMPOSE(C)                                                                                               \
    GPIO_INFO_COMPOSE(D)                                                                                               \
    GPIOE_INFO_COMPOSE                                                                                                 \
    GPIO_INFO_COMPOSE(F)                                                                                               \
    GPIOG_INFO_COMPOSE                                                                                                 \
    GPIOH_INFO_COMPOSE

static const GpioInfo_t GpioInfo[] = {
    GPIO_INFO_ALL
    //   {.valid=true, .port=PORT_A, .clock_type=CRM_GPIOA_PERIPH_CLOCK, .GPIOx=GPIOA,},
    //   {.valid=true, .port=PORT_B, .clock_type=CRM_GPIOB_PERIPH_CLOCK, .GPIOx=GPIOB,},
    //   {.valid=true, .port=PORT_C, .clock_type=CRM_GPIOC_PERIPH_CLOCK, .GPIOx=GPIOC,},
    //   {.valid=true, .port=PORT_D, .clock_type=CRM_GPIOD_PERIPH_CLOCK, .GPIOx=GPIOD,},
    //   {.valid=true, .port=PORT_E, .clock_type=CRM_GPIOE_PERIPH_CLOCK, .GPIOx=GPIOE,},
    //   {.valid=true, .port=PORT_F, .clock_type=CRM_GPIOF_PERIPH_CLOCK, .GPIOx=GPIOF,},
    //   {.valid=true, .port=PORT_G, .clock_type=CRM_GPIOG_PERIPH_CLOCK, .GPIOx=GPIOG,},
    //   {.valid=true, .port=PORT_H, .clock_type=CRM_GPIOH_PERIPH_CLOCK, .GPIOx=GPIOH,},
};

#ifdef HAS_AT32F43X
static GpioApiMode_t GpioArteryModeToMode(GpioAt32Mode_t at32_mode) {
    GpioApiMode_t mode = GPIO_API_MODE_UNDEF;
    switch((uint32_t)at32_mode) {
    case GP_AT32_MODE_INPUT: {
        mode = GPIO_API_MODE_INPUT;
    } break;
    case GP_AT32_MODE_GNRL_PURPOSE_OUT: {
        mode = GPIO_API_MODE_OUTPUT;
    } break;
    case GP_AT32_MODE_ALT_FUN: {
        mode = GPIO_API_MODE_ALT1;
    } break;
    case GP_AT32_MODE_ANALOG: {
        mode = GPIO_API_MODE_ANALOG;
    } break;
    }
    return mode;
}
#endif

const GpioInfo_t* GpioGetPortInfo(Port_t port) {
    const GpioInfo_t* Node = NULL;
    uint8_t i = 0;
    for(i = 0; i < ARRAY_SIZE(GpioInfo); i++) {
        if(GpioInfo[i].valid) {
            if(port == GpioInfo[i].port) {
                Node = &GpioInfo[i];
                break;
            }
        }
    }
    return Node;
}

GpioPullMode_t GpioAt32Pull2GeneralPull(gpio_pull_type at32_pull_code) {
    GpioPullMode_t general_pull_code = GPIO__PULL_UNDEF;
    switch((uint8_t)at32_pull_code) {
    case GPIO_PULL_NONE:
        general_pull_code = GPIO__PULL_AIR;
        break;
    case GPIO_PULL_UP:
        general_pull_code = GPIO__PULL_UP;
        break;
    case GPIO_PULL_DOWN:
        general_pull_code = GPIO__PULL_DOWN;
        break;
    default:
        LOG_ERROR(GPIO, "UndefAT32PullMode %u", at32_pull_code);
        break;
    }
    return general_pull_code;
}

#if 0
static crm_periph_clock_type PortToClockType(Port_t port) {
    crm_periph_clock_type clock_type = 0;

    GpioInfo_t* Info = GpioGetPortInfo(port);
    if(Info) {
        clock_type = Info->clock_type;
    }

    return clock_type;
}
#endif

static GpioLogicLevel_t GpioAt32LlToGpioLl(flag_status status) {
    GpioLogicLevel_t logic_level = GPIO_LVL_UNDEF;
    switch((uint8_t)status) {
    case RESET:
        logic_level = GPIO_LVL_LOW;
        break;
    case SET:
        logic_level = GPIO_LVL_HI;
        break;
    }
    return logic_level;
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
    crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
#ifdef HAS_GPIO_DIAG
    LOG_INFO(GPIO, "A ClkOn");
#endif /*HAS_LOG*/
    cnt++;
#endif

#ifdef GPIOB
    crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
#ifdef HAS_GPIO_DIAG
    LOG_INFO(GPIO, "B ClkOn");
#endif /*HAS_LOG*/
    cnt++;
#endif

#ifdef GPIOC
    crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
#ifdef HAS_GPIO_DIAG
    LOG_INFO(GPIO, "C ClkOn");
#endif /*HAS_LOG*/
    cnt++;
#endif

#ifdef GPIOD
    crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
#ifdef HAS_GPIO_DIAG
    LOG_INFO(GPIO, "D ClkOn");
#endif /*HAS_LOG*/
    cnt++;
#endif

#ifdef GPIOE
    crm_periph_clock_enable(CRM_GPIOE_PERIPH_CLOCK, TRUE);
#ifdef HAS_GPIO_DIAG
    LOG_INFO(GPIO, "E ClkOn");
#endif /*HAS_LOG*/
    cnt++;
#endif

#ifdef GPIOF
    crm_periph_clock_enable(CRM_GPIOF_PERIPH_CLOCK, TRUE);
#ifdef HAS_GPIO_DIAG
    LOG_INFO(GPIO, "F ClkOn");
#endif /*HAS_LOG*/
    cnt++;
#endif

#ifdef GPIOG
    crm_periph_clock_enable(CRM_GPIOG_PERIPH_CLOCK, TRUE);
#ifdef HAS_GPIO_DIAG
    LOG_INFO(GPIO, "G ClkOn");
#endif /*HAS_LOG*/
    cnt++;
#endif

#ifdef GPIOH
    crm_periph_clock_enable(CRM_GPIOH_PERIPH_CLOCK, TRUE);
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

gpio_type* Port2PortPtr(Port_t port) {
    gpio_type* GPIOx = NULL;
    GpioInfo_t* Info = GpioGetPortInfo(port);
    if(Info) {
        GPIOx = Info->GPIOx;
    }
    return GPIOx;
}

bool gpio_get_state(uint8_t pad_num, GpioLogicLevel_t* logic_level) {
    Pad_t pad = {0};
    (void)pad;
    bool res = false;
    pad.byte = pad_num;
#ifdef HAS_GPIO_DIAG
    // LOG_DEBUG(GPIO, "Get P%s%u", GpioPort2Str(pad.port), pad.pin);
#endif
    gpio_type* PORTx = Port2PortPtr(pad.port);
    if(PORTx) {
        if(logic_level) {
            flag_status status = gpio_input_data_bit_read(PORTx, ((uint16_t)1) << pad.pin);
            (*logic_level) = GpioAt32LlToGpioLl(status);
            res = true;
        }
    }
    return res;
}

uint32_t gpio_read(uint8_t pad_num) {
    uint32_t ret = 0;
    Pad_t pad = {0};
    (void)pad;
    pad.byte = pad_num;
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "Get P%s%u", GpioPort2Str(pad.port), pad.pin);
#endif
    // GPIO_PinState value = HAL_GPIO_ReadPin(Port2PortPtr(pad.port), 1 << pad.pin);
    ret = (uint32_t)0;
    return ret;
}

/*can be called from isr*/
bool gpio_logic_level_set(uint8_t pad_num, GpioLogicLevel_t logic_level) {
    Pad_t pad = {0};
    (void)pad;
    pad.byte = pad_num;
#ifdef HAS_GPIO_DIAG
    // LOG_DEBUG(GPIO, "Set P%s%u LL:%u", GpioPort2Str(pad.port), pad.pin, logic_level);
#endif
    gpio_type* GPIOx = Port2PortPtr(pad.port);
    if(GPIOx) {
        switch((uint8_t)logic_level) {
        case GPIO_LVL_HI: {
            GPIOx->scr = 1 << pad.pin;
        } break;
        case GPIO_LVL_LOW: {
            GPIOx->clr = 1 << pad.pin;
        } break;
        }
    }
    return true;
}

bool is_edge_irq_en(uint8_t dio_pin) {
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

OutType_t gpio_get_out_type(uint8_t pad_num) {
    OutType_t out_type = OUT_TYPE_UNDEF;
    return out_type;
}

GpioApiMode_t gpio_mode_get(uint8_t pad_num) {
    Pad_t Pad;
    GpioApiMode_t pin_mode = GPIO_API_MODE_UNDEF;
    Pad.byte = pad_num;
    /*  GPIO configuration register (GPIOx_CFGR)*/
    gpio_type* GPIOx = Port2PortPtr(Pad.port);
    if(GPIOx) {
#ifdef HAS_AT32F43X
        GpioAt32Mode_t at32_mode = GP_AT32_MODE_UNDEF;
        switch(Pad.pin) {
        case 0: {
            at32_mode = GPIOx->cfgr_bit.iomc0;
        } break;
        case 1: {
            at32_mode = GPIOx->cfgr_bit.iomc1;
        } break;
        case 2: {
            at32_mode = GPIOx->cfgr_bit.iomc2;
        } break;
        case 3: {
            at32_mode = GPIOx->cfgr_bit.iomc3;
        } break;
        case 4: {
            at32_mode = GPIOx->cfgr_bit.iomc4;
        } break;
        case 5: {
            at32_mode = GPIOx->cfgr_bit.iomc5;
        } break;
        case 6: {
            at32_mode = GPIOx->cfgr_bit.iomc6;
        } break;
        case 7: {
            at32_mode = GPIOx->cfgr_bit.iomc7;
        } break;
        case 8: {
            at32_mode = GPIOx->cfgr_bit.iomc8;
        } break;
        case 9: {
            at32_mode = GPIOx->cfgr_bit.iomc9;
        } break;
        case 10: {
            at32_mode = GPIOx->cfgr_bit.iomc10;
        } break;
        case 11: {
            at32_mode = GPIOx->cfgr_bit.iomc11;
        } break;
        case 12: {
            at32_mode = GPIOx->cfgr_bit.iomc12;
        } break;
        case 13: {
            at32_mode = GPIOx->cfgr_bit.iomc13;
        } break;
        case 14: {
            at32_mode = GPIOx->cfgr_bit.iomc14;
        } break;
        case 15: {
            at32_mode = GPIOx->cfgr_bit.iomc15;
        } break;
        }
        pin_mode = GpioArteryModeToMode(at32_mode);
#else
        pin_mode = gpio_at32f413_mode_get(Pad);
#endif

    } else {

    } // if(GPIOx)
    return pin_mode;
}

GpioDir_t gpio_dir_get(uint8_t pad_num) {
    GpioDir_t dirr = GPIO_DIR_UNDEF;
#ifdef HAS_AT32F413
    Pad_t Pad;
    Pad.byte = pad_num;
    dirr = gpio_at32f413_dir_get(Pad);
#endif

#ifdef HAS_AT32F43X
    GpioApiMode_t mode = gpio_mode_get(pad_num);
    switch((uint8_t)mode) {
    case GPIO_API_MODE_GPIO:
        dirr = GPIO_DIR_UNDEF;
        break;

    case GPIO_API_MODE_I2C:
    case GPIO_API_MODE_ALT1:
    case GPIO_API_MODE_ALT2:
        dirr = GPIO_DIR_UNDEF;
        break;

    case GPIO_API_MODE_INPUT:
    case GPIO_API_MODE_ANALOG:
        dirr = GPIO_DIR_IN;
        break;

    case GPIO_API_MODE_HW_PWM:
    case GPIO_API_MODE_OUTPUT:
        dirr = GPIO_DIR_OUT;
        break;
    }
#endif
    return dirr;
}

GpioAt32Speed_t gpio_get_speed(uint8_t pad_num) {
    GpioAt32Speed_t mode = SPEED_UNDEF;
    Pad_t pad;
    pad.byte = pad_num;
    gpio_type* GPIOx = Port2PortPtr(pad.port);
    if(GPIOx) {
        /*TODO*/
    }
    return mode;
}

static gpio_pull_type GpioPullToAt32Pull(GpioPullMode_t pull_code) {
    gpio_pull_type at32_pull_code = GPIO_PULL_NONE;
    switch((uint8_t)pull_code) {
    case GPIO__PULL_AIR:
        at32_pull_code = GPIO_PULL_NONE;
        break;
    case GPIO__PULL_UP:
        at32_pull_code = GPIO_PULL_UP;
        break;
    case GPIO__PULL_DOWN:
        at32_pull_code = GPIO_PULL_DOWN;
        break;
    case GPIO__PULL_BOTH:
        at32_pull_code = GPIO_PULL_NONE;
        break;
    case GPIO__PULL_UNDEF:
        at32_pull_code = GPIO_PULL_NONE;
        break;
    }
    return at32_pull_code;
}

GpioPullMode_t gpio_pull_get(uint8_t pad_num) {
    GpioPullMode_t mode = GPIO__PULL_UNDEF;
    Pad_t Pad;
    Pad.byte = pad_num;
    gpio_type* GPIOx = Port2PortPtr(Pad.port);
    if(GPIOx) {
#ifdef HAS_AT32F43X
        uint32_t code = 0;
        switch(Pad.pin) {
        case 0:
            code = GPIOx->pull_bit.pull0;
            break;
        case 1:
            code = GPIOx->pull_bit.pull1;
            break;
        case 2:
            code = GPIOx->pull_bit.pull2;
            break;
        case 3:
            code = GPIOx->pull_bit.pull3;
            break;
        case 4:
            code = GPIOx->pull_bit.pull4;
            break;
        case 5:
            code = GPIOx->pull_bit.pull5;
            break;
        case 6:
            code = GPIOx->pull_bit.pull6;
            break;
        case 7:
            code = GPIOx->pull_bit.pull7;
            break;
        case 8:
            code = GPIOx->pull_bit.pull8;
            break;
        case 9:
            code = GPIOx->pull_bit.pull9;
            break;
        case 10:
            code = GPIOx->pull_bit.pull10;
            break;
        case 11:
            code = GPIOx->pull_bit.pull11;
            break;
        case 12:
            code = GPIOx->pull_bit.pull12;
            break;
        case 13:
            code = GPIOx->pull_bit.pull13;
            break;
        case 14:
            code = GPIOx->pull_bit.pull14;
            break;
        case 15:
            code = GPIOx->pull_bit.pull15;
            break;
        }

        LOG_DEBUG(GPIO, "AT32PullCode 0x%x", code);
        mode = GpioAt32Pull2GeneralPull((gpio_pull_type)code);
        LOG_DEBUG(GPIO, "mode 0x%x", mode);
#else        // HAS_AT32F43X
        mode = gpio_at32f413_pull_get(Pad);
#endif       // HAS_AT32F43X
    } else { // if(GPIOx) {
#ifdef HAS_GPIO_DIAG
        LOG_ERROR(GPIO, "PortErr P%s", GpioPort2Str(Pad.port));
#endif
    }
    return mode;
}

bool generate_sw_int(uint32_t mask) {
    bool res = true;
    // __HAL_GPIO_EXTI_GENERATE_SWIT(mask);
    return res;
}

bool gpio_pin_fun_get(Pad_t Pad, GpioPinFunction_t* const function) {
    bool res = true;
#ifdef HAS_AT32F413
    res = gpio_at32f413_pin_fun_get(Pad, function);
#endif
    return res;
}

bool ext_int_set_mask(uint32_t mask) {
    bool res = true;
    //  EXTI->IMR |= mask;
    return res;
}

bool ext_int_reset_mask(uint32_t mask) {
    bool res = true;
    //  EXTI->IMR &= ~mask;
    return res;
}


GpioAt32Pull_t GpioPullToArteryPull(GpioPullMode_t pull_mode) {
    GpioAt32Pull_t at32_pull = AT32_PULL_UNDEF;
    switch((uint32_t)pull_mode) {
    case GPIO__PULL_AIR:
        at32_pull = AT32_PULL_AIR;
        break;
    case GPIO__PULL_UP:
        at32_pull = AT32_PULL_UP;
        break;
    case GPIO__PULL_DOWN:
        at32_pull = AT32_PULL_DOWN;
        break;
    case GPIO__PULL_BOTH:
        at32_pull = AT32_PULL_AIR;
        break;

    default:
        break;
    }

    return at32_pull;
}

bool gpio_pull_set(uint8_t pad_num, GpioPullMode_t pull_mode) {
    bool res = false;
    Pad_t pad;
    pad.byte = pad_num;
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "Set Pad %u=%s, Pull %s", pad_num, GpioPad2Str(pad.byte), GpioPull2Str(pull_mode));
#endif
    // gpio_pull_type at32_pull_mode = GpioPullToAt32Pull(pull_mode);
    volatile gpio_type* GPIOx = Port2PortPtr(pad.port);
    if(GPIOx) {
        res = gpio_is_valid_pull(pull_mode);
        if(res) {

#ifdef HAS_AT32F43X
            uint8_t code = GpioPullToArteryPull(pull_mode);
            switch(pad.pin) {
            case 0: {
                GPIOx->pull_bit.pull0 = code;
            } break;
            case 1: {
                GPIOx->pull_bit.pull1 = code;
            } break;
            case 2: {
                GPIOx->pull_bit.pull2 = code;
            } break;
            case 3: {
                GPIOx->pull_bit.pull3 = code;
            } break;
            case 4: {
                GPIOx->pull_bit.pull4 = code;
            } break;
            case 5: {
                GPIOx->pull_bit.pull5 = code;
            } break;
            case 6: {
                GPIOx->pull_bit.pull6 = code;
            } break;
            case 7: {
                GPIOx->pull_bit.pull7 = code;
            } break;
            case 8: {
                GPIOx->pull_bit.pull8 = code;
            } break;
            case 9: {
                GPIOx->pull_bit.pull9 = code;
            } break;
            case 10: {
                GPIOx->pull_bit.pull10 = code;
            } break;
            case 11: {
                GPIOx->pull_bit.pull11 = code;
            } break;
            case 12: {
                GPIOx->pull_bit.pull12 = code;
            } break;
            case 13: {
                GPIOx->pull_bit.pull13 = code;
            } break;
            case 14: {
                GPIOx->pull_bit.pull14 = code;
            } break;
            case 15: {
                GPIOx->pull_bit.pull15 = code;
            } break;
            default: {
            } break;
            }

            res = true;
#endif
        }
    }
    return res;
}

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

static gpio_output_type GpioModeToAt32OutType(GpioDir_t dirr) {
    gpio_output_type output_type = GPIO_MODE_INPUT;
    switch((uint8_t)dirr) {
    case GPIO_DIR_OUT:
        output_type = GPIO_OUTPUT_PUSH_PULL;
        break;
    case GPIO_DIR_OUT_PUSH_PULL:
        output_type = GPIO_OUTPUT_PUSH_PULL;
        break;
    case GPIO_DIR_INOUT:
        output_type = GPIO_OUTPUT_PUSH_PULL;
        break;
    case GPIO_DIR_NONE:
        output_type = GPIO_OUTPUT_PUSH_PULL;
        break;
    case GPIO_DIR_IN:
        output_type = GPIO_OUTPUT_PUSH_PULL;
        break;
    case GPIO_DIR_INOUT_OPEN_DRAIN:
        output_type = GPIO_OUTPUT_OPEN_DRAIN;
        break;
    case GPIO_DIR_OUT_OPEN_DRAIN:
        output_type = GPIO_OUTPUT_OPEN_DRAIN;
        break;
    }
    return output_type;
}

static gpio_mode_type GpioModeToAt32Mode(GpioApiMode_t mode) {
    gpio_mode_type gpio_mode = GPIO_MODE_INPUT;
    switch((uint8_t)mode) {
    case GPIO_API_MODE_GPIO:
        gpio_mode = GPIO_MODE_OUTPUT;
        break;
    case GPIO_API_MODE_ALT1:
        gpio_mode = GPIO_MODE_MUX;
        break;
    case GPIO_API_MODE_ALT2:
        gpio_mode = GPIO_MODE_MUX;
        break;
    case GPIO_API_MODE_HW_PWM:
        gpio_mode = GPIO_MODE_MUX;
        break;
    case GPIO_API_MODE_OUTPUT:
        gpio_mode = GPIO_MODE_OUTPUT;
        break;
    case GPIO_API_MODE_INPUT_EXINT:
    case GPIO_API_MODE_INPUT:
        gpio_mode = GPIO_MODE_INPUT;
        break;
    case GPIO_API_MODE_ANALOG:
        gpio_mode = GPIO_MODE_ANALOG;
        break;
    }
    return gpio_mode;
}

bool gpio_init_custom(void) {
    bool res = false;
    return res;
}

bool gpio_deinit_one(Pad_t Pad) {
    bool res = false;
    res = false;
    gpio_type* GPIOx = Port2PortPtr(Pad.port);
    if(GPIOx) {
        const GpioInfo_t* Info = GpioGetPortInfo(Pad.port);
        if(Info) {
            crm_periph_clock_enable(Info->clock_type, TRUE);
#ifdef HAS_GPIO_DIAG
            LOG_INFO(GPIO, "%s,ClkOn", GpioPort2Str(Pad.port));
#endif
        }
        /*Configure GPIO pin Output Level */
        uint32_t pin_mask = PinNum2PinMask(Pad.pin);

        gpio_init_type GpioInitStruct = {0};
        gpio_default_para_init(&GpioInitStruct);

        GpioInitStruct.gpio_pins = pin_mask;
        GpioInitStruct.gpio_mode = GpioModeToAt32Mode(GPIO_API_MODE_INPUT);
        GpioInitStruct.gpio_pull = GpioPullToAt32Pull(GPIO__PULL_AIR);
        GpioInitStruct.gpio_out_type = GpioModeToAt32OutType(GPIO_DIR_IN);
        GpioInitStruct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
        gpio_init(GPIOx, &GpioInitStruct);
#ifdef HAS_AT32F43X
        gpio_pin_mux_config(GPIOx, ((gpio_pins_source_type)Pad.pin), GPIO_MUX_0);
#endif
        res = gpio_logic_level_set(Pad.byte, GPIO_LVL_LOW);

        // res = true;
    }

    return res;
}

bool gpio_pin_mux_set(uint8_t port, uint8_t pin, uint8_t mux) {
    bool res = false;
    gpio_type* GPIOx = Port2PortPtr(port);
    if(GPIOx) {
#ifdef HAS_AT32F43X
        gpio_pin_mux_config(GPIOx, ((gpio_pins_source_type)pin), (gpio_mux_sel_type)mux);
        res = true;
#endif
    }
    return res;
}

bool gpio_pin_mux_get(uint8_t port, uint8_t pin, uint8_t* const mux) {
    bool res = false;
    uint8_t mux_val = 0;
    gpio_type* GPIOx = Port2PortPtr(port);
    if(GPIOx) {
#ifdef HAS_AT32F43X
        if(pin <= 7) {
            mux_val = MASK_4BIT & (GPIOx->muxl >> (pin * 4));
            res = true;
        } else if(pin <= 15) {
            mux_val = MASK_4BIT & (GPIOx->muxh >> ((pin - 8) * 4));
            res = true;
        } else {
            res = false;
        }
#else
        Pad_t Pad = {
            .port = port,
            .pin = pin,
        };
        res = gpio_at32f413_pin_mux_get(Pad, mux);
#endif

#if 0
        switch(pin){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7: {
            mux_val= MASK_4BIT & (GPIOx->muxl>>(pin*4));
            res = true;
        } break;
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:{
            mux_val= MASK_4BIT & (   GPIOx->muxh>>((pin-8)*4));
            res = true;

        } break;
        default:  {
        } break;
        }
#endif
    }

    if(res) {
        *mux = mux_val;
    } else {
        LOG_ERROR(GPIO, "PinErr");
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
            LOG_DEBUG(GPIO, "Single P%s%u", GpioPort2Str(Config->pad.port), Config->pad.pin);
#endif
            res = false;
            gpio_type* GPIOx = Port2PortPtr(Config->pad.port);
            if(GPIOx) {
                GpioInfo_t* Info = GpioGetPortInfo(Config->pad.port);
                if(Info) {
                    crm_periph_clock_enable(Info->clock_type, TRUE);
#ifdef HAS_GPIO_DIAG
                    LOG_INFO(GPIO, "%s,ClkOn", GpioPort2Str(Config->pad.port));
#endif
                }
                /*Configure GPIO pin Output Level */
                uint32_t pin_mask = PinNum2PinMask(Config->pad.pin);

                /*Configure GPIO pin : PtPin */
                res = gpio_is_valid_mode(Config->mode);
#ifdef HAS_DEBUGGER
                ASSERT_CRITICAL(true == res);
#endif
                if(res) {
                    gpio_init_type GpioInitStruct = {0};
                    gpio_default_para_init(&GpioInitStruct);

                    GpioInitStruct.gpio_pins = pin_mask;
                    GpioInitStruct.gpio_mode = GpioModeToAt32Mode(Config->mode);
                    GpioInitStruct.gpio_pull = GpioPullToAt32Pull(Config->pull);
                    GpioInitStruct.gpio_out_type = GpioModeToAt32OutType(Config->dir);
                    GpioInitStruct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
                    gpio_init(GPIOx, &GpioInitStruct);

                    switch((uint32_t)Config->mode) {
                    case GPIO_API_MODE_ALT1:
                    case GPIO_API_MODE_ALT2: {
#ifdef HAS_AT32F43X
                        gpio_pin_mux_config(GPIOx, ((gpio_pins_source_type)Config->pad.pin),
                                            (gpio_mux_sel_type)Config->mux);
#endif

                    } break;

                    case GPIO_API_MODE_INPUT_EXINT: {
#if 0
                            res = false;
                            exint_init_type ExIntInitStruct={0};
                            scfg_exint_line_config(Info->port_source,(scfg_pins_source_type) Config->pad.pin);

                            exint_default_para_init(&ExIntInitStruct);
                            ExIntInitStruct.line_enable = TRUE;
                            ExIntInitStruct.line_mode = EXINT_LINE_INTERRUPUT;
                            uint32_t line_select = num_exint_line(Config->pad.pin);
                            ExIntInitStruct.line_select = line_select;
                            exint_polarity_config_type line_polarity = GpioExpIntPotarityToArtery(Config->int_edge);
                            ExIntInitStruct.line_polarity = line_polarity;
                            exint_init(&ExIntInitStruct);

                            nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);

                            const ExtIntInfo_t* ExtIntNode=ExtIntGetInfo(Config->pad.pin);
                            if(ExtIntNode){
                                nvic_irq_enable(ExtIntNode->irq_n, 2, 2);
                                res = true;
                            }
#endif

                    } break;
                    default:
                        break;
                    }

                    res = gpio_logic_level_set(Config->pad.byte, Config->logic_level);
                    // res = true;

                } else {
#ifdef HAS_GPIO_DIAG
                    LOG_ERROR(GPIO, "ModeErr P%s%u", GpioPort2Str(Config->pad.port), Config->pad.pin);
#endif
                    res = false;
                }
            }
        } else {
#ifdef HAS_GPIO_DIAG
            LOG_ERROR(GPIO, "ReDefine P%s%u", GpioPort2Str(Config->pad.port), Config->pad.pin);
#endif
        }
    }
    return res;
}

static gpio_mode_type GpioDirToAt32Mode(GpioDir_t dir) {
    gpio_mode_type mode_type = GPIO_MODE_INPUT;
    switch((uint8_t)dir) {
    case GPIO_DIR_OUT:
        mode_type = GPIO_MODE_OUTPUT;
        break;
    case GPIO_DIR_OUT_PUSH_PULL:
        mode_type = GPIO_MODE_OUTPUT;
        break;
    case GPIO_DIR_OUT_OPEN_DRAIN:
        mode_type = GPIO_MODE_OUTPUT;
        break;
    case GPIO_DIR_INOUT:
        mode_type = GPIO_MODE_INPUT;
        break;
    case GPIO_DIR_NONE:
        mode_type = GPIO_MODE_INPUT;
        break;
    case GPIO_DIR_INOUT_OPEN_DRAIN:
        mode_type = GPIO_MODE_INPUT;
        break;
    case GPIO_DIR_IN:
        mode_type = GPIO_MODE_INPUT;
        break;
    }
    return mode_type;
}

bool gpio_dir_set(uint8_t pad_num, GpioDir_t dir) {
    bool res = false;
    Pad_t Pad = {.byte = pad_num};
    gpio_type* GPIOx = Port2PortPtr(Pad.port);
    if(GPIOx) {
        gpio_init_type GpioInitStruct = {0};
        gpio_default_para_init(&GpioInitStruct);
        uint32_t pin_mask = PinNum2PinMask(Pad.pin);
        GpioInitStruct.gpio_pins = pin_mask;
        GpioInitStruct.gpio_mode = GpioDirToAt32Mode(dir);
        gpio_init(GPIOx, &GpioInitStruct);
        res = true;
    }

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
