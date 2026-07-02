#include "gpio_config.h"

#include "data_utils.h"
#include "gpio_mcal.h"
#include "gpio_types.h"
#include "stm32f4xx_hal.h"
#include "sys_config.h"

#ifndef USE_HAL_DRIVER
#error "that file only for STM32 MCUs"
#endif

#include "gpio_custom_const.h"

#ifdef HAS_SDIO
#define GPIO_CONFIG_SDIO                                           \
    {.Pad={ .port=PORT_C, .pin=12, },  .name="SD_CLK", .connector1="SD.5", .connector2="",     .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI,}, \
    {.Pad={ .port=PORT_D, .pin=2,  },  .name="SD_CMD", .connector1="SD.3", .connector2="PD.5", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI,}, \
    {.Pad={ .port=PORT_C, .pin=8,  },  .name="SD_D0",  .connector1="SD.7", .connector2="",     .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI,}, \
    {.Pad={ .port=PORT_C, .pin=9,  },  .name="SD_D1",  .connector1="SD.8", .connector2="",     .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI,}, \
    {.Pad={ .port=PORT_C, .pin=10, },  .name="SD_D2",  .connector1="SD.1", .connector2="",     .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI,}, \
    {.Pad={ .port=PORT_C, .pin=11, },  .name="SD_D3",  .connector1="SD.2", .connector2="",     .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI,},
#else
#define GPIO_CONFIG_SDIO
#endif

#ifdef HAS_I2S2
#define GPIO_CONFIG_I2S2                                                                                                                                                                       \
    {.Pad = {.port=PORT_C, .pin=2,},  .connector2="J3.36/PC2", .mux = 6, .dir=GPIO_DIR_IN,  .name="I2S2_SDEXT", .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .logic_level=GPIO_LVL_HI,   },    \
    {.Pad = {.port=PORT_B, .pin=13,}, .connector2="J4.4/PB13", .mux = 5, .dir=GPIO_DIR_OUT, .name="I2S2_CK",    .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_DOWN, .logic_level=GPIO_LVL_HI, },    \
    {.Pad = {.port=PORT_B, .pin=12,}, .connector2="J3.11/PB12", .mux = 5, .dir=GPIO_DIR_OUT, .name="I2S2_WS",    .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .logic_level=GPIO_LVL_HI,   },    \
    {.Pad = {.port=PORT_C, .pin=3,}, .connector2="J3.35/PC3",   .mux = 5, .dir=GPIO_DIR_OUT, .name="I2S2_SD",    .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .logic_level=GPIO_LVL_HI,   },

#else
#define GPIO_CONFIG_I2S2
#endif

#define GPIO_CONFIG_I2S   \
        GPIO_CONFIG_I2S2

#ifdef HAS_UART1
#define GPIO_CONFIG_UART1                           \
    {.Pad = {.port = PORT_A, .pin = 9,},            \
     .name = "UART1_TX",                            \
     .mode = GPIO_API_MODE_ALT1,                    \
     .pull = GPIO__PULL_AIR,                        \
     .speed = GPIO_SPEED_HIGH_SPEED,                \
     .mux = GPIO_AF7_USART1,                        \
     .logic_level = GPIO_LVL_HI,},                  \
    {.Pad = {.port=PORT_A, .pin=10,},               \
     .name = "UART1_RX",                            \
     .mode = GPIO_API_MODE_ALT1,                    \
     .pull = GPIO__PULL_UP,                         \
     .speed = GPIO_SPEED_HIGH_SPEED,                \
     .mux = GPIO_AF7_USART1,                        \
     .logic_level = GPIO_LVL_HI,},
#else
#define GPIO_CONFIG_UART1
#endif /*HAS_UART1*/

