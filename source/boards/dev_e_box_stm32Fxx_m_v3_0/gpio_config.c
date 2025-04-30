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

const GpioConfig_t GpioConfig[] = {
#ifdef HAS_LED
    {.pad.port=PORT_A, .pad.pin=1, .name="LedGreem",     .connector1="-", .mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_HI},
#endif/*HAS_LED*/

#ifdef HAS_W25Q16BV
    {.pad={.port=PORT_A,  .pin=13}, .name="F_CS",     .mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_SPI1
    {.pad={.port=PORT_B, .pin=3}, .name="SPI1_SCK",    .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF5_SPI1, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_B, .pin=5},  .name="SPI1_MOSI",   .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF5_SPI1, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_B, .pin=4},  .name="SPI1_MISO",       .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF5_SPI1, .logic_level=GPIO_LVL_HI},
#endif /*HAS_SPI1*/


#ifdef HAS_BUTTON
    {.pad.port=PORT_A, .pad.pin=0,  .name="WKUP", .connector1="PA.0", .connector2="pin34", .mode=GPIO_API_MODE_INPUT_EXINT_RISING,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW, .mux=0, .logic_level=GPIO_LVL_HI},
#endif
    {.pad.port=PORT_B, .pad.pin=1,  .name="INT", .mode=GPIO_API_MODE_INPUT_EXINT_FAILLING,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_LOW, .mux=0, .logic_level=GPIO_LVL_HI},

#ifdef HAS_UART1
    {.pad={.port=PORT_A, .pin=9},  .name="UART1_TX",  .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF7_USART1, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_A, .pin=10},  .name="UART1_RX",  .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF7_USART1, .logic_level=GPIO_LVL_HI},
#endif /*HAS_UART1*/

#ifdef HAS_SI4703
    {.pad.port=PORT_C, .pad.pin=3,  .name="SI4703_RST",     .connector1="UEXT.8",  .connector2="JP1.3", .mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_LOW},
    {.pad.port=PORT_C, .pad.pin=2,  .name="SI4703_SEN",     .connector1="UEXT.7",  .connector2="JP1.4", .mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_D, .pad.pin=0,  .name="SI4703_GPIO1",   .connector1="PD.3",    .connector2="JP1.2", .mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_D, .pad.pin=1,  .name="SI4703_GPIO2",   .connector1="PD.4",    .connector2="JP1.1", .mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_HI},
#endif /*HAS_SI4703*/

#ifdef HAS_I2C1
    {.pad={.port=PORT_B, .pin=6}, .name="I2C1_SCL", .mode=GPIO_MODE_AF_OD,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF4_I2C1, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_B, .pin=7}, .name="I2C1_SDA", .mode=GPIO_MODE_AF_OD,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF4_I2C1, .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_I2C2
    {.pad.port=PORT_B, .pad.pin=10,  .name="I2C2_SCL", .mode=GPIO_MODE_AF_OD,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF4_I2C2, .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_B, .pad.pin=11,  .name="I2C2_SDA", .mode=GPIO_MODE_AF_OD,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF4_I2C2, .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_I2C3
    //{.pad.port=PORT_X, .pad.pin=x, .name="I2C3_SCL",   .connector1="Host", .connector2="",  .mode=GPIO_MODE_AF_OD,  .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=xxxxxxx, .logic_level=xxxxxx},
    //{.pad.port=PORT_X, .pad.pin=x,  .name="I2C3_SDA",   .connector1="Host", .connector2="", .mode=GPIO_MODE_AF_OD,  .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=xxxxxxx, .logic_level=xxxxxx},
#endif

#ifdef HAS_USB_DEVICE
    {.pad.port=PORT_B, .pad.pin=15, .name="OTG_HS_DP",     .connector1="USB_OTG.D+",  .connector2="", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF12_OTG_HS_FS, .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_B, .pad.pin=14, .name="OTG_HS_DM",     .connector1="USB_OTG.D-",  .connector2="", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF12_OTG_HS_FS, .logic_level=GPIO_LVL_HI},
#endif /*HAS_USB_DEVICE*/

#ifdef HAS_USB_HOST
    {.pad.port=PORT_A, .pad.pin=9,  .name="OTG_FS_VBUS",   .connector1="PA9", .connector2="USB_HOST.1", .mode=GPIO_MODE_INPUT,     .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW, .mux=0, .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_A, .pad.pin=11, .name="OTG_FS_DM",     .connector1="D-", .connector2="USB_HOST.2", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF10_OTG_FS, .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_A, .pad.pin=12, .name="OTG_FS_DP",     .connector1="D+", .connector2="USB_HOST.3", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF10_OTG_FS, .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_SDIO
    {.pad.port=PORT_D, .pad.pin=2,  .name="SD_CMD", .connector1="SD.3", .connector2="PD.5", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_C, .pad.pin=12, .name="SD_CLK", .connector1="SD.5", .connector2="",     .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_C, .pad.pin=8,  .name="SD_D0",  .connector1="SD.7", .connector2="",     .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_C, .pad.pin=9,  .name="SD_D1",  .connector1="SD.8", .connector2="",     .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_C, .pad.pin=10, .name="SD_D2",  .connector1="SD.1", .connector2="",     .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_C, .pad.pin=11, .name="SD_D3",  .connector1="SD.2", .connector2="",     .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI},
#endif /*HAS_SDIO*/

#ifdef HAS_USART6
    {.pad.port=PORT_C, .pad.pin=6,  .name="USART6_TX",  .connector1="UEXT.3",.mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_HIGH_SPEED, .mux=GPIO_AF8_USART6, .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_C, .pad.pin=7,  .name="USART6_RX",  .connector1="UEXT.4",.mode=GPIO_API_MODE_ALT1,             .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_HIGH_SPEED,             .mux=GPIO_AF8_USART6,            .logic_level=GPIO_LVL_HI},
#endif /*HAS_USART6*/
};

uint32_t gpio_get_cnt(void) {
    return ARRAY_SIZE(GpioConfig);
}
