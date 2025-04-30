#include "gpio_mcal.h"


#include "microcontroller.h"
#include "gpio_custom_drv.h"
#include "hal_mcal.h"
#include "mik32_hal_gpio.h"
#ifdef HAS_DEBUGGER
#include "debugger.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

GPIO_PinState GpioLevelToMik32Level(GpioLogicLevel_t level) {
    GPIO_PinState pin_state = GPIO_PIN_LOW;
    switch(level) {
    case GPIO_LVL_LOW:
        pin_state = GPIO_PIN_LOW;
        break;
    case GPIO_LVL_HI:
        pin_state = GPIO_PIN_HIGH;
        break;
    default:
        break;
    }
    return pin_state;
}

#ifdef HAS_GPIO_EXT
GpioApiMode_t GpioMik32ModeToMode(HAL_GPIO_ModeTypeDef mik_mode) {
    GpioApiMode_t mode = GPIO_API_MODE_INPUT;
    switch(mik_mode) {
    case HAL_GPIO_MODE_GPIO_INPUT:
        mode = GPIO_API_MODE_INPUT;
        break;
    case HAL_GPIO_MODE_GPIO_OUTPUT:
        mode = GPIO_API_MODE_OUTPUT;
        break;
    case HAL_GPIO_MODE_SERIAL:
        mode = GPIO_API_MODE_ALT1;
        break;
    case HAL_GPIO_MODE_TIMER_SERIAL:
        mode = GPIO_API_MODE_ALT2;
        break;
    case HAL_GPIO_MODE_ANALOG:
        mode = GPIO_API_MODE_ANALOG;
        break;
    default:
        break;
    }
    return mode;
}
#endif

#ifdef HAS_GPIO_EXT
GpioPullMode_t GpioMik32Pull2GeneralPull(HAL_GPIO_PullTypeDef mik32_pull) {
    GpioPullMode_t general_pull_code = GPIO__PULL_UNDEF;
    switch((uint32_t)mik32_pull) {
    case HAL_GPIO_PULL_NONE:
        general_pull_code = GPIO__PULL_AIR;
        break;
    case HAL_GPIO_PULL_UP:
        general_pull_code = GPIO__PULL_UP;
        break;
    case HAL_GPIO_PULL_DOWN:
        general_pull_code = GPIO__PULL_DOWN;
        break;
    default:
#ifdef HAS_LOG
        LOG_ERROR(GPIO, "UndefMIKPullMode %u", mik32_pull);
#endif
        break;
    }
    return general_pull_code;
}
#endif

#ifdef HAS_GPIO_EXT
GpioLogicLevel_t GpioMik32LevelToLevel(GPIO_PinState pin_state) {
    GpioLogicLevel_t level = GPIO_LVL_UNDEF;
    switch((uint32_t)pin_state) {
    case GPIO_PIN_LOW:
        level = GPIO_LVL_LOW;
        break;
    case GPIO_PIN_HIGH:
        level = GPIO_LVL_HI;
        break;
    default:
        break;
    }
    return level;
}
#endif

#ifdef HAS_GPIO_EXT

GpioDir_t GpioMik32DirToDir(HAL_GPIO_ModeTypeDef mode) {
    GpioDir_t direction = GPIO_DIR_UNDEF;
    switch((uint8_t)mode) {
    case HAL_GPIO_MODE_TIMER_SERIAL:
    case HAL_GPIO_MODE_SERIAL:
        direction = GPIO_DIR_UNDEF;
        break;
    case HAL_GPIO_MODE_ANALOG:
        direction = GPIO_DIR_IN;
        break;
    case HAL_GPIO_MODE_GPIO_INPUT:
        direction = GPIO_DIR_IN;
        break;
    case HAL_GPIO_MODE_GPIO_OUTPUT:
        direction = GPIO_DIR_OUT;
        break;
    }
    return direction;
}
#endif

