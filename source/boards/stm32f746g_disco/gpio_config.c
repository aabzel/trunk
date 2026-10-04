#include "gpio_config.h"

#include "data_utils.h"
#include "gpio_types.h"
#include "stm32fx_hal.h"
#include "sys_config.h"
#include "gpio_custom_const.h"

#ifndef USE_HAL_DRIVER
#error "that wile only for STM32 MCUs"
#endif

/*
STLINK_RX   VCP_RX  PB7 B5  USART1_RX
STLINK_TX   VCP_TX  PA9 E15 USART1_TX
*/
#ifdef HAS_UART1
#define GPIO_CONFIG_UART1_NORNAL_PINS     \
    {.Pad={.port = PORT_B, .pin = 7,}, .name="UART1_RX",  .mux=GPIO_AF7_USART1, .mode = GPIO_API_MODE_ALT1, .pull = GPIO__PULL_UP, .speed = GPIO_SPEED_FREQ_VERY_HIGH,   .logic_level = GPIO_LVL_HI,}, \
    {.Pad={.port = PORT_A, .pin = 9,}, .name="UART1_TX",  .mux=GPIO_AF7_USART1, .mode = GPIO_API_MODE_ALT1, .pull = GPIO__PULL_UP, .speed = GPIO_SPEED_FREQ_VERY_HIGH,   .logic_level = GPIO_LVL_HI,},
#else
#define GPIO_CONFIG_UART1_NORNAL_PINS
#endif


#ifdef HAS_UART1_DEBUG
#define GPIO_CONFIG_UART1_PINS   GPIO_CONFIG_UART1_HOT_FIX_PINS
#else
#define GPIO_CONFIG_UART1_PINS GPIO_CONFIG_UART1_NORNAL_PINS
#endif


#define GPIO_CONFIG_OUT1_PINS \
    {.Pad = {.port = PORT_D, .pin = 5,},  .name = "OUT1_1",  .mux = 0, .mode = GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_DOWN, .speed=GPIO_SPEED_FREQ_HIGH,  .logic_level=GPIO_LVL_LOW,    }, \
    {.Pad = {.port = PORT_D, .pin = 3,},  .name = "OUT1_2",  .mux = 0, .mode = GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_DOWN, .speed=GPIO_SPEED_FREQ_HIGH,  .logic_level=GPIO_LVL_LOW,    }, \
    {.Pad = {.port = PORT_D, .pin = 2,},  .name = "OUT1_3",  .mux = 0, .mode = GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_DOWN, .speed=GPIO_SPEED_FREQ_HIGH,  .logic_level=GPIO_LVL_LOW,    }, \
    {.Pad = {.port = PORT_D, .pin = 0,},  .name = "OUT1_4",  .mux = 0, .mode = GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_DOWN, .speed=GPIO_SPEED_FREQ_HIGH,  .logic_level=GPIO_LVL_LOW,    },


#define GPIO_CONFIG_OUT2_PINS         \
    {.Pad = {.port = PORT_C, .pin = 7,},  .name = "OUT2_1",  .mux = 0, .mode = GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_DOWN, .speed=GPIO_SPEED_FREQ_HIGH,  .logic_level=GPIO_LVL_LOW,    }, \
    {.Pad = {.port = PORT_A, .pin = 8,},  .name = "OUT2_2",  .mux = 0, .mode = GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_DOWN, .speed=GPIO_SPEED_FREQ_HIGH,  .logic_level=GPIO_LVL_LOW,    }, \
    GPIO_CONFIG_OUT2_EXTRA_PINS


#define GPIO_CONFIG_OUT3_PINS     \
    {.Pad = {.port = PORT_C, .pin = 6,},  .name = "OUT3_1",  .mux = 0, .mode = GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_DOWN, .speed=GPIO_SPEED_FREQ_HIGH,  .logic_level=GPIO_LVL_LOW,    }, \
    {.Pad = {.port = PORT_D, .pin = 14,}, .name = "OUT3_2",  .mux = 0, .mode = GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_DOWN, .speed=GPIO_SPEED_FREQ_HIGH,  .logic_level=GPIO_LVL_LOW,    }, \
    {.Pad = {.port = PORT_D, .pin = 13,}, .name = "OUT3_3",  .mux = 2, .mode = GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_DOWN, .speed=GPIO_SPEED_FREQ_HIGH,  .logic_level=GPIO_LVL_LOW,    }, \
    {.Pad = {.port = PORT_D, .pin = 11,}, .name = "OUT3_4",  .mux = 0, .mode = GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_DOWN, .speed=GPIO_SPEED_FREQ_HIGH,  .logic_level=GPIO_LVL_LOW,    },

