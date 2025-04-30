#include "gpio_mcal.h"


#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "bit_utils.h"
#include "board_config.h"
#include "data_utils.h"
#ifdef HAS_DEBUGGER
#include "debugger.h" //For assert
#endif
#include "gpio_config.h"
#include "gpio_const.h"
#include "gpio_custom_drv.h"
#include "gpio_isr.h"


#include "gpio_custom_types.h"
#ifdef HAS_LOG
#include "log.h"
#endif
#include "at32f435_437.h"


#define GPIO_INFO_COMPOSE(CODE) \
    {.valid=true, .port=PORT_##CODE, .clock_type=CRM_GPIO##CODE##_PERIPH_CLOCK, .GPIOx=GPIO##CODE,}


static const GpioInfo_t GpioInfo[]={
		GPIO_INFO_COMPOSE(A),
		GPIO_INFO_COMPOSE(B),
		GPIO_INFO_COMPOSE(C),
		GPIO_INFO_COMPOSE(D),
		GPIO_INFO_COMPOSE(E),
		GPIO_INFO_COMPOSE(F),
		GPIO_INFO_COMPOSE(G),
		GPIO_INFO_COMPOSE(H)
     //   {.valid=true, .port=PORT_A, .clock_type=CRM_GPIOA_PERIPH_CLOCK, .GPIOx=GPIOA,},
     //   {.valid=true, .port=PORT_B, .clock_type=CRM_GPIOB_PERIPH_CLOCK, .GPIOx=GPIOB,},
     //   {.valid=true, .port=PORT_C, .clock_type=CRM_GPIOC_PERIPH_CLOCK, .GPIOx=GPIOC,},
     //   {.valid=true, .port=PORT_D, .clock_type=CRM_GPIOD_PERIPH_CLOCK, .GPIOx=GPIOD,},
     //   {.valid=true, .port=PORT_E, .clock_type=CRM_GPIOE_PERIPH_CLOCK, .GPIOx=GPIOE,},
     //   {.valid=true, .port=PORT_F, .clock_type=CRM_GPIOF_PERIPH_CLOCK, .GPIOx=GPIOF,},
     //   {.valid=true, .port=PORT_G, .clock_type=CRM_GPIOG_PERIPH_CLOCK, .GPIOx=GPIOG,},
     //   {.valid=true, .port=PORT_H, .clock_type=CRM_GPIOH_PERIPH_CLOCK, .GPIOx=GPIOH,},
};


GpioInfo_t* GpioGetInfo(Port_t port) {
    GpioInfo_t* Node = NULL;
    uint8_t i = 0;
    for(i = 0; i < ARRAY_SIZE(GpioInfo); i++) {
        if(GpioInfo[i].valid){
            if(port == GpioInfo[i].port) {
                Node = &GpioInfo[i];
                break;
            }
        }
    }
    return Node;
}

static GpioPullMode_t GpioAt32Pull2GeneralPull(gpio_pull_type at32_pull_code) {
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

crm_periph_clock_type PortToClockType(Port_t port){
    crm_periph_clock_type clock_type=0;

    GpioInfo_t* Info= GpioGetInfo(  port);
    if(Info){
        clock_type=Info->clock_type;
    }

    return clock_type;
}

static GpioLogicLevel_t GpioAt32LlToGpioLl(flag_status status){
    GpioLogicLevel_t logic_level=GPIO_LVL_UNDEF;
    switch((uint8_t) status) {
        case RESET: logic_level=GPIO_LVL_LOW; break;
        case SET: logic_level=GPIO_LVL_HI; break;
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
    GpioInfo_t* Info=GpioGetInfo(    port);
    if(Info){
        GPIOx = Info->GPIOx;
    }
    return GPIOx;
}


bool gpio_get_state(uint8_t pad_num, GpioLogicLevel_t* logic_level) {
    Pad_t pad={0};
    (void) pad;
    bool res = false;
    pad.byte = pad_num;
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "Get P%s%u", GpioPort2Str(pad.port), pad.pin);
#endif
    gpio_type* PORTx = Port2PortPtr(pad.port);
    if(PORTx) {
        if(logic_level) {
            flag_status status = gpio_input_data_bit_read(PORTx, ((uint16_t) 1) << pad.pin);
            (*logic_level) = GpioAt32LlToGpioLl(status);
            res = true;
        }
    }
    return res;
}

uint32_t gpio_read(uint8_t pad_num) {
    uint32_t ret = 0;
    Pad_t pad={0};
    (void) pad;
    pad.byte = pad_num;
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "Get P%s%u", GpioPort2Str(pad.port), pad.pin);
#endif
   // GPIO_PinState value = HAL_GPIO_ReadPin(Port2PortPtr(pad.port), 1 << pad.pin);
    ret = (uint32_t)0;
    return ret;
}

bool gpio_set_logic_level(uint8_t pad_num, GpioLogicLevel_t logic_level) {
    Pad_t pad={0};
    (void) pad;
    pad.byte = pad_num;
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "Set P%s%u LL:%u", GpioPort2Str(pad.port), pad.pin, logic_level);
#endif
    gpio_type* GPIOx = Port2PortPtr(pad.port);
    if(GPIOx){
        switch((uint8_t)logic_level){
            case GPIO_LVL_HI:{ GPIOx->scr = 1 << pad.pin; } break;
            case GPIO_LVL_LOW:{ GPIOx->clr = 1 << pad.pin; } break;
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

PinIntEdge_t pin_get_edge(uint8_t pin) {
    PinIntEdge_t edge = PIN_INT_EDGE_UNDEF;

    return edge;
}

OutType_t gpio_get_out_type(uint8_t pad_num) {
    OutType_t out_type = OUT_TYPE_UNDEF;
    return out_type;
}

GpioDir_t gpio_get_dir(uint8_t pad_num) {
    GpioDir_t dirr = GPIO_DIR_UNDEF;
    GpioAt32Mode_t mode = gpio_get_mode(pad_num);
    switch((uint8_t)mode) {
    case GP_AT32_MODE_ALT_FUN:
        dirr = GPIO_DIR_UNDEF;
        break;
    case GP_AT32_MODE_ANALOG:
        dirr = GPIO_DIR_IN;
        break;
    case GP_AT32_MODE_INPUT:
        dirr = GPIO_DIR_IN;
        break;
    case GP_AT32_MODE_GNRL_PURPOSE_OUT:
        dirr = GPIO_DIR_OUT;
        break;
    }
    return dirr;
}

GpioAt32Mode_t gpio_get_mode(uint8_t pad_num) {
    GpioAt32Mode_t pin_mode = GP_AT32_MODE_UNDEF;
    Pad_t pad;
    pad.byte = pad_num;
    gpio_type* GPIOx = Port2PortPtr(pad.port);
    if(GPIOx) {

    }
    return pin_mode;
}

GpioAt32Speed_t gpio_get_speed(uint8_t pad_num) {
    GpioAt32Speed_t mode = SPEED_UNDEF;
    Pad_t pad;
    pad.byte = pad_num;
    gpio_type* GPIOx = Port2PortPtr(pad.port);
    if(GPIOx) {

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
        at32_pull_code = GPIO_PULL_NONE ;
        break;
    case GPIO__PULL_UNDEF:
        at32_pull_code = GPIO_PULL_NONE;
        break;
    }
    return at32_pull_code;
}

GpioPullMode_t gpio_get_pull(uint8_t pad_num) {
    GpioPullMode_t mode = GPIO__PULL_UNDEF;
    Pad_t pad;
    pad.byte = pad_num;
    gpio_type* GPIOx = Port2PortPtr(pad.port);
    if(GPIOx) {
        uint32_t code = 0;
        LOG_DEBUG(GPIO, "AT32PullCode 0x%x", code);
        mode = GpioAt32Pull2GeneralPull((gpio_pull_type)code);
        LOG_DEBUG(GPIO, "mode 0x%x", mode);
    } else {
#ifdef HAS_GPIO_DIAG
        LOG_ERROR(GPIO, "PortErr P%s", GpioPort2Str(pad.port));
#endif
    }
    return mode;
}


bool generate_sw_int(uint32_t mask) {
    bool res = true;
   // __HAL_GPIO_EXTI_GENERATE_SWIT(mask);
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

bool gpio_set_pull(uint8_t pad_num, GpioPullMode_t pull_mode) {
    bool res = false;
    Pad_t pad;
    pad.byte = pad_num;
#ifdef HAS_GPIO_DIAG
    LOG_DEBUG(GPIO, "Set Pad %u=%s, Pull %s", pad_num, GpioPad2Str(pad.byte), GpioPull2Str(pull_mode));
#endif
    //gpio_pull_type at32_pull_mode = GpioPullToAt32Pull(pull_mode);
    volatile gpio_type* GPIOx = Port2PortPtr(pad.port);
    if(GPIOx) {

#warning TODO

        res = true;
    }
    return res;
}


uint8_t LogicLevel2PinState(GpioLogicLevel_t logic_level) {
    uint8_t pin_state = 0;
    switch((uint8_t)logic_level) {
        case GPIO_LVL_LOW: pin_state = 0; break;
        case GPIO_LVL_HI: pin_state = 1; break;
    default:
        break;
    }
    return pin_state;
}

static gpio_output_type GpioModeToAt32OutType(GpioApiMode_t mode) {
    gpio_output_type output_type = GPIO_MODE_INPUT;
    switch((uint8_t)mode){
        case GPIO_API_MODE_GPIO:output_type = GPIO_OUTPUT_PUSH_PULL; break;
        case GPIO_API_MODE_ALT1:output_type = GPIO_OUTPUT_PUSH_PULL; break;
        case GPIO_API_MODE_ALT2:output_type = GPIO_OUTPUT_PUSH_PULL; break;
        case GPIO_API_MODE_HW_PWM:output_type = GPIO_OUTPUT_PUSH_PULL; break;
        case GPIO_API_MODE_OUTPUT:output_type = GPIO_OUTPUT_PUSH_PULL; break;
        case GPIO_API_MODE_INPUT:output_type = GPIO_OUTPUT_PUSH_PULL; break;
        case GPIO_API_MODE_I2C: output_type = GPIO_OUTPUT_OPEN_DRAIN;break;
        case GPIO_API_MODE_ANALOG: output_type = GPIO_OUTPUT_PUSH_PULL;break;
    }
    return output_type;
}


static gpio_mode_type GpioModeToAt32Mode(GpioApiMode_t mode) {
    gpio_mode_type gpio_mode = GPIO_MODE_INPUT;
    switch((uint8_t)mode){
        case GPIO_API_MODE_GPIO:gpio_mode = GPIO_MODE_OUTPUT; break;
        case GPIO_API_MODE_ALT1:gpio_mode = GPIO_MODE_MUX; break;
        case GPIO_API_MODE_ALT2:gpio_mode = GPIO_MODE_MUX; break;
        case GPIO_API_MODE_HW_PWM:gpio_mode = GPIO_MODE_MUX; break;
        case GPIO_API_MODE_OUTPUT:gpio_mode = GPIO_MODE_OUTPUT; break;
        case GPIO_API_MODE_INPUT:gpio_mode = GPIO_MODE_INPUT; break;
        case GPIO_API_MODE_ANALOG: gpio_mode = GPIO_MODE_INPUT;break;
    }
    return gpio_mode;
}

bool gpio_init_custom(void){
	bool res = false;
	return res;
}


bool gpio_init_one(const GpioConfig_t* const Config) {
    bool res = false;
    if(Config) {
#ifdef HAS_GPIO_DIAG
        gpio_diag_conf(Config);
#endif
        res = gpio_is_pin_single(Config->pad.byte);
        if(res) {
            res = false;
            gpio_type* GPIOx = Port2PortPtr(Config->pad.port);
            if(GPIOx) {
                GpioInfo_t* Info=GpioGetInfo(Config->pad.port);
                if(Info){
                    crm_periph_clock_enable(Info->clock_type, TRUE);
                    LOG_INFO(GPIO, "%u ClkOn", Config->pad.port);
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
                    GpioInitStruct.gpio_pull = GpioPullToAt32Pull(Config->gpio_pull);
                    GpioInitStruct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
                    GpioInitStruct.gpio_out_type = GpioModeToAt32OutType(Config->mode);;
                    gpio_init(GPIOx, &GpioInitStruct);

                    if((GPIO_API_MODE_ALT1==Config->mode) ||
                        (GPIO_API_MODE_ALT2==Config->mode) ) {
                        gpio_pin_mux_config(GPIOx,
                                ((gpio_pins_source_type) Config->pad.pin)  ,
                                (gpio_mux_sel_type)Config->mux   );
                    }

                    res= gpio_set_logic_level(Config->pad.byte, Config->logic_level);
                    //res = true;
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

gpio_mode_type GpioDirToAt32Mode(GpioDir_t dir){
    gpio_mode_type mode_type;
    switch((uint8_t)dir){
        case GPIO_DIR_OUT: mode_type=GPIO_MODE_OUTPUT; break;
        case GPIO_DIR_OUT_PUSH_PULL: mode_type=GPIO_MODE_OUTPUT; break;
        case GPIO_DIR_OUT_OPEN_DRAIN: mode_type=GPIO_MODE_OUTPUT; break;
        case GPIO_DIR_INOUT: mode_type=GPIO_MODE_INPUT; break;
        case GPIO_DIR_NONE:  mode_type=GPIO_MODE_INPUT; break;
        case GPIO_DIR_INOUT_OD: mode_type=GPIO_MODE_INPUT; break;
        case GPIO_DIR_IN: mode_type=GPIO_MODE_INPUT;  break;
    }
    return mode_type;
}

bool gpio_set_dir(uint8_t pad_num, GpioDir_t dir) {
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