HAL_GPIO_ModeTypeDef GpioModeToMik32Mode(GpioApiMode_t mode) {
    HAL_GPIO_ModeTypeDef mik_mode = HAL_GPIO_MODE_GPIO_INPUT;
    switch(mode) {
    case GPIO_API_MODE_INPUT:
        mik_mode = HAL_GPIO_MODE_GPIO_INPUT;
        break;
    case GPIO_API_MODE_OUTPUT:
        mik_mode = HAL_GPIO_MODE_GPIO_OUTPUT;
        break;
    case GPIO_API_MODE_ALT1:
        mik_mode = HAL_GPIO_MODE_SERIAL;
        break;
    case GPIO_API_MODE_GPIO:
        mik_mode = HAL_GPIO_MODE_GPIO_INPUT;
        break;
    case GPIO_API_MODE_ALT2:
        mik_mode = HAL_GPIO_MODE_TIMER_SERIAL;
        break;
    case GPIO_API_MODE_ANALOG:
        mik_mode = HAL_GPIO_MODE_ANALOG;
        break;
    case GPIO_API_MODE_I2C:
        mik_mode = HAL_GPIO_MODE_GPIO_INPUT;
        break;
    case GPIO_API_MODE_INPUT_EXINT:
        mik_mode = HAL_GPIO_MODE_GPIO_INPUT;
        break;
    case GPIO_API_MODE_INPUT_EXINT_FAILLING:
        mik_mode = HAL_GPIO_MODE_GPIO_INPUT;
        break;
    case GPIO_API_MODE_INPUT_EXINT_RISING:
        mik_mode = HAL_GPIO_MODE_GPIO_INPUT;
        break;
    default:
        mik_mode = HAL_GPIO_MODE_GPIO_INPUT;
        break;
    }
    return mik_mode;
}

