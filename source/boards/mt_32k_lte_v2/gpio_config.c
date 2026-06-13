#include "gpio_config.h"

#include "data_utils.h"
#include "gpio_mcal.h"
#include "gpio_types.h"
#include "stm32f4xx_hal.h"
#include "sys_config.h"
#include "gpio_custom_const.h"

#ifndef USE_HAL_DRIVER
#error "that file only for STM32 MCUs"
#endif


#ifdef HAS_CAN1
#define GPIO_CONFIG_CAN1    \
    {.Pad={.port=PORT_D, .pin=1,}, .name="CAN1_TX", .mux = GPIO_AF9_CAN1, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, },   \
    {.Pad={.port=PORT_D, .pin=0,}, .name="CAN1_RX", .mux = GPIO_AF9_CAN1, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH, },
#else
#define GPIO_CONFIG_CAN1
#endif


#ifdef HAS_CAN2
#define GPIO_CONFIG_CAN2    \
    {.Pad={.port=PORT_B, .pin=5,}, .name="CAN2_RX", .mux = GPIO_AF9_CAN2, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH, },   \
    {.Pad={.port=PORT_B, .pin=6,}, .name="CAN2_TX", .mux = GPIO_AF9_CAN2, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, },
#else
#define GPIO_CONFIG_CAN2
#endif

#define GPIO_CONFIG_CAN     \
        GPIO_CONFIG_CAN1    \
        GPIO_CONFIG_CAN2

/*
PA5  NORFLASH, SPI1_SCK, тип PP
PA6  NORFLASH, SPI1_MISO
PA7  NORFLASH, SPI1_MOSI, тип PP
*/
#ifdef HAS_SPI1
#define GPIO_CONFIG_SPI1    \
    {.Pad={.port=PORT_A, .pin=5,}, .name="SPI1_SCK",  .mux = GPIO_AF5_SPI1, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, },   \
    {.Pad={.port=PORT_A, .pin=6,}, .name="SPI1_MISO", .mux = GPIO_AF5_SPI1, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH, },   \
    {.Pad={.port=PORT_A, .pin=7,}, .name="SPI1_MOSI", .mux = GPIO_AF5_SPI1, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH, },
#else
#define GPIO_CONFIG_SPI1
#endif

/*
PE2  NRF24L01, SPI5 SCK, тип PP
PE5  NRF24L01, SPI5 MISO
PE6  NRF24L01, SPI5 MOSI, тип PP
*/
#ifdef HAS_SPI5
#define GPIO_CONFIG_SPI5    \
    {.Pad={.port=PORT_E, .pin=3,}, .name="SPI5_SCK",  .mux = GPIO_AF6_SPI5, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, },   \
    {.Pad={.port=PORT_E, .pin=5,}, .name="SPI5_MISO", .mux = GPIO_AF6_SPI5, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH, },   \
    {.Pad={.port=PORT_E, .pin=6,}, .name="SPI5_MOSI", .mux = GPIO_AF6_SPI5, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH, },
#else
#define GPIO_CONFIG_SPI5
#endif

#define GPIO_CONFIG_SPI     \
        GPIO_CONFIG_SPI1    \
        GPIO_CONFIG_SPI5

#define GPIO_CONFIG_ADC

#define GPIO_CONFIG_DEBUG


#ifdef HAS_LOG
#define GPIO_LED_RED_NAME     .name = "LedRed",
#define GPIO_LED_GREEN_NAME   .name = "LedGReen",
#define GPIO_LED_BLUE_NAME    .name = "LedBlue",
#else
#define GPIO_LED_RED_NAME
#define GPIO_LED_GREEN_NAME
#define GPIO_LED_BLUE_NAME
#endif

#define GPIO_CONFIG_LED                                            \
    { .Pad = { .port = PORT_D, .pin = 13 },                                 \
      .mode = GPIO_API_MODE_OUTPUT,                                         \
      .pull = GPIO__PULL_AIR, .mux = 0,                                     \
      .logic_level = GPIO_LVL_LOW,                                          \
      GPIO_LED_RED_NAME                                                     \
    },                                                                      \
    { .Pad = { .port = PORT_D, .pin = 14 },                                 \
      .mode = GPIO_API_MODE_OUTPUT,                                         \
      .pull = GPIO__PULL_AIR, .mux = 0,                                     \
      .logic_level = GPIO_LVL_LOW,                                          \
      GPIO_LED_GREEN_NAME                                                   \
    },                                                                      \
    { .Pad = { .port = PORT_D, .pin = 15 },                                 \
      .mode = GPIO_API_MODE_OUTPUT,                                         \
      .pull = GPIO__PULL_AIR, .mux = 0,                                     \
      .logic_level = GPIO_LVL_LOW,                                          \
      GPIO_LED_BLUE_NAME                                                    \
    },                                                                      \
    { .Pad = { .port = PORT_G, .pin = 10 },                                 \
      .mode = GPIO_API_MODE_OUTPUT,                                         \
      .pull = GPIO__PULL_AIR, .mux = 0,                                     \
      .logic_level = GPIO_LVL_LOW,                                          \
    },

