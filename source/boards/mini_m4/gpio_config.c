#include "gpio_config.h"

#include "data_utils.h"
#include "gpio_mcal.h"
#include "gpio_types.h"
#include "stm32f4xx_hal.h"
#include "sys_config.h"

#ifndef USE_HAL_DRIVER
#error "that wile only for STM32 MCUs"
#endif /*USE_HAL_DRIVER*/

#include "gpio_stm_const.h"

GpioConfig_t GpioConfig[] = {
    {.pad.port=PORT_A, .pad.pin=9, .name="OTG_FS_Vbus",  .connector1="-",.mode=GPIO_MODE_INPUT,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_HI},
#ifdef HAS_LED
    {.pad.port = PORT_C, .pad.pin = 12, .name = "LedRed",  .testable=true,   .connector1 = "-",.mode = GPIO_API_MODE_OUTPUT,  .pull = GPIO__PULL_AIR, .speed = GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_HI},
    {.pad.port = PORT_C, .pad.pin = 13, .name = "LedYellow", .testable=true, .connector1 = "-",.mode = GPIO_API_MODE_OUTPUT,  .pull = GPIO__PULL_AIR, .speed = GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_HI},
#endif /*HAS_LED*/

#if defined(HAS_LOG) && defined(HAS_UART)
    {.pad.port=PORT_B, .pad.pin=6,  .name="USART1_TX",  .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF7_USART1, .logic_level=GPIO_LVL_HI},
#ifdef HAS_CLI
    {.pad.port=PORT_B, .pad.pin=7,  .name="USART1_RX",  .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF7_USART1, .logic_level=GPIO_LVL_HI},
#endif /*HAS_CLI*/
#endif /*HAS_LOG*/

#ifdef HAS_USB_DEVICE
    {.pad.port=PORT_A, .pad.pin=11, .name="USB-D_N",     .connector1="OTG_FS_D_N",  .connector2="", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF10_OTG_FS, .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_A, .pad.pin=12, .name="USB-D_P",     .connector1="OTG_FS_D_P",  .connector2="", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF10_OTG_FS, .logic_level=GPIO_LVL_HI},
#endif /*HAS_USB_DEVICE*/

#ifdef HAS_USB_HOST
    //{.pad.port=PORT_A, .pad.pin=9,  .name="OTG_FS_VBUS",   .connector1="PA9", .connector2="USB_HOST.1", .mode=GPIO_MODE_INPUT,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW, .mux=0, .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_A, .pad.pin=11, .name="USB-D_N",     .connector1="D-", .connector2="USB_HOST.2", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF10_OTG_FS, .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_A, .pad.pin=12, .name="USB-D_P",     .connector1="D+", .connector2="USB_HOST.3", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF10_OTG_FS, .logic_level=GPIO_LVL_HI},
#endif /*HAS_USB_HOST*/

#ifdef HAS_SDIO
    {.pad.port=PORT_D, .pad.pin=2,  .name="SD_CMD", .connector1="CMD", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_C, .pad.pin=12, .name="SD_CLK", .connector1="CLK", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_C, .pad.pin=8,  .name="SD_D0",  .connector1="DO0", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_C, .pad.pin=9,  .name="SD_D1",  .connector1="DO1", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_C, .pad.pin=10, .name="SD_D2",  .connector1="DO2", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_C, .pad.pin=11, .name="SD_D3",  .connector1="DO3", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI},
#endif /*HAS_SDIO*/

#ifdef HAS_SD_CARD
    {.pad.port=PORT_A, .pad.pin=4, .name="SD_CARD_CS", .testable=true, .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=0, .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_SPI
    {.pad.port=PORT_A, .pad.pin=5, .name="SPI1_SCK",   .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF5_SPI1, .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_A, .pad.pin=6, .name="SPI1_MISO",  .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP,  .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF5_SPI1, .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_A, .pad.pin=7, .name="SPI1_MOSI",  .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP,  .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF5_SPI1, .logic_level=GPIO_LVL_HI},
#endif /*HAS_SPI*/
};

uint32_t gpio_get_cnt(void) {
    return ARRAY_SIZE(GpioConfig);
}