#define GPIO_INFO_COMPOSE(CODE)                                                                                        \
    { .valid = true, .port = PORT_##CODE, .GPIOx = GPIO_##CODE, }

static const GpioInfo_t GpioInfo[] = {
    GPIO_INFO_COMPOSE(0), GPIO_INFO_COMPOSE(1), GPIO_INFO_COMPOSE(2),
    //   {.valid=true, .port=PORT_2, .clock_type=CRM_GPIOA_PERIPH_CLOCK, .GPIOx=GPIO_2,},
};

const GpioInfo_t* GpioGetInfo(Port_t port) {
    GpioInfo_t* Node = 0;
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

#ifdef HAS_GPIO_EXT
static PinInt_t PinInt[] = {
    {.gpio_pin = 0, .int_cnt = 0},  {.gpio_pin = 1, .int_cnt = 0},  {.gpio_pin = 2, .int_cnt = 0},
    {.gpio_pin = 3, .int_cnt = 0},  {.gpio_pin = 4, .int_cnt = 0},  {.gpio_pin = 5, .int_cnt = 0},
    {.gpio_pin = 6, .int_cnt = 0},  {.gpio_pin = 7, .int_cnt = 0},  {.gpio_pin = 8, .int_cnt = 0},
    {.gpio_pin = 9, .int_cnt = 0},  {.gpio_pin = 10, .int_cnt = 0}, {.gpio_pin = 11, .int_cnt = 0},
    {.gpio_pin = 12, .int_cnt = 0}, {.gpio_pin = 13, .int_cnt = 0}, {.gpio_pin = 14, .int_cnt = 0},
    {.gpio_pin = 15, .int_cnt = 0},
};

PinInt_t* PinIntGetNode(uint16_t gpio_pin) {
    PinInt_t* Node = 0;
    uint8_t i = 0;
    for(i = 0; i < ARRAY_SIZE(PinInt); i++) {
        if(gpio_pin == PinInt[i].gpio_pin) {
            Node = &PinInt[i];
            break;
        }
    }
    return Node;
}
#endif

#if 0
static bool is_valid_mik_mode(uint32_t mik_mode) {
    bool res = false;
    switch(mik_mode) {
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

#ifdef HAS_PINS
bool gpio_clock_init(void) {
    bool res = false;
#ifdef HAS_LOG
    LOG_WARNING(GPIO, "ClockInit");
#endif
    return res;
}
#endif /*HAS_PINS*/

#ifdef HAS_GPIO_EXT
uint32_t PinNum2PinMask(uint8_t pin_num) {
    uint32_t pin_mask = 0;
    pin_mask |= (1 << pin_num);
    return pin_mask;
}
#endif

HAL_GPIO_PullTypeDef GpioPullToMik32Pull(GpioPullMode_t pull_code) {
    HAL_GPIO_PullTypeDef mik32_pull = HAL_GPIO_PULL_NONE;
    switch((uint8_t)pull_code) {
    case GPIO__PULL_AIR:
        mik32_pull = HAL_GPIO_PULL_NONE;
        break;
    case GPIO__PULL_UP:
        mik32_pull = HAL_GPIO_PULL_UP;
        break;
    case GPIO__PULL_DOWN:
        mik32_pull = HAL_GPIO_PULL_DOWN;
        break;
    case GPIO__PULL_UNDEF:
        mik32_pull = HAL_GPIO_PULL_NONE;
        break;
    }
    return mik32_pull;
}

HAL_GPIO_DSTypeDef GpioDriveSelToMik32DriveSel(GpioDriveSelect_t drive_select) {
    HAL_GPIO_DSTypeDef mik32_ds = HAL_GPIO_DS_8MA;
    switch((uint8_t)drive_select) {
    case GPIO_DRIVE_SELECT_2MA:
        mik32_ds = HAL_GPIO_DS_2MA;
        break;
    case GPIO_DRIVE_SELECT_4MA:
        mik32_ds = HAL_GPIO_DS_4MA;
        break;
    case GPIO_DRIVE_SELECT_8MA:
        mik32_ds = HAL_GPIO_DS_8MA;
        break;
    }
    return mik32_ds;
}

#ifdef HAS_GPIO_EXT
GpioDir_t gpio_dir_get(uint8_t pad_num) {
    GpioDir_t dir = GPIO_DIR_UNDEF;
    return dir;
}
#endif

#ifdef HAS_GPIO_EXT
GpioSpeed_t GpioMik32SpeedToSpeed(GpioMik32Speed_t mik_speed) {
    GpioSpeed_t speed = GPIO_SPEED_UNDEF;
    switch(mik_speed) {
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
#endif

#ifdef HAS_GPIO_EXT
bool gpio_get_state(uint8_t pad_num, GpioLogicLevel_t* logic_level) {
    bool res = false;
    Pad_t Pad = {.byte = pad_num};
    const GpioInfo_t* Info = GpioGetInfo(Pad.port);
    if(Info) {
        GPIO_PinState PinState = GPIO_PIN_LOW;
        uint16_t pin_mask = (1 << Pad.pin);
        PinState = HAL_GPIO_ReadPin(Info->GPIOx, (HAL_PinsTypeDef)pin_mask);
        *logic_level = GpioMik32LevelToLevel(PinState);
        res = true;
    }
    return res;
}
#endif

#ifdef HAS_GPIO_EXT
uint32_t gpio_read(uint8_t pad_num) {
    uint32_t ret = 0;

    return ret;
}
#endif

bool gpio_logic_level_set(Pad_t Pad, GpioLogicLevel_t logic_level) {
    bool res = false;
    uint16_t pin_mask = (1 << Pad.pin);
    const GpioInfo_t* Info = GpioGetInfo(Pad.port);
    if(Info) {
        GPIO_PinState pinState = GPIO_PIN_LOW;
        pinState = GpioLevelToMik32Level(logic_level);
        HAL_GPIO_WritePin(Info->GPIOx, (HAL_PinsTypeDef)pin_mask, pinState);
        res = true;
    }
    return res;
}


#ifdef HAS_GPIO_EXT
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
#endif

#ifdef HAS_EXT_INT
PinIntEdge_t pin_get_edge(uint8_t pin) {
    PinIntEdge_t edge;
    return edge;
}
#endif

#ifdef HAS_GPIO_EXT
OutType_t gpio_get_out_type(uint8_t pad_num) {
    OutType_t out_type = OUT_TYPE_UNDEF;

    return out_type;
}
#endif

#ifdef HAS_GPIO_EXT
GpioApiMode_t gpio_mode_get(uint8_t pad_num) {
    GpioApiMode_t mode = GPIO_API_MODE_UNDEF;

    return mode;
}
#endif

#ifdef HAS_GPIO_EXT
static GpioMik32Speed_t gpio_mik_speed_get(uint8_t pad_num) {
    GpioMik32Speed_t mode = SPEED_UNDEF;
    return mode;
}
#endif

#ifdef HAS_GPIO_EXT
GpioSpeed_t gpio_speed_get(uint8_t pad_num) {
    GpioSpeed_t speed = GPIO_SPEED_UNDEF;
    GpioMik32Speed_t mik_speed = gpio_mik_speed_get(pad_num);
    speed = GpioMik32SpeedToSpeed(mik_speed);
    return speed;
}
#endif

#ifdef HAS_GPIO_EXT
GpioPullMode_t gpio_pull_get(uint8_t pad_num) {
    GpioPullMode_t mode = GPIO__PULL_UNDEF;
    return mode;
}
#endif

#ifdef HAS_GPIO_EXT
bool ext_int_set_mask(uint32_t mask) {
    bool res = true;
    return res;
}
#endif

#ifdef HAS_GPIO_EXT
bool ext_int_reset_mask(uint32_t mask) {
    bool res = true;

    return res;
}
#endif


#ifdef HAS_GPIO_EXT
bool gpio_is_valid_pad(uint8_t pad_num) {
    bool res = false;
    Pad_t Pad = {.byte = pad_num};
    if(Pad.pin <= GPIO_PIN_COUNT) {
        if(Pad.port <= PORT_2) {
            res = true;
        }
    }
    return res;
}
#endif

#ifdef HAS_GPIO_EXT
static bool gpio_port0_pin_mux_get(Mik32PinMux_t* PinMux, uint8_t pin, uint8_t* mux) {
    bool res = true;
    switch(pin) {
    case 0:
        *mux = PinMux->PAD0_CFG.pin_mux_0;
        break;
    case 1:
        *mux = PinMux->PAD0_CFG.pin_mux_1;
        break;
    case 2:
        *mux = PinMux->PAD0_CFG.pin_mux_2;
        break;
    case 3:
        *mux = PinMux->PAD0_CFG.pin_mux_3;
        break;
    case 4:
        *mux = PinMux->PAD0_CFG.pin_mux_4;
        break;
    case 5:
        *mux = PinMux->PAD0_CFG.pin_mux_5;
        break;
    case 6:
        *mux = PinMux->PAD0_CFG.pin_mux_6;
        break;
    case 7:
        *mux = PinMux->PAD0_CFG.pin_mux_7;
        break;
    case 8:
        *mux = PinMux->PAD0_CFG.pin_mux_8;
        break;
    case 9:
        *mux = PinMux->PAD0_CFG.pin_mux_9;
        break;
    case 10:
        *mux = PinMux->PAD0_CFG.pin_mux_10;
        break;
    case 11:
        *mux = PinMux->PAD0_CFG.pin_mux_11;
        break;
    case 12:
        *mux = PinMux->PAD0_CFG.pin_mux_12;
        break;
    case 13:
        *mux = PinMux->PAD0_CFG.pin_mux_13;
        break;
    case 14:
        *mux = PinMux->PAD0_CFG.pin_mux_14;
        break;
    case 15:
        *mux = PinMux->PAD0_CFG.pin_mux_15;
        break;
    default:
        break;
    }
    return res;
}
#endif


static bool gpio_port0_pin_mux_set(Mik32PinMux_t* PinMux, uint8_t pin, uint8_t mux) {
    bool res = false;
    uint32_t mask_mux = mux;
    PinMux->PAD0_CFG.dword &= ~(0x3<<pin);
    PinMux->PAD0_CFG.dword |= (mask_mux)<<pin;
#if 0
    switch(pin) {
    case 0:
        PinMux->PAD0_CFG.pin_mux_0 = mux;
        break;
    case 1:
        PinMux->PAD0_CFG.pin_mux_1 = mux;
        break;
    case 2:
        PinMux->PAD0_CFG.pin_mux_2 = mux;
        break;
    case 3:
        PinMux->PAD0_CFG.pin_mux_3 = mux;
        break;
    case 4:
        PinMux->PAD0_CFG.pin_mux_4 = mux;
        break;
    case 5:
        PinMux->PAD0_CFG.pin_mux_5 = mux;
        break;
    case 6:
        PinMux->PAD0_CFG.pin_mux_6 = mux;
        break;
    case 7:
        PinMux->PAD0_CFG.pin_mux_7 = mux;
        break;
    case 8:
        PinMux->PAD0_CFG.pin_mux_8 = mux;
        break;
    case 9:
        PinMux->PAD0_CFG.pin_mux_9 = mux;
        break;
    case 10:
        PinMux->PAD0_CFG.pin_mux_10 = mux;
        break;
    case 11:
        PinMux->PAD0_CFG.pin_mux_11 = mux;
        break;
    case 12:
        PinMux->PAD0_CFG.pin_mux_12 = mux;
        break;
    case 13:
        PinMux->PAD0_CFG.pin_mux_13 = mux;
        break;
    case 14:
        PinMux->PAD0_CFG.pin_mux_14 = mux;
        break;
    case 15:
        PinMux->PAD0_CFG.pin_mux_15 = mux;
        break;
    default:
        break;
    }
#endif
    return res;
}

static bool gpio_port1_pin_mux_set(Mik32PinMux_t* PinMux, uint8_t pin, uint8_t mux) {
    bool res = false;
    uint32_t mask_mux = mux;
    PinMux->PAD1_CFG.dword &= ~(0x00000003<<pin);
    PinMux->PAD1_CFG.dword |= (mask_mux)<<pin;
#if 0
    switch(pin) {
    case 0:
        PinMux->PAD1_CFG.pin_mux_0 = mux;
        break;
    case 1:
        PinMux->PAD1_CFG.pin_mux_1 = mux;
        break;
    case 2:
        PinMux->PAD1_CFG.pin_mux_2 = mux;
        break;
    case 3:
        PinMux->PAD1_CFG.pin_mux_3 = mux;
        break;
    case 4:
        PinMux->PAD1_CFG.pin_mux_4 = mux;
        break;
    case 5:
        PinMux->PAD1_CFG.pin_mux_5 = mux;
        break;
    case 6:
        PinMux->PAD1_CFG.pin_mux_6 = mux;
        break;
    case 7:
        PinMux->PAD1_CFG.pin_mux_7 = mux;
        break;
    case 8:
        PinMux->PAD1_CFG.pin_mux_8 = mux;
        break;
    case 9:
        PinMux->PAD1_CFG.pin_mux_9 = mux;
        break;
    case 10:
        PinMux->PAD1_CFG.pin_mux_10 = mux;
        break;
    case 11:
        PinMux->PAD1_CFG.pin_mux_11 = mux;
        break;
    case 12:
        PinMux->PAD1_CFG.pin_mux_12 = mux;
        break;
    case 13:
        PinMux->PAD1_CFG.pin_mux_13 = mux;
        break;
    case 14:
        PinMux->PAD1_CFG.pin_mux_14 = mux;
        break;
    case 15:
        PinMux->PAD1_CFG.pin_mux_15 = mux;
        break;
    default:
        break;
    }
#endif
    return res;
}

static bool gpio_port2_pin_mux_set(Mik32PinMux_t* PinMux, uint8_t pin, uint8_t mux) {
    bool res = false;

    uint32_t mask_mux = mux;
    PinMux->PAD2_CFG.dword &= ~(0x00000003<<pin);
    PinMux->PAD2_CFG.dword |= (mask_mux)<<pin;
#if 0
    switch(pin) {
    case 0:
        PinMux->PAD2_CFG.pin_mux_0 = mux;
        break;
    case 1:
        PinMux->PAD2_CFG.pin_mux_1 = mux;
        break;
    case 2:
        PinMux->PAD2_CFG.pin_mux_2 = mux;
        break;
    case 3:
        PinMux->PAD2_CFG.pin_mux_3 = mux;
        break;
    case 4:
        PinMux->PAD2_CFG.pin_mux_4 = mux;
        break;
    case 5:
        PinMux->PAD2_CFG.pin_mux_5 = mux;
        break;
    case 6:
        PinMux->PAD2_CFG.pin_mux_6 = mux;
        break;
    case 7:
        PinMux->PAD2_CFG.pin_mux_7 = mux;
        break;
    case 8:
        PinMux->PAD2_CFG.pin_mux_8 = mux;
        break;
    case 9:
        PinMux->PAD2_CFG.pin_mux_9 = mux;
        break;
    case 10:
        PinMux->PAD2_CFG.pin_mux_10 = mux;
        break;
    case 11:
        PinMux->PAD2_CFG.pin_mux_11 = mux;
        break;
    case 12:
        PinMux->PAD2_CFG.pin_mux_12 = mux;
        break;
    case 13:
        PinMux->PAD2_CFG.pin_mux_13 = mux;
        break;
    case 14:
        PinMux->PAD2_CFG.pin_mux_14 = mux;
        break;
    case 15:
        PinMux->PAD2_CFG.pin_mux_15 = mux;
        break;
    default:
        break;
    }
#endif
    return res;
}

bool gpio_init_custom(void) {
    bool res = true;

    __HAL_PCC_GPIO_0_CLK_ENABLE();
    __HAL_PCC_GPIO_1_CLK_ENABLE();
    __HAL_PCC_GPIO_2_CLK_ENABLE();
    return res;
}

bool gpio_pin_mux_set(Port_t port, uint8_t pin, uint8_t mux) {
    bool res = false;
    Mik32PinMux_t* PinMux = PAD_CONFIG_BASE_ADDRESS;
    switch(port) {
    case PORT_0:
        res = gpio_port0_pin_mux_set(PinMux, pin, mux);
        break;
    case PORT_1:
        res = gpio_port1_pin_mux_set(PinMux, pin, mux);
        break;
    case PORT_2:
        res = gpio_port2_pin_mux_set(PinMux, pin, mux);
        break;
    default:
        break;
    }
    return res;
}

static bool gpio_port0_pin_pull_set(Mik32PinMux_t* PinMux, uint8_t pin, HAL_GPIO_PullTypeDef pull_code) {
    bool res = true;

    uint32_t mask_pull = pull_code;
    PinMux->PAD0_PUPD.dword &= ~(0x00000003<<pin);
    PinMux->PAD0_PUPD.dword |= mask_pull<<pin;

#if 0
    switch(pin) {
    case 0:
        PinMux->PAD0_PUPD.pin_0 = pull_code;
        break;
    case 1:
        PinMux->PAD0_PUPD.pin_1 = pull_code;
        break;
    case 2:
        PinMux->PAD0_PUPD.pin_2 = pull_code;
        break;
    case 3:
        PinMux->PAD0_PUPD.pin_3 = pull_code;
        break;
    case 4:
        PinMux->PAD0_PUPD.pin_4 = pull_code;
        break;
    case 5:
        PinMux->PAD0_PUPD.pin_5 = pull_code;
        break;
    case 6:
        PinMux->PAD0_PUPD.pin_6 = pull_code;
        break;
    case 7:
        PinMux->PAD0_PUPD.pin_7 = pull_code;
        break;
    case 8:
        PinMux->PAD0_PUPD.pin_8 = pull_code;
        break;
    case 9:
        PinMux->PAD0_PUPD.pin_9 = pull_code;
        break;
    case 10:
        PinMux->PAD0_PUPD.pin_10 = pull_code;
        break;
    case 11:
        PinMux->PAD0_PUPD.pin_11 = pull_code;
        break;
    case 12:
        PinMux->PAD0_PUPD.pin_12 = pull_code;
        break;
    case 13:
        PinMux->PAD0_PUPD.pin_13 = pull_code;
        break;
    case 14:
        PinMux->PAD0_PUPD.pin_14 = pull_code;
        break;
    case 15:
        PinMux->PAD0_PUPD.pin_15 = pull_code;
        break;
    default:
        break;
    }
#endif
    return res;
}

static bool gpio_port1_pin_pull_set(Mik32PinMux_t* PinMux, uint8_t pin, HAL_GPIO_PullTypeDef pull_code) {
    bool res = true;

    uint32_t mask_pull = pull_code;
    PinMux->PAD1_PUPD.dword &= ~(0x00000003<<pin);
    PinMux->PAD1_PUPD.dword |= mask_pull<<pin;
#if 0
    switch(pin) {
    case 0:
        PinMux->PAD1_PUPD.pin_0 = pull_code;
        break;
    case 1:
        PinMux->PAD1_PUPD.pin_1 = pull_code;
        break;
    case 2:
        PinMux->PAD1_PUPD.pin_2 = pull_code;
        break;
    case 3:
        PinMux->PAD1_PUPD.pin_3 = pull_code;
        break;
    case 4:
        PinMux->PAD1_PUPD.pin_4 = pull_code;
        break;
    case 5:
        PinMux->PAD1_PUPD.pin_5 = pull_code;
        break;
    case 6:
        PinMux->PAD1_PUPD.pin_6 = pull_code;
        break;
    case 7:
        PinMux->PAD1_PUPD.pin_7 = pull_code;
        break;
    case 8:
        PinMux->PAD1_PUPD.pin_8 = pull_code;
        break;
    case 9:
        PinMux->PAD1_PUPD.pin_9 = pull_code;
        break;
    case 10:
        PinMux->PAD1_PUPD.pin_10 = pull_code;
        break;
    case 11:
        PinMux->PAD1_PUPD.pin_11 = pull_code;
        break;
    case 12:
        PinMux->PAD1_PUPD.pin_12 = pull_code;
        break;
    case 13:
        PinMux->PAD1_PUPD.pin_13 = pull_code;
        break;
    case 14:
        PinMux->PAD1_PUPD.pin_14 = pull_code;
        break;
    case 15:
        PinMux->PAD1_PUPD.pin_15 = pull_code;
        break;
    default:
        break;
    }
#endif
    return res;
}

static bool gpio_port2_pin_pull_set(Mik32PinMux_t* PinMux, uint8_t pin, HAL_GPIO_PullTypeDef pull_code) {
    bool res = true;


    uint32_t mask_pull = pull_code;
    PinMux->PAD2_PUPD.dword &= ~(0x00000003<<pin);
    PinMux->PAD2_PUPD.dword |= mask_pull<<pin;
#if 0
    switch(pin) {
    case 0:
        PinMux->PAD2_PUPD.pin_0 = pull_code;
        break;
    case 1:
        PinMux->PAD2_PUPD.pin_1 = pull_code;
        break;
    case 2:
        PinMux->PAD2_PUPD.pin_2 = pull_code;
        break;
    case 3:
        PinMux->PAD2_PUPD.pin_3 = pull_code;
        break;
    case 4:
        PinMux->PAD2_PUPD.pin_4 = pull_code;
        break;
    case 5:
        PinMux->PAD2_PUPD.pin_5 = pull_code;
        break;
    case 6:
        PinMux->PAD2_PUPD.pin_6 = pull_code;
        break;
    case 7:
        PinMux->PAD2_PUPD.pin_7 = pull_code;
        break;
    case 8:
        PinMux->PAD2_PUPD.pin_8 = pull_code;
        break;
    case 9:
        PinMux->PAD2_PUPD.pin_9 = pull_code;
        break;
    case 10:
        PinMux->PAD2_PUPD.pin_10 = pull_code;
        break;
    case 11:
        PinMux->PAD2_PUPD.pin_11 = pull_code;
        break;
    case 12:
        PinMux->PAD2_PUPD.pin_12 = pull_code;
        break;
    case 13:
        PinMux->PAD2_PUPD.pin_13 = pull_code;
        break;
    case 14:
        PinMux->PAD2_PUPD.pin_14 = pull_code;
        break;
    case 15:
        PinMux->PAD2_PUPD.pin_15 = pull_code;
        break;
    default:
        break;
    }
#endif
    return res;
}

bool gpio_pull_set(Pad_t Pad, GpioPullMode_t pull_mode) {
    bool res = false;
    HAL_GPIO_PullTypeDef pull_code = GpioPullToMik32Pull(pull_mode);
    Mik32PinMux_t* PinMux = PAD_CONFIG_BASE_ADDRESS;
    switch(Pad.port) {
    case PORT_0:
        res = gpio_port0_pin_pull_set(PinMux, Pad.pin, pull_code);
        break;
    case PORT_1:
        res = gpio_port1_pin_pull_set(PinMux, Pad.pin, pull_code);
        break;
    case PORT_2:
        res = gpio_port2_pin_pull_set(PinMux, Pad.pin, pull_code);
        break;
    default:
        res = false;
        break;
    }
    return res;
}

#ifdef HAS_GPIO_EXT
bool gpio_pin_mux_get(uint8_t port, uint8_t pin, uint8_t* const mux) {
    bool res = false;
    Mik32PinMux_t* PinMux = PAD_CONFIG_BASE_ADDRESS;
    switch(port) {
    case PORT_0:
        res = gpio_port0_pin_mux_get(PinMux, pin, mux);
        break;
    // case PORT_1: res = gpio_port1_pin_mux_get(PinMux, pin, mux); break;
    // case PORT_2: res = gpio_port2_pin_mux_get(PinMux, pin, mux); break;
    default:
        break;
    }
    return res;
}
#endif

#ifdef HAS_GPIO_EXT
bool gpio_proc(void) {
    bool res = false;
    return res;
}
#endif

#ifdef HAS_GPIO_EXT
bool gpio_toggle(const Pad_t Pad) {
    bool res = false;
    GpioInfo_t* Info = GpioGetInfo(Pad.port);
    if(Info){
    	uint16_t mask= (1U<<Pad.pin);
        HAL_GPIO_TogglePin(Info->GPIOx, (HAL_PinsTypeDef) mask);
    	res = true;
    }
    return res;
}
#endif

bool gpio_init_one(const GpioConfig_t* const Config) {
    bool res = false;
    if(Config) {
#ifdef HAS_GPIO_DIAG
        // gpio_diag_conf(Config);
#endif

        res = true;
#ifdef HAS_GPIO_EXT
        res = gpio_is_valid_pad(Config->pad.byte);
#endif

#ifdef HAS_DEBUGGER
        ASSERT_CRITICAL(true == res);
#endif
        if(res) {
#ifdef HAS_GPIO_EXT
            res = gpio_is_pin_single(Config->pad.byte);
#endif
            if(res) {
                res = false;
                GpioInfo_t* Info = GpioGetInfo(Config->pad.port);
                if(Info) {
                    HAL_StatusTypeDef ret = HAL_ERROR;
                    GPIO_InitTypeDef GpioInit = {0};
                    GpioInit.Pin = (1 << Config->pad.pin);
                    GpioInit.Mode = GpioModeToMik32Mode(Config->mode);
                    GpioInit.Pull = GpioPullToMik32Pull(Config->pull);
                    GpioInit.DS = GpioDriveSelToMik32DriveSel(Config->drive_select);
                    ret = HAL_GPIO_Init(Info->GPIOx, &GpioInit);
                    res = MIK32_HalRetToRes(ret);

                    res = gpio_pin_mux_set(Config->pad.port, Config->pad.pin, Config->mux);
                    res = gpio_pull_set(Config->pad, Config->pull);
                    res = gpio_logic_level_set(Config->pad, Config->logic_level);
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