#ifdef HAS_BUTTON
#define  GPIO_CONFIG_BUTTOM    \
    {.Pad = {.port=PORT_F, .pin=14,}, .name="SW1", .mode=GPIO_API_MODE_INPUT_EXINT_FAILLING, .pull=GPIO__PULL_AIR,   .mux=0, .logic_level=GPIO_LVL_HI},  \
    {.Pad = {.port=PORT_C, .pin=13,}, .name="SW2", .mode=GPIO_API_MODE_INPUT_EXINT_FAILLING, .pull=GPIO__PULL_AIR,   .mux=0, .logic_level=GPIO_LVL_HI},
#else
#define  GPIO_CONFIG_BUTTOM
#endif


const GpioConfig_t GpioConfig[] = {
        GPIO_CONFIG_ADC
        GPIO_CONFIG_DEBUG
        GPIO_CONFIG_CAN
        GPIO_CONFIG_SPI
        GPIO_CONFIG_LED
        GPIO_CONFIG_BUTTOM

        { .Pad = { .port = PORT_B, .pin = 0 },
          .mode = GPIO_API_MODE_OUTPUT,
          .pull = GPIO__PULL_UP, .mux = 0,
          .logic_level = GPIO_LVL_HI,
          .name="CS,MX25L6433F",
        },

        { .Pad = { .port = PORT_C, .pin = 12 },
          .mode = GPIO_API_MODE_OUTPUT,
          .pull = GPIO__PULL_AIR, .mux = 0,
          .logic_level = GPIO_LVL_HI,
          .name="EVA M8M,LDO",
        },

#ifdef HAS_UART3
    {.Pad = {.port=PORT_C, .pin=10}, .name="USART3_TX",   .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR,  .mux=GPIO_AF7_USART3, .logic_level=GPIO_LVL_HI},
    {.Pad = {.port=PORT_C, .pin=11}, .name="USART3_RX",   .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP,  .mux=GPIO_AF7_USART3, .logic_level=GPIO_LVL_HI},
#endif /*HAS_UART3*/

#ifdef HAS_UART7
    /*PE8  XP3-1 Debug UART7 Tx, тип PP*/
    {.Pad = {.port=PORT_E, .pin=8,}, .name="USART7_TX", .mode=GPIO_API_MODE_ALT1, .mux=GPIO_AF8_UART7, .pull=GPIO__PULL_AIR,  .logic_level=GPIO_LVL_HI},
    /*PE7  XP3-2 Debug UART7 Rx*/
    {.Pad = {.port=PORT_E, .pin=7,}, .name="USART7_RX", .mode=GPIO_API_MODE_ALT1,  .mux=GPIO_AF8_UART7, .pull=GPIO__PULL_UP,  .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_USB
    {.Pad={.port=PORT_A, .pin=12,}, .name="USB_FS_DP", .mux = GPIO_AF10_OTG_FS,  .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP,  .speed=GPIO_SPEED_FREQ_VERY_HIGH,   .logic_level=GPIO_LVL_HI,},
    {.Pad={.port=PORT_A, .pin=11,}, .name="USB_FS_DM", .mux = GPIO_AF10_OTG_FS,  .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH,   .logic_level=GPIO_LVL_HI,},
#endif

#ifdef HAS_UART1
    {.Pad = {.port=PORT_A, .pin=10, }, .name="USART1_RX",   .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP,   .mux=GPIO_AF7_USART1, .logic_level=GPIO_LVL_HI},
    {.Pad = {.port=PORT_A, .pin=9,  }, .name="USART1_TX",   .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR,  .mux=GPIO_AF7_USART1, .logic_level=GPIO_LVL_HI},
#endif /*HAS_UART1*/

#ifdef HAS_UART2
    {.Pad = {.port=PORT_D, .pin=6,}, .name="USART2_RX",   .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP,  .mux=GPIO_AF7_USART2, .logic_level=GPIO_LVL_HI},
    {.Pad = {.port=PORT_D, .pin=5,}, .name="USART2_TX",   .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR,  .mux=GPIO_AF7_USART2, .logic_level=GPIO_LVL_HI},
#endif /*HAS_UART2*/

#ifdef HAS_UART4
    {.Pad = {.port=PORT_D, .pin=0,}, .name="UART4_RX",   .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP,  .mux=GPIO_AF11_UART4, .logic_level=GPIO_LVL_HI},
    {.Pad = {.port=PORT_D, .pin=1,}, .name="UART4_TX",   .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR,  .mux=GPIO_AF11_UART4, .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_UART6
    {.Pad = {.port=PORT_C, .pin=6}, .name="USART6_TX", .mode=GPIO_API_MODE_ALT1, .mux=GPIO_AF8_USART6, .pull=GPIO__PULL_AIR,  .logic_level=GPIO_LVL_HI},
    {.Pad = {.port=PORT_C, .pin=7}, .name="USART6_RX", .mode=GPIO_API_MODE_ALT1,  .mux=GPIO_AF8_USART6, .pull=GPIO__PULL_UP,  .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_UART8
    {.Pad = {.port=PORT_E, .pin=1, }, .name="UART8_TX", .mode=GPIO_API_MODE_ALT1, .mux=GPIO_AF8_UART8, .pull=GPIO__PULL_AIR,  .logic_level=GPIO_LVL_HI},
    {.Pad = {.port=PORT_E, .pin=0, }, .name="UART8_RX", .mode=GPIO_API_MODE_ALT1,  .mux=GPIO_AF8_UART8, .pull=GPIO__PULL_UP,  .logic_level=GPIO_LVL_HI},
#endif


#ifdef HAS_MCO
    {.Pad={.port=PORT_C, .pin=9,}, .name="MCO2", .mux = GPIO_AF0_MCO, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, },
    {.Pad={.port=PORT_A, .pin=8,}, .name="MCO1", .mux = GPIO_AF0_MCO, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, },
#endif /*HAS_MCO*/

#ifdef HAS_USB_DEVICE
   // {.Pad = {.port=PORT_A, .pin=9}, .name="OTG_FS_VBUS", .mode=GPIO_MODE_INPUT, .pull=GPIO__PULL_AIR,   .mux=0, .logic_level=GPIO_LVL_HI},
   // {.Pad = {.port=PORT_A, .pin=11}, .name="OTG_FS_DM",  .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR,  .mux=GPIO_AF10_OTG_FS, .logic_level=GPIO_LVL_HI},
   // {.Pad = {.port=PORT_A, .pin=12}, .name="OTG_FS_DP",  .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP,  .mux=GPIO_AF10_OTG_FS, .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_USB_HOST
   // {.Pad = {.port=PORT_B, .pin=15}, .name="OTG_HS_DP", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP,  .mux=GPIO_AF12_OTG_HS_FS, .logic_level=GPIO_LVL_HI},
   // {.Pad = {.port=PORT_B, .pin=14}, .name="OTG_HS_DM", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR,  .mux=GPIO_AF12_OTG_HS_FS, .logic_level=GPIO_LVL_HI},
#endif /*HAS_USB_DEVICE*/


#ifdef HAS_IR
    {.Pad = {.port=PORT_F, .pin=3},
#ifdef HAS_LOG
     .name="IR_SENS",
#endif
     .mode = GPIO_API_MODE_INPUT_EXINT_BOTH_EDGE, .pull=GPIO__PULL_AIR,   .mux = 0, .logic_level = GPIO_LVL_HI, } ,
#endif


#ifdef HAS_I2C2
    {.Pad = {.port=PORT_F, .pin=1}, .name="I2C2_SCL",  .mode=GPIO_API_MODE_I2C, .pull=GPIO__PULL_UP,  .mux=GPIO_AF4_I2C2, .logic_level=GPIO_LVL_HI},
    {.Pad = {.port=PORT_F, .pin=0}, .name="I2C2_SDA",  .mode=GPIO_API_MODE_I2C, .pull=GPIO__PULL_UP,  .mux=GPIO_AF4_I2C2, .logic_level=GPIO_LVL_HI},
#endif


#ifdef HAS_I2C1
    {.pad = {.port = PORT_B, .pin = 8}, .name="I2C1_SCL",   .mode=GPIO_API_MODE_I2C, .pull=GPIO__PULL_UP,  .mux=GPIO_AF4_I2C1, .logic_level=GPIO_LVL_HI},
    {.pad = {.port = PORT_B, .pin = 9}, .name="I2C1_SDA",   .mode=GPIO_API_MODE_I2C, .pull=GPIO__PULL_UP,  .mux=GPIO_AF4_I2C1, .logic_level=GPIO_LVL_HI},
#endif

};

uint32_t gpio_get_cnt(void) {
    return ARRAY_SIZE(GpioConfig);
}