#ifdef HAS_UART2
#define GPIO_CONFIG_UART2           \
    {.Pad={.port=PORT_A, .pin=2,},  \
     .name="USART2_TX",             \
     .mode=GPIO_API_MODE_ALT1,      \
     .pull=GPIO__PULL_AIR,          \
     .speed=GPIO_SPEED_HIGH_SPEED,  \
     .mux=GPIO_AF7_USART2,          \
     .logic_level=GPIO_LVL_HI,},    \
    {.Pad={.port=PORT_A, .pin=3,},  \
     .name="USART2_RX",             \
     .mode=GPIO_API_MODE_ALT1,      \
     .pull=GPIO__PULL_UP,           \
     .speed=GPIO_SPEED_HIGH_SPEED,  \
     .mux=GPIO_AF7_USART2,          \
     .logic_level=GPIO_LVL_HI,      \
    },

#else
#define GPIO_CONFIG_UART2
#endif /*HAS_UART2*/

#ifdef HAS_UART6
#define GPIO_CONFIG_UART6                                  \
    {.Pad={ .port=PORT_C, .pin=6,  },                      \
     .name = "USART6_TX",                                  \
     .connector1 = "UEXT.3",                               \
     .mode = GPIO_API_MODE_ALT1,                           \
     .pull = GPIO__PULL_AIR,                               \
     .speed=GPIO_SPEED_HIGH_SPEED,                         \
     .mux=GPIO_AF8_USART6,                                 \
     .logic_level=GPIO_LVL_HI},                            \
    {.Pad={ .port=PORT_C, .pin=7,  },  .name="USART6_RX",  \
     .connector1="UEXT.4",.mode=GPIO_API_MODE_ALT1,        \
     .pull=GPIO__PULL_AIR,                                 \
     .speed=GPIO_SPEED_HIGH_SPEED,                         \
     .mux=GPIO_AF8_USART6,                                 \
     .logic_level=GPIO_LVL_HI,                             \
    },

#else
#define GPIO_CONFIG_UART6
#endif

#define GPIO_CONFIG_UART    \
        GPIO_CONFIG_UART1   \
        GPIO_CONFIG_UART2   \
        GPIO_CONFIG_UART6

#ifdef HAS_I2C1
#define GPIO_CONFIG_I2C1                                                                                                            \
    {.Pad = {.port = PORT_B, .pin=6, }, .name="I2C1_SCL", .mode=GPIO_API_MODE_I2C,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF4_I2C1, .logic_level=GPIO_LVL_HI,},               \
    {.Pad = {.port = PORT_B, .pin=7, }, .name="I2C1_SDA", .mode=GPIO_API_MODE_I2C,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF4_I2C1, .logic_level=GPIO_LVL_HI,},
#else
#define GPIO_CONFIG_I2C1
#endif

#ifdef HAS_I2C2
#define GPIO_CONFIG_I2C2                                                                                                                                                               \
    {.Pad={.port=PORT_B, .pin=10,  }, .name="I2C2_SCL", .mode=GPIO_API_MODE_I2C,   .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF4_I2C2, .logic_level=GPIO_LVL_HI,},   \
    {.Pad={.port=PORT_B, .pin=11, },  .name="I2C2_SDA", .mode=GPIO_API_MODE_I2C,   .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF4_I2C2, .logic_level=GPIO_LVL_HI,},
#else
#define GPIO_CONFIG_I2C2
#endif

#ifdef HAS_I2C3
#define GPIO_CONFIG_I2C3    \
    {.Pad={ .port=PORT_X, .pin=x, },  .name="I2C3_SCL",   .mode=GPIO_API_MODE_I2C,  .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=xxxxxxx, .logic_level=xxxxxx},    \
    {.Pad={ .port=PORT_X, .pin=x,  },  .name="I2C3_SDA",   .mode=GPIO_API_MODE_I2C,  .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=xxxxxxx, .logic_level=xxxxxx},
#else
#define GPIO_CONFIG_I2C3
#endif

#define GPIO_CONFIG_I2C    \
        GPIO_CONFIG_I2C1   \
        GPIO_CONFIG_I2C2   \
        GPIO_CONFIG_I2C3