#define GPIO_CONFIG_OUT4_PINS     \
    {.Pad = {.port = PORT_D, .pin = 10,},  .name = "OUT4_1",  .mux = 0, .mode = GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_DOWN, .speed=GPIO_SPEED_FREQ_HIGH,  .logic_level=GPIO_LVL_LOW,    }, \
    {.Pad = {.port = PORT_D, .pin = 8,},   .name = "OUT4_2",  .mux = 0, .mode = GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_DOWN, .speed=GPIO_SPEED_FREQ_HIGH,  .logic_level=GPIO_LVL_LOW,    }, \
    {.Pad = {.port = PORT_B, .pin = 15,},  .name = "OUT4_3",  .mux = 0, .mode = GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_DOWN, .speed=GPIO_SPEED_FREQ_HIGH,  .logic_level=GPIO_LVL_LOW,    }, \
    {.Pad = {.port = PORT_D, .pin = 7,},   .name = "OUT4_4",  .mux = 0, .mode = GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_DOWN, .speed=GPIO_SPEED_FREQ_HIGH,  .logic_level=GPIO_LVL_LOW,    },


#define GPIO_CONFIG_DISCRET_INPUPT_PINS     \
    {.Pad={.port=PORT_E, .pin=7,},   .name="DI_1",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_E, .pin=8,},   .name="DI_2",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_E, .pin=9 ,},  .name="DI_3",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_E, .pin=10,},  .name="DI_4",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_E, .pin=11,},  .name="DI_5",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_E, .pin=12,},  .name="DI_6",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_E, .pin=13,},  .name="DI_7",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_E, .pin=14,},  .name="DI_8",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  },


#define GPIO_CONFIG_ANALOG_INPUPT_PINS     \
    {.Pad={.port=PORT_A, .pin=0,},  .name="AI_1",     .mode = GPIO_API_MODE_ANALOG, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_A, .pin=1,},  .name="AI_2",     .mode = GPIO_API_MODE_ANALOG, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_A, .pin=2,},  .name="AI_3",     .mode = GPIO_API_MODE_ANALOG, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_A, .pin=3,},  .name="AI_4",     .mode = GPIO_API_MODE_ANALOG, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_A, .pin=4,},  .name="AI_VS_5V", .mode = GPIO_API_MODE_ANALOG, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  },


#define GPIO_CONFIG_GPIO_MAP_PINS          \
    {.Pad={.port=PORT_B, .pin=0,},   .name="PB0",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_B, .pin=1,},   .name="PB1",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_B, .pin=2,},   .name="PB2",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_B, .pin=3,},   .name="PB3",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_B, .pin=4,},   .name="PB4",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_B, .pin=5,},   .name="PB5",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_B, .pin=8,},   .name="PB8",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_B, .pin=14,},  .name="PB14",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_B, .pin=9,},   .name="PB9",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  },


#define GPIO_CONFIG_GPIO_MAP_ERR_PINS          \
    {.Pad={.port=PORT_C, .pin=0,},   .name="PC0",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_C, .pin=1,},   .name="PC1",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_C, .pin=2,},   .name="PC2",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_C, .pin=3,},   .name="PC3",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_C, .pin=4,},   .name="PC4",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_C, .pin=5,},   .name="PC5",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_C, .pin=13,},   .name="PC13",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_C, .pin=14,},   .name="PC14",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_C, .pin=15,},   .name="PC15",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  },

