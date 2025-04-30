#include "gpio_config.h"

#include "data_utils.h"

#include "gpio_mcal.h"
#include "gpio_types.h"

#include "stm32f4xx_hal.h"
#include "sys_config.h"

#ifndef USE_HAL_DRIVER
#error "that wile only for STM32 MCUs"
#endif /*USE_HAL_DRIVER*/

#include "gpio_custom_const.h"

GpioConfig_t GpioConfig[] = {

#ifdef HAS_BUTTON
    {.pad = {.port=PORT_A, .pin=0}, .name="UserBtn", .stm_mode=GPIO_MODE_INPUT, .dir=GPIO_DIR_IN, .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_LOW, .mux=0,   .logic_level=GPIO_LVL_HI,  },
#endif

#ifdef HAS_I2C1
    {.pad = {.port=PORT_B, .pin=6},  .name="I2C1_SCL",     .stm_mode=GPIO_MODE_AF_OD,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_HIGH, .mux=GPIO_AF4_I2C1, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_B, .pin=7},  .name="I2C1_SDA",     .stm_mode=GPIO_MODE_AF_OD,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_HIGH, .mux=GPIO_AF4_I2C1, .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_DWM1000
    {.pad={.port=PORT_A, .pin=4}, .testable=false, .name="DWM1000_RST", .stm_mode=GPIO_MODE_INPUT, .dir=GPIO_DIR_IN, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,  .mux=0,   .logic_level=GPIO_LVL_HI,  },
    {.pad={.port=PORT_A, .pin=1}, .testable=false, .name="DWM1000_IRQ", .stm_mode=GPIO_MODE_INPUT, .dir=GPIO_DIR_IN, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,  .mux=0,   .logic_level=GPIO_LVL_LOW,  },
    {.pad={.port=PORT_A, .pin=2}, .testable=true,  .name="DWM1000_CS", .stm_mode=GPIO_API_MODE_OUTPUT, .dir=GPIO_DIR_OUT, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,  .mux=0,   .logic_level=GPIO_LVL_HI,  },
    {.pad={.port=PORT_A, .pin=3}, .testable=true,  .name="DWM1000_WKP", .stm_mode=GPIO_API_MODE_OUTPUT,  .dir=GPIO_DIR_OUT, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,  .mux=0,    .logic_level=GPIO_LVL_HI,  },
#endif /*HAS_DWM1000*/

#ifdef HAS_LED_MONO
    {.pad = {.port=PORT_C, .pin=13},  .testable=true, .name="LedGreen",     .stm_mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_HI},
#endif/*HAS_LED*/

#ifdef HAS_MCO1
    {.pad = {.port=PORT_A , .pin=8}, .name="MCO1",   .stm_mode=GPIO_API_MODE_ALT1,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,  .mux=GPIO_AF0_MCO},
#endif

#ifdef HAS_SPI1
    {.pad={.port=PORT_A, .pin=5}, .name="SPI1_SCK",  .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF5_SPI1,   .logic_level=GPIO_LVL_LOW},
    {.pad={.port=PORT_A, .pin=6}, .name="SPI1_MISO", .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF5_SPI1,   .logic_level=GPIO_LVL_LOW},
    {.pad={.port=PORT_A, .pin=7}, .name="SPI1_MOSI", .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF5_SPI1,   .logic_level=GPIO_LVL_LOW},
#endif /*HAS_SPI1*/

#ifdef HAS_UART1
    {.pad = {.port=PORT_A, .pin=9},  .name="USART1_TX", .stm_mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF7_USART1, .logic_level=GPIO_LVL_HI},
#ifdef HAS_CLI
    {.pad = {.port=PORT_A, .pin=10},  .name="USART1_RX", .stm_mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF7_USART1, .logic_level=GPIO_LVL_HI},
#endif /*HAS_CLI*/
#endif /*HAS_UART1*/
    /*{.pad = {.port=PORT_B, .pin=14, .name="I2S_ext_SD",                      .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW, .mux=GPIO_AF6_I2S2ext, .logic_level=GPIO_LVL_HI},*/
};

uint32_t gpio_get_cnt(void) {
    return ARRAY_SIZE(GpioConfig);
}