const GpioConfig_t GpioConfig[] = {
        GPIO_CONFIG_I2S
        GPIO_CONFIG_I2C
        GPIO_CONFIG_UART
        GPIO_CONFIG_SDIO

#ifdef HAS_GAME_PAD_PS2
    {.Pad = {.port = PORT_B, .pin = 12,}, .name="PS2_CS", .connector1 = "-", .mode = GPIO_API_MODE_OUTPUT,  .pull = GPIO__PULL_AIR, .speed = GPIO_SPEED_FREQ_LOW,  .mux = 0, .logic_level = GPIO_LVL_HI,},
#endif /*HAS_GAME_PAD_PS2*/

#ifdef HAS_SPI1
    {.Pad = {.port=PORT_B, .pin=3,},  .name="SPI1_SCK",   .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF5_SPI1, .logic_level=GPIO_LVL_HI,},
    {.Pad = {.port=PORT_B, .pin=5,},  .name="SPI1_MOSI",  .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP,  .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF5_SPI1, .logic_level=GPIO_LVL_HI,},
    {.Pad = {.port=PORT_B, .pin=4,},  .name="SPI1_MISO",  .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP,  .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF5_SPI1, .logic_level=GPIO_LVL_HI,},
#endif /*HAS_SPI1*/



#ifdef HAS_SPI2
    {.Pad = {.port=PORT_B, .pin=13,}, .name="SPI2_SCK",  .mode=GPIO_API_MODE_ALT1,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF5_SPI2,   .logic_level=GPIO_LVL_LOW,},
    {.Pad = {.port=PORT_B, .pin=14,}, .name="SPI2_MISO", .mode=GPIO_API_MODE_ALT1,  .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF5_SPI2,   .logic_level=GPIO_LVL_LOW,},
    {.Pad = {.port=PORT_B, .pin=15,}, .name="SPI2_MOSI", .mode=GPIO_API_MODE_ALT1,  .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF5_SPI2,   .logic_level=GPIO_LVL_LOW,},
#endif /* HAS_SPI2 */

#ifdef HAS_LED
    {.Pad={ .port=PORT_A, .pin=1, }, .name="LedGreem",     .connector1="-", .mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_HI,},
#endif

    { .Pad = {.port=PORT_A, .pin=5,}, .mux = 0,  .name="IR_SENS", .connector1="", .connector2="", .mode = GPIO_API_MODE_INPUT_EXINT_BOTH_EDGE, .pull=GPIO__PULL_UP,   .logic_level = GPIO_LVL_HI,},
#ifdef HAS_TIMER8
    { .Pad = {.port=PORT_C, .pin=6,},  .mux = GPIO_AF3_TIM8,  .name="TIM8_CH1", .connector1="", .connector2="", .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR,  .logic_level = GPIO_LVL_HI,},
#endif /**/

#ifdef HAS_TIMER10
    { .Pad = {.port=PORT_B, .pin=8,},  .mux = GPIO_AF3_TIM10,  .name="TIM10_CH1", .connector1="", .connector2="", .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR,  .logic_level = GPIO_LVL_HI,},
#endif /*HAS_TIMER10*/

#ifdef HAS_TIMER1
    {.Pad={.port=PORT_E, .pin=13,}, .mux=GPIO_AF1_TIM1, .name="TIM1_CH3", .connector1="pin66", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR,  .logic_level=GPIO_LVL_HI,},
    {.Pad={.port=PORT_E, .pin=14,}, .mux=GPIO_AF1_TIM1, .name="TIM1_CH4", .connector1="pin67", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR,  .logic_level=GPIO_LVL_HI,},
#endif /*HAS_TIMER1*/
  //  { .Pad = {.port=PORT_E, .pin=0,}, .name="IR_SENS1", .connector1="J2.44", .connector2="pin97", .mode = GPIO_API_MODE_INPUT_EXINT_BOTH_EDGE, .pull=GPIO__PULL_UP,   .mux = 0, .logic_level = GPIO_LVL_HI},
  //  { .Pad = {.port=PORT_E, .pin=1,}, .name="IR_SENS2", .connector1="", .connector2="", .mode = GPIO_API_MODE_INPUT_EXINT_BOTH_EDGE, .pull=GPIO__PULL_UP,   .mux = 0, .logic_level = GPIO_LVL_HI},

    //{.Pad={ .port=PORT_A, .pin=4, .name="Buzzer",     .connector1="-", .mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_MEDIUM,       .mux=0,               .logic_level=GPIO_LVL_LOW},


#ifdef HAS_TIMER3
    {.Pad = {.port=PORT_A, .pin=6,}, .mux=GPIO_AF2_TIM3, .name="TIM3_CH1*", .connector1="pin42", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR,  .logic_level=GPIO_LVL_HI,},
    {.Pad = {.port=PORT_A, .pin=7,}, .mux=GPIO_AF2_TIM3, .name="TIM3_CH2", .connector1="pin43", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR,  .logic_level=GPIO_LVL_HI,},
#endif /*HAS_TIMER3*/

#ifdef HAS_TIMER4
    {.Pad={.port=PORT_D, .pin=12,}, .mux=GPIO_AF2_TIM4, .name="TIM4_CH1", .connector1="", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR,  .logic_level=GPIO_LVL_HI,},
#endif /*HAS_TIMER4*/


#ifdef HAS_W25Q16BV
    {.Pad={.port=PORT_A,  .pin=13,}, .name="F_CS",     .mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_HI,},
#endif

#ifdef HAS_BUTTON
    {.Pad={ .port=PORT_A, .pin=0, },   .name="WKUP", .connector1="PA.0", .connector2="pin34", .mode=GPIO_API_MODE_INPUT_EXINT_RISING,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW, .mux=0, .logic_level=GPIO_LVL_HI,},
#endif
   // {.Pad={ .port=PORT_B, .pin=1,  .name="INT", .mode=GPIO_API_MODE_INPUT_EXINT_FAILLING,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_LOW, .mux=0, .logic_level=GPIO_LVL_HI},


#ifdef HAS_SI4703
    {.Pad={ .port=PORT_C, .pin=3,},  .name="SI4703_RST",     .connector1="UEXT.8",  .connector2="JP1.3", .mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_LOW,},
    {.Pad={ .port=PORT_C, .pin=2,},  .name="SI4703_SEN",     .connector1="UEXT.7",  .connector2="JP1.4", .mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_HI,},
    {.Pad={ .port=PORT_D, .pin=0,},  .name="SI4703_GPIO1",   .connector1="PD.3",    .connector2="JP1.2", .mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_HI,},
    {.Pad={ .port=PORT_D, .pin=1,},  .name="SI4703_GPIO2",   .connector1="PD.4",    .connector2="JP1.1", .mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_HI,},
#endif /*HAS_SI4703*/


#ifdef HAS_USB_DEVICE
    {.Pad={ .port=PORT_B, .pin=15, }, .name="OTG_HS_DP",     .connector1="USB_OTG.D+",  .connector2="", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF12_OTG_HS_FS, .logic_level=GPIO_LVL_HI,},
    {.Pad={ .port=PORT_B, .pin=14, },  .name="OTG_HS_DM",     .connector1="USB_OTG.D-",  .connector2="", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF12_OTG_HS_FS, .logic_level=GPIO_LVL_HI,},
#endif /*HAS_USB_DEVICE*/

#ifdef HAS_USB_HOST
    {.Pad={ .port=PORT_A, .pin=9, },   .name="OTG_FS_VBUS",   .connector1="PA9", .connector2="USB_HOST.1", .mode=GPIO_MODE_INPUT,     .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW, .mux=0, .logic_level=GPIO_LVL_HI,},
    {.Pad={ .port=PORT_A, .pin=11, },  .name="OTG_FS_DM",     .connector1="D-", .connector2="USB_HOST.2", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF10_OTG_FS, .logic_level=GPIO_LVL_HI,},
    {.Pad={ .port=PORT_A, .pin=12, },  .name="OTG_FS_DP",     .connector1="D+", .connector2="USB_HOST.3", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF10_OTG_FS, .logic_level=GPIO_LVL_HI,},
#endif

};

uint32_t gpio_get_cnt(void) {
    return ARRAY_SIZE(GpioConfig);
}
