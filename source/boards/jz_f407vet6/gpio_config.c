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

#define GPIO_CONFIG_LASER   \
    {.Pad={.port=PORT_A, .pin=8,}, .name="TIM1_CH1", .mux = GPIO_AF1_TIM1, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, }, \
    {.Pad={.port=PORT_E, .pin=5,}, .name="laser", .mux = GPIO_AF3_TIM9, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, }, \
    {.Pad={.port=PORT_B, .pin=7,}, .name="laser", .mux = GPIO_AF2_TIM4, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, }, \
    {.Pad={.port=PORT_A, .pin=6,}, .name="laser", .mux = GPIO_AF2_TIM3, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, },

const GpioConfig_t GpioConfig[] = {
        GPIO_CONFIG_LASER

        { .Pad = { .port = PORT_A, .pin = 5 },
          .mode = GPIO_API_MODE_OUTPUT, .pull = GPIO__PULL_AIR, .mux = 0, .logic_level = GPIO_LVL_HI,
    #ifdef HAS_LOG
          .name = "LedRed",
    #endif
        },

    { .Pad = { .port = PORT_E, .pin = 13 },
      .mode = GPIO_API_MODE_OUTPUT, .pull = GPIO__PULL_AIR, .mux = 0, .logic_level = GPIO_LVL_HI,
#ifdef HAS_LOG
      .name = "LedRed",
#endif
    },

    { .Pad = { .port = PORT_E, .pin = 14 },
      .mode = GPIO_API_MODE_OUTPUT, .pull = GPIO__PULL_AIR, .mux = 0, .logic_level = GPIO_LVL_HI,
#ifdef HAS_LOG
      .name = "LedRed",
#endif
    },

    { .Pad = { .port = PORT_E, .pin = 15 },
      .mode = GPIO_API_MODE_OUTPUT, .pull = GPIO__PULL_AIR, .mux = 0, .logic_level = GPIO_LVL_HI,
#ifdef HAS_LOG
      .name = "LedRed",
#endif
    },

    { .Pad = { .port = PORT_A, .pin = 6 },
      .mode = GPIO_API_MODE_OUTPUT, .pull = GPIO__PULL_AIR, .mux = 0, .logic_level = GPIO_LVL_LOW,
#ifdef HAS_LOG
      .name = "DEBUG",
#endif
    },

    { .Pad = { .port = PORT_A, .pin = 5 },
      .mode = GPIO_API_MODE_OUTPUT, .pull = GPIO__PULL_AIR, .mux = 0, .logic_level = GPIO_LVL_LOW,
#ifdef HAS_LOG
      .name = "DEBUG_SC",
#endif
    },

    { .Pad = { .port = PORT_A, .pin = 4 },
      .mode = GPIO_API_MODE_OUTPUT, .pull = GPIO__PULL_AIR, .mux = 0, .logic_level = GPIO_LVL_LOW,
#ifdef HAS_LOG
      .name = "DEBUG_2",
#endif
    },


    { .Pad = { .port = PORT_A, .pin = 3 },
      .mode = GPIO_API_MODE_OUTPUT, .pull = GPIO__PULL_AIR, .mux = 0, .logic_level = GPIO_LVL_LOW,
#ifdef HAS_LOG
      .name = "DEBUG_PA3",
#endif
    },

    { .Pad = { .port = PORT_C, .pin = 13 },
      .mode = GPIO_API_MODE_OUTPUT, .pull = GPIO__PULL_AIR, .mux = 0, .logic_level = GPIO_LVL_LOW,
#ifdef HAS_LOG
      .name = "DEBUG_3",
#endif
    },

    { .Pad = { .port = PORT_C, .pin = 0 },
      .mode = GPIO_API_MODE_OUTPUT, .pull = GPIO__PULL_AIR, .mux = 0, .logic_level = GPIO_LVL_LOW,
#ifdef HAS_LOG
      .name = "DEBUG_PC0",
#endif
    },

#ifdef HAS_LED
#endif/*HAS_LED*/

#ifdef HAS_USB
    {.Pad={.port=PORT_A, .pin=12,}, .name="USB_FS_DP", .mux = GPIO_AF10_OTG_FS,  .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP,  .speed=GPIO_SPEED_FREQ_VERY_HIGH,   .logic_level=GPIO_LVL_HI,},
    {.Pad={.port=PORT_A, .pin=11,}, .name="USB_FS_DM", .mux = GPIO_AF10_OTG_FS,  .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH,   .logic_level=GPIO_LVL_HI,},
#endif /*HAS_USB*/

#ifdef HAS_CAN1
    {.Pad={.port=PORT_D, .pin=1,}, .name="CAN1_TX", .mux = GPIO_AF9_CAN1, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, },
    {.Pad={.port=PORT_D, .pin=0,}, .name="CAN1_RX", .mux = GPIO_AF9_CAN1, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH, },
#endif /*HAS_CAN1*/

#ifdef HAS_CAN2
    {.Pad={.port=PORT_B, .pin=5,}, .name="CAN2_RX", .mux = GPIO_AF9_CAN2, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH, },
    {.Pad={.port=PORT_B, .pin=6,}, .name="CAN2_TX", .mux = GPIO_AF9_CAN2, .mode = GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, },
#endif /*HAS_CAN2*/

#ifdef HAS_BUTTON
    {.Pad = {.port=PORT_E, .pin=10,}, .name="SW1", .mode=GPIO_API_MODE_INPUT_EXINT_FAILLING, .pull=GPIO__PULL_AIR,   .mux=0, .logic_level=GPIO_LVL_HI},
    {.Pad = {.port=PORT_E, .pin=11,}, .name="SW2", .mode=GPIO_API_MODE_INPUT_EXINT_FAILLING, .pull=GPIO__PULL_AIR,   .mux=0, .logic_level=GPIO_LVL_HI},
    {.Pad = {.port=PORT_E, .pin=12,}, .name="SW3", .mode=GPIO_API_MODE_INPUT_EXINT_FAILLING, .pull=GPIO__PULL_AIR,   .mux=0, .logic_level=GPIO_LVL_HI},
#endif



#ifdef HAS_UART1
    {.Pad = {.port=PORT_A, .pin=10, }, .name="USART1_RX",   .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP,   .mux=GPIO_AF7_USART1, .logic_level=GPIO_LVL_HI},
    {.Pad = {.port=PORT_A, .pin=9,  }, .name="USART1_TX",   .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR,  .mux=GPIO_AF7_USART1, .logic_level=GPIO_LVL_HI},
#endif /*HAS_UART1*/

#ifdef HAS_UART2
    {.Pad = {.port=PORT_D, .pin=6,}, .name="USART2_RX",   .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP,  .mux=GPIO_AF7_USART2, .logic_level=GPIO_LVL_HI},
    {.Pad = {.port=PORT_D, .pin=5,}, .name="USART2_TX",   .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR,  .mux=GPIO_AF7_USART2, .logic_level=GPIO_LVL_HI},
#endif /*HAS_UART2*/

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

#ifdef HAS_SDIO
    {.Pad = {.port=PORT_C, .pin=12,}, .name="SD_CLK", .connector1="SD.5",, .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR,  .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI},
    {.Pad = {.port=PORT_D, .pin=2, }, .name="SD_CMD", .connector1="SD.3", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP,  .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI},
    {.Pad = {.port=PORT_C, .pin=8, }, .name="SD_D0", .connector1="SD.7",  .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP,  .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI},
    {.Pad = {.port=PORT_C, .pin=9, }, .name="SD_D1", .connector1="SD.8",  .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP,  .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI},
    {.Pad = {.port=PORT_C, .pin=10,}, .name="SD_D2", .connector1="SD.1",  .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP,  .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI},
    {.Pad = {.port=PORT_C, .pin=11,}, .name="SD_D3", .connector1="SD.2",  .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP,  .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI},
#endif /*HAS_SDIO*/

#ifdef HAS_I2C2
    {.Pad = {.port=PORT_F, .pin=1}, .name="I2C2_SCL",  .mode=GPIO_API_MODE_I2C, .pull=GPIO__PULL_UP,  .mux=GPIO_AF4_I2C2, .logic_level=GPIO_LVL_HI},
    {.Pad = {.port=PORT_F, .pin=0}, .name="I2C2_SDA",  .mode=GPIO_API_MODE_I2C, .pull=GPIO__PULL_UP,  .mux=GPIO_AF4_I2C2, .logic_level=GPIO_LVL_HI},
#endif


#ifdef HAS_UART6
    {.Pad = {.port=PORT_C, .pin=6}, .name="USART6_TX", .mode=GPIO_API_MODE_ALT1, .mux=GPIO_AF8_USART6, .pull=GPIO__PULL_AIR,  .logic_level=GPIO_LVL_HI},
    {.Pad = {.port=PORT_C, .pin=7}, .name="USART6_RX", .mode=GPIO_API_MODE_ALT1,  .mux=GPIO_AF8_USART6, .pull=GPIO__PULL_UP,  .logic_level=GPIO_LVL_HI},
#endif /*HAS_USART6*/

#ifdef HAS_I2C1
    {.pad = {.port = PORT_B, .pin = 8}, .name="I2C1_SCL",   .mode=GPIO_API_MODE_I2C, .pull=GPIO__PULL_UP,  .mux=GPIO_AF4_I2C1, .logic_level=GPIO_LVL_HI},
    {.pad = {.port = PORT_B, .pin = 9}, .name="I2C1_SDA",   .mode=GPIO_API_MODE_I2C, .pull=GPIO__PULL_UP,  .mux=GPIO_AF4_I2C1, .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_UART3
    {.Pad = {.port=PORT_B, .pin=10}, .name="UART3_TX",   .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR,  .mux=GPIO_AF7_USART3, .logic_level=GPIO_LVL_HI},
    {.Pad = {.port=PORT_B, .pin=11}, .name="UART3_RX",   .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP,  .mux=GPIO_AF7_USART3, .logic_level=GPIO_LVL_HI},
#endif /*HAS_UART3*/

};

uint32_t gpio_get_cnt(void) {
    return ARRAY_SIZE(GpioConfig);
}
