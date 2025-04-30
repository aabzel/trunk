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
    {.pad={.port=PORT_A, .pin=5}, .name="LED_G",     .stm_mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_LOW},
	{.pad={.port=PORT_C, .pin=13}, .name="UserBtn",   .stm_mode=GPIO_MODE_INPUT,      .pull=GPIO__PULL_AIR},
#endif /**/

#ifdef HAS_MCO
	//{.pad={.port=PORT_C, .pin=9}, .name="MCO_2",   .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH,  .mux= GPIO_AF0_MCO,},
	//{.pad={.port=PORT_A, .pin=8}, .name="MCO_1",   .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH,  .mux= GPIO_AF0_MCO,},
#endif /*HAS_MCO*/

#ifdef HAS_ADC
	{.pad={.port=PORT_A, .pin=0}, .name="ADC_CH0",   .stm_mode=GPIO_MODE_ANALOG,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH,  .mux= 0,},
#endif /**/

#ifdef HAS_I2C1
	{.pad={.port=PORT_B, .pin=6}, .name="I2C1_SCL",   .stm_mode=GPIO_MODE_AF_OD,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH,  .mux= GPIO_AF4_I2C1,},
	{.pad={.port=PORT_B, .pin=7}, .name="I2C1_SDA",   .stm_mode=GPIO_MODE_AF_OD,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH,  .mux= GPIO_AF4_I2C1,},
#endif /*HAS_I2C1*/

#ifdef HAS_I2C3
	{.pad={.port=PORT_C, .pin=9}, .name="I2C3_SDA",   .stm_mode=GPIO_MODE_AF_OD,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH,  .mux= GPIO_AF4_I2C3,},
	{.pad={.port=PORT_A, .pin=8}, .name="I2C3_SCL",   .stm_mode=GPIO_MODE_AF_OD,      .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH,  .mux= GPIO_AF4_I2C3,},
#endif /*HAS_I2C3*/

#ifdef HAS_LOG
    {.pad={.port=PORT_A, .pin=2}, .name="USART2_TX", .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF7_USART2, .logic_level=GPIO_LVL_HI},
#endif /*HAS_LOG*/

#ifdef HAS_CLI
    {.pad={.port=PORT_A, .pin=3}, .name="USART2_RX", .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF7_USART2, .logic_level=GPIO_LVL_HI},
#endif /*HAS_CLI*/

#ifdef HAS_SPI1
	{.pad={.port=PORT_A, .pin=5}, .name="SPI1_SCK",  .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF5_SPI1,   .logic_level=GPIO_LVL_LOW},
    {.pad={.port=PORT_A, .pin=6}, .name="SPI1_MISO", .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF5_SPI1,   .logic_level=GPIO_LVL_LOW},
    {.pad={.port=PORT_A, .pin=7}, .name="SPI1_MOSI", .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF5_SPI1,   .logic_level=GPIO_LVL_LOW},
#endif /*HAS_SPI1*/

#ifdef HAS_SPI2
	{.pad={.port=PORT_B, .pin=10}, .name="SPI2_SCK",  .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF5_SPI2,   .logic_level=GPIO_LVL_LOW},
    {.pad={.port=PORT_B, .pin=14}, .name="SPI2_MISO", .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF5_SPI2,   .logic_level=GPIO_LVL_LOW},
    {.pad={.port=PORT_B, .pin=15}, .name="SPI2_MOSI", .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF5_SPI2,   .logic_level=GPIO_LVL_LOW},
#endif /*HAS_SPI2*/

#ifdef HAS_SD_CARD
    {.pad.port=PORT_B, .pad.pin=4, .name="SD_CARD_CS", .testable=true, .stm_mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=0, .logic_level=GPIO_LVL_HI},
#endif /**/


#ifdef HAS_SX1262
    {.pad={.port=PORT_B, .pin=3}, .name="LoRaBusy",  .stm_mode=GPIO_MODE_INPUT,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_LOW},
    {.pad={.port=PORT_A, .pin=8}, .name="LoRa_CS",   .stm_mode= GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=0,               .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_A, .pin=0}, .name="LoRaRst",   .stm_mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_HI},
#endif /*HAS_SX1262*/

};

uint32_t gpio_get_cnt(void) {
    return ARRAY_SIZE(GpioConfig);
}