#define GPIO_CONFIG_UNUSED_PINS     \
        GPIO_CONFIG_GPIO_MAP_PINS   \
        GPIO_CONFIG_GPIO_MAP_ERR_PINS   \
    {.Pad={.port=PORT_E, .pin=0,},   .name="InitToggle",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_E, .pin=1,},   .name="PE1",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_E, .pin=5,},   .name="PE5",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_E, .pin=6,},   .name="PE6",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_E, .pin=15,},   .name="PE15",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_A, .pin=5,},   .name="PA5",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_A, .pin=6,},   .name="PA6",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \
    {.Pad={.port=PORT_A, .pin=7,},   .name="PA7",  .mode = GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_AIR,  }, \



#ifdef HAS_UART3
#define GPIO_CONFIG_UART3_PINS     \
    {.Pad={.port = PORT_B, .pin = 10,}, .name="UART3_TX",  .mux=GPIO_AF7_USART3, .mode = GPIO_API_MODE_ALT1, .pull = GPIO__PULL_UP, .speed = GPIO_SPEED_FREQ_VERY_HIGH,   .logic_level = GPIO_LVL_HI,},   \
    {.Pad={.port = PORT_B, .pin = 11,}, .name="UART3_RX",  .mux=GPIO_AF7_USART3, .mode = GPIO_API_MODE_ALT1, .pull = GPIO__PULL_UP, .speed = GPIO_SPEED_FREQ_VERY_HIGH,   .logic_level = GPIO_LVL_HI,},
#else
#define GPIO_CONFIG_UART3_PINS
#endif


#ifdef HAS_CAN1
#define GPIO_CONFIG_CAN1_PINS     \
    {.Pad={.port=PORT_A, .pin=11,}, .name="CAN1_RX", .mux = GPIO_AF9_CAN1, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH, },     \
    {.Pad={.port=PORT_A, .pin=12,}, .name="CAN1_TX", .mux = GPIO_AF9_CAN1, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, },
#else
#define GPIO_CONFIG_CAN1_PINS
#endif

#ifdef HAS_CAN2
#define GPIO_CONFIG_CAN2_PINS     \
    {.Pad={.port=PORT_B, .pin=12,}, .name="CAN2_RX", .mux = GPIO_AF9_CAN2, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH, },     \
    {.Pad={.port=PORT_B, .pin=13,}, .name="CAN2_TX", .mux = GPIO_AF9_CAN2, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, },
#else
#define GPIO_CONFIG_CAN2_PINS
#endif

#define GPIO_CONFIG_CAN_PINS    \
        GPIO_CONFIG_CAN1_PINS   \
        GPIO_CONFIG_CAN2_PINS


#ifdef HAS_SPI3
#define GPIO_CONFIG_SPI3_PINS     \
    {.Pad={.port=PORT_C, .pin=10,}, .name="SPI3_CLK",  .dir=GPIO_DIR_OUT, .pull=GPIO__PULL_AIR, .mux = GPIO_AF6_SPI3, .mode = GPIO_API_MODE_ALT1,   .speed=GPIO_SPEED_FREQ_VERY_HIGH, },     \
    {.Pad={.port=PORT_C, .pin=11,}, .name="SPI3_MISO", .dir=GPIO_DIR_IN,  .pull=GPIO__PULL_UP,  .mux = GPIO_AF6_SPI3, .mode = GPIO_API_MODE_ALT1,   .speed=GPIO_SPEED_FREQ_VERY_HIGH, },     \
    {.Pad={.port=PORT_C, .pin=12,}, .name="SPI3_MOSI", .dir=GPIO_DIR_OUT, .pull=GPIO__PULL_UP,  .mux = GPIO_AF6_SPI3, .mode = GPIO_API_MODE_ALT1,   .speed=GPIO_SPEED_FREQ_VERY_HIGH, },
#else
#define GPIO_CONFIG_SPI3_PINS
#endif

#ifdef HAS_LOG
#define GPIO_CFG_NAME_LD1 .name = "LD1",
#else
#define GPIO_CFG_NAME_LD1
#endif

#ifdef HAS_LOG
#define GPIO_CFG_NAME_LD5 .name = "LD5",
#else
#define GPIO_CFG_NAME_LD5
#endif


#define GPIO_CONFIG_LD5                             \
    {.Pad = {.port=PORT_J, .pin = 12,},             \
     .mux = 0,                                      \
     .mode = GPIO_API_MODE_OUTPUT,                  \
     .pull = GPIO__PULL_AIR,                        \
     .speed = GPIO_SPEED_FREQ_HIGH,                 \
     .logic_level = GPIO_LVL_LOW,                   \
      GPIO_CFG_NAME_LD5                             \
    },



