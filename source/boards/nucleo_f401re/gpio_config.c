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

const GpioConfig_t GpioConfig[] = {

#ifdef HAS_BUZZER
    {.Pad={.port=PORT_A, .pin=15,}, .name="Buzzer",     .mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_LOW},
#endif /*HAS_BUZZER*/

    #ifdef HAS_UART2
    {.Pad={.port=PORT_A, .pin=2,}, .name="USART2_TX", .mode=GPIO_API_MODE_ALT1,    .mux=GPIO_AF7_USART2,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH,  .logic_level=GPIO_LVL_HI},
    {.Pad={.port=PORT_A, .pin=3,}, .name="USART2_RX", .mode=GPIO_API_MODE_ALT1,    .mux=GPIO_AF7_USART2,  .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH,   .logic_level=GPIO_LVL_HI},
#endif /*HAS_UART2*/

#ifdef HAS_SPI2
    { .Pad = {.port = PORT_B, .pin = 10, }, .name="SPI2_SCK",  .mode = GPIO_API_MODE_ALT1, .mux=GPIO_AF5_SPI2,   .pull=GPIO__PULL_AIR, .speed = GPIO_SPEED_FREQ_VERY_HIGH,    .logic_level=GPIO_LVL_LOW,},
    { .Pad = {.port = PORT_B, .pin = 14, }, .name="SPI2_MISO", .mode = GPIO_API_MODE_ALT1, .mux=GPIO_AF5_SPI2,   .pull=GPIO__PULL_UP, .speed = GPIO_SPEED_FREQ_VERY_HIGH,    .logic_level=GPIO_LVL_LOW,},
    { .Pad = {.port = PORT_B, .pin = 15, }, .name="SPI2_MOSI", .mode = GPIO_API_MODE_ALT1, .mux=GPIO_AF5_SPI2,   .pull=GPIO__PULL_UP, .speed = GPIO_SPEED_FREQ_VERY_HIGH,    .logic_level=GPIO_LVL_LOW,},
#endif /*HAS_SPI2*/

#ifdef HAS_SD_CARD
    {.Pad={.port=PORT_B, .pin=4,}, .name="SD_CARD_CS", .testable=true, .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=0, .logic_level=GPIO_LVL_HI},
#endif /*HAS_SD_CARD*/

#ifdef HAS_IR
    { .Pad = {.port=PORT_A, .pin=12,}, .mux = 0,  .name="IR_SENS", .connector1="", .connector2="", .mode = GPIO_API_MODE_INPUT_EXINT_BOTH_EDGE, .pull=GPIO__PULL_UP,   .logic_level = GPIO_LVL_HI,},
#endif

#ifdef HAS_I2C1
    {.Pad={.port=PORT_B, .pin=8, }, .name="I2C1_SCL",  .mode=GPIO_API_MODE_I2C, .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH,  .mux= GPIO_AF4_I2C1,},
    {.Pad={.port=PORT_B, .pin=9, }, .name="I2C1_SDA",  .mode=GPIO_API_MODE_I2C, .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH,  .mux= GPIO_AF4_I2C1,},
#endif /*HAS_I2C1*/

#ifdef HAS_SI4703
    {.Pad={.port=PORT_A, .pin=1,}, .name="SI4703_Rst",  .mux=0,   .mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_LOW,                    .logic_level=GPIO_LVL_LOW},
    {.Pad={.port=PORT_A, .pin=4,}, .name="SI4703_Sen",    .mux=0,   .mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_LOW,                 .logic_level=GPIO_LVL_LOW},
    {.Pad={.port=PORT_A, .pin=8,}, .name="SI4703_GPIO1",  .mux=0,   .mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,                  .logic_level=GPIO_LVL_LOW},
    {.Pad={.port=PORT_A, .pin=11,}, .name="SI4703_GPIO2",  .mux=0,   .mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,                  .logic_level=GPIO_LVL_LOW},
#endif

#ifdef HAS_SPI1
    {.Pad={.port=PORT_A, .pin=5,}, .name="SPI1_SCK",  .mode=GPIO_API_MODE_ALT1,    .mux=GPIO_AF5_SPI1,   .pull=GPIO__PULL_AIR, .speed = GPIO_SPEED_FREQ_VERY_HIGH,  .logic_level=GPIO_LVL_LOW,},
    {.Pad={.port=PORT_A, .pin=6,}, .name="SPI1_MISO", .mode=GPIO_API_MODE_ALT1,    .mux=GPIO_AF5_SPI1,   .pull=GPIO__PULL_AIR, .speed = GPIO_SPEED_FREQ_VERY_HIGH,  .logic_level=GPIO_LVL_LOW,},
    {.Pad={.port=PORT_A, .pin=7,}, .name="SPI1_MOSI", .mode=GPIO_API_MODE_ALT1,    .mux=GPIO_AF5_SPI1,   .pull=GPIO__PULL_AIR, .speed = GPIO_SPEED_FREQ_VERY_HIGH,  .logic_level=GPIO_LVL_LOW,},
#endif /*HAS_SPI1*/

#ifdef HAS_SW_UART
    {.Pad={.port=PORT_B, .pin=2, }, .name="SW_UART_Tx",   .mux = 0,   .mode=GPIO_API_MODE_OUTPUT,    .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_LOW,                .logic_level=GPIO_LVL_HI},
    {.Pad={.port=PORT_B, .pin=5, }, .name="SW_UART_Rx",  .mux = 0, .connector1="", .connector2="", .mode = GPIO_API_MODE_INPUT_EXINT_BOTH_EDGE, .pull=GPIO__PULL_UP,   .logic_level = GPIO_LVL_HI,},
#endif

#ifdef HAS_LED
    {.Pad={.port=PORT_A, .pin=5,}, .name="LED_G",     .mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_LOW},
#endif /*HAS_LED*/

#ifdef HAS_UART1
    {.Pad={.port=PORT_A, .pin=9,}, .mux=GPIO_AF7_USART1,  .name="USART1_TX", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH,   .logic_level=GPIO_LVL_HI},
    {.Pad={.port=PORT_A, .pin=10,},  .mux=GPIO_AF7_USART1, .name="USART1_RX", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH,  .logic_level=GPIO_LVL_HI},
#endif /*HAS_UART1*/


#ifdef HAS_UART6
    {.Pad={.port=PORT_A, .pin=11,}, .name="USART6_TX", .mux=GPIO_AF8_USART6,  .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .logic_level=GPIO_LVL_HI},
    {.Pad={.port=PORT_A, .pin=12,}, .name="USART6_RX", .mux=GPIO_AF8_USART6, .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .logic_level=GPIO_LVL_HI},
#endif /*HAS_UART6*/

    {.Pad={.port=PORT_C, .pin=13,}, .name="UserBtn",   .mode=GPIO_MODE_INPUT,      .pull=GPIO__PULL_AIR},

#ifdef HAS_MCO
    //{.Pad={.port=PORT_C, .pin=9}, .name="MCO_2",   .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH,  .mux= GPIO_AF0_MCO,},
    //{.Pad={.port=PORT_A, .pin=8}, .name="MCO_1",   .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH,  .mux= GPIO_AF0_MCO,},
#endif /*HAS_MCO*/

#ifdef HAS_ADC
    {.Pad={.port=PORT_A, .pin=0}, .name="ADC_CH0",   .mode=GPIO_MODE_ANALOG,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH,  .mux= 0,},
#endif /**/

#ifdef HAS_I2C3
    {.Pad={.port=PORT_C, .pin=9}, .name="I2C3_SDA",   .mode=GPIO_API_MODE_I2C,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH,  .mux= GPIO_AF4_I2C3,},
    {.Pad={.port=PORT_A, .pin=8}, .name="I2C3_SCL",   .mode=GPIO_API_MODE_I2C,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH,  .mux= GPIO_AF4_I2C3,},
#endif /*HAS_I2C3*/


#ifdef HAS_SX1262
    {.Pad={.port=PORT_B, .pin=3}, .name="LoRaBusy",  .mode=GPIO_MODE_INPUT,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_LOW},
    {.Pad={.port=PORT_A, .pin=8}, .name="LoRa_CS",   .mode= GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=0,               .logic_level=GPIO_LVL_HI},
    {.Pad={.port=PORT_A, .pin=0}, .name="LoRaRst",   .mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_HI},
#endif /*HAS_SX1262*/

};

uint32_t gpio_get_cnt(void) {
    return ARRAY_SIZE(GpioConfig);
}