#define GPIO_CONFIG_LEDS    GPIO_CONFIG_LD5        \
    {.Pad = {.port=PORT_I, .pin = 1,},             \
     .mux = 0,                                     \
     .mode = GPIO_API_MODE_OUTPUT,                 \
     .pull = GPIO__PULL_AIR,                       \
     .speed = GPIO_SPEED_FREQ_HIGH,                \
     .logic_level = GPIO_LVL_LOW,                  \
      GPIO_CFG_NAME_LD1                            \
    },

/*
WireName    GPIO    PinMux  PinMux  Pin
AUDIO_SDA   PH8 I2C3_SDA    AF4 P14
AUDIO_SCL   PH7 I2C3_SCL    AF4 N13
*/
#define GPIO_CONFIG_I2C3            \
    {.Pad = {.port = PORT_H, .pin = 7,}, .name = "AUDIO_SCL", .mode = GPIO_API_MODE_I2C, .pull=GPIO__PULL_UP, .mux=GPIO_AF4_I2C3, .logic_level=GPIO_LVL_HI}, \
    {.Pad = {.port = PORT_H, .pin = 8,}, .name = "AUDIO_SDA", .mode = GPIO_API_MODE_I2C, .pull=GPIO__PULL_UP, .mux=GPIO_AF4_I2C3, .logic_level=GPIO_LVL_HI},

#define GPIO_CONFIG_I2C                            \
        GPIO_CONFIG_I2C3

const GpioConfig_t SECTION_CFG_DATA GpioConfig[] = {

    GPIO_CONFIG_I2C
    GPIO_CONFIG_LEDS
    GPIO_CONFIG_UART1_PINS

#if 0
#endif

#if 0

    GPIO_CONFIG_UNUSED_PINS
    GPIO_CONFIG_ANALOG_INPUPT_PINS

    GPIO_CONFIG_SPI3_PINS
#endif


#ifdef HAS_MCO
#error That pads busy in schematic!
    {.Pad={.port=PORT_C, .pin=9,}, .name="MCO2", .mux = GPIO_AF0_MCO, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, },
    {.Pad={.port=PORT_A, .pin=8,}, .name="MCO1", .mux = GPIO_AF0_MCO, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, },
#endif /*HAS_MCO*/

#if 0
    //////-0---------------
    {.Pad={.port=PORT_B, .pin=14,}, .name="USB_DM", .mux=GPIO_AF12_OTG_HS_FS,  .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH,   .logic_level=GPIO_LVL_HI,},
    {.Pad={.port=PORT_B, .pin=15,}, .name="USB_DP", .mux=GPIO_AF12_OTG_HS_FS,  .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP,  .speed=GPIO_SPEED_FREQ_VERY_HIGH,   .logic_level=GPIO_LVL_HI,},
#ifdef HAS_USB
#endif /*HAS_USB*/


    {.Pad = {.port =PORT_D, .pin=1,}, .mux=0, .mode = GPIO_API_MODE_INPUT, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,  .logic_level=GPIO_LVL_LOW,
    #ifdef HAS_LOG
     .name="DEBUG.2",
    #endif
        },

    {.Pad = {.port =PORT_D, .pin=3,}, .mux=0, .mode = GPIO_API_MODE_INPUT, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,  .logic_level=GPIO_LVL_LOW,
    #ifdef HAS_LOG
     .name="DEBUG.3",
    #endif
        },



    {.Pad = {.port = PORT_C, .pin = 6,},.mux = 0,  .mode = GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_HIGH,  .logic_level=GPIO_LVL_LOW,
#ifdef HAS_LOG
     .name = "TX2_LED",
#endif
    },

    {.Pad = {.port = PORT_C, .pin = 10,}, .mux = 0, .mode = GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW, .logic_level=GPIO_LVL_LOW,
#ifdef HAS_LOG
     .name = "STATUS_LED",
#endif
    },

#ifdef HAS_LED
#endif /*HAS_LED*/


#endif

};

uint32_t gpio_get_cnt(void) {
    return ARRAY_SIZE(GpioConfig);
}
