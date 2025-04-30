#include "gpio_config.h"

#include "data_utils.h"

#include "gpio_mcal.h"

#include "stm32f4xx_hal.h"
#include "sys_config.h"

#ifndef USE_HAL_DRIVER
#error "that wile only for STM32 MCUs"
#endif /*USE_HAL_DRIVER*/

#include "gpio_custom_const.h"


GpioConfig_t GpioConfig[] = {
#ifdef HAS_ADC1
    {.pad = {.port=PORT_A, .pin=1},  .name="ADC1_CH1",  .connector1="?",   .stm_mode=GPIO_MODE_ANALOG,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=0, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_A, .pin=2},  .name="ADC1_CH2",  .connector1="?",   .stm_mode=GPIO_MODE_ANALOG,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=0, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_A, .pin=4},  .name="ADC1_CH4",  .connector1="?",   .stm_mode=GPIO_MODE_ANALOG,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=0, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_A, .pin=5},  .name="ADC1_CH5",  .connector1="?",   .stm_mode=GPIO_MODE_ANALOG,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=0, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_A, .pin=6},  .name="ADC1_CH6",  .connector1="?",   .stm_mode=GPIO_MODE_ANALOG,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=0, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_A, .pin=7},  .name="ADC1_CH7",  .connector1="?",   .stm_mode=GPIO_MODE_ANALOG,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=0, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_B, .pin=0},  .name="ADC1_CH8",  .connector1="?",   .stm_mode=GPIO_MODE_ANALOG,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=0, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_B, .pin=1},  .name="ADC1_CH9",  .connector1="?",   .stm_mode=GPIO_MODE_ANALOG,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=0, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_C, .pin=4},  .name="ADC1_CH14",  .connector1="?",  .stm_mode=GPIO_MODE_ANALOG,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=0, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_C, .pin=5},  .name="ADC1_CH15",  .connector1="?",  .stm_mode=GPIO_MODE_ANALOG,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=0, .logic_level=GPIO_LVL_HI},
#if 0
    {.pad = {.port=PORT_C, .pin=3},  .name="ADC1_CH13",  .connector1="?",  .stm_mode=GPIO_MODE_ANALOG,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=0, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_C, .pin=2},  .name="ADC1_CH12",  .connector1="?",  .stm_mode=GPIO_MODE_ANALOG,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=0, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_C, .pin=0},  .name="ADC1_CH10",  .connector1="?",  .stm_mode=GPIO_MODE_ANALOG,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=0, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_C, .pin=1},  .name="ADC1_CH11",  .connector1="?",  .stm_mode=GPIO_MODE_ANALOG,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=0, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_A, .pin=3},  .name="ADC1_CH3",  .connector1="?",   .stm_mode=GPIO_MODE_ANALOG,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=0, .logic_level=GPIO_LVL_HI},
#endif

#endif /*HAS_ADC1*/

#ifdef HAS_BUTTON
    {.pad={.port=PORT_C, .pin=13}, .testable=false, .name="UserBtn", .dir=GPIO_DIR_IN, .stm_mode=GPIO_MODE_INPUT,   .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW, .mux=0, .logic_level=GPIO_LVL_LOW},
#endif

#ifdef HAS_I2C1
    {.pad = {.port=PORT_B, .pin=9},  .name="I2C1_SDA", .connector1="CN7.4",  .stm_mode=GPIO_MODE_AF_OD,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_HIGH, .mux=GPIO_AF4_I2C1, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_B, .pin=8},  .name="I2C1_SCL", .connector1="CN7.2",  .stm_mode=GPIO_MODE_AF_OD,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_HIGH, .mux=GPIO_AF4_I2C1, .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_I2C2
    {.pad = {.port=PORT_B, .pin=10}, .name="I2C2_SCL", .connector1="CN10.32",.connector2="J10.13",  .stm_mode=GPIO_MODE_AF_OD,             .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF4_I2C2, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_B, .pin=11}, .name="I2C2_SDA", .connector1="CN10.34",.connector2="J10.15",  .stm_mode=GPIO_MODE_AF_OD,             .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF4_I2C2, .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_DWM1000
    {.pad={.port=PORT_C, .pin=7},  .testable=false, .name="DWM1000_RST", .stm_mode=GPIO_MODE_INPUT, .dir=GPIO_DIR_IN, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,  .mux=0,   .logic_level=GPIO_LVL_HI,  },
    {.pad={.port=PORT_C, .pin=8},  .testable=false, .name="DWM1000_IRQ", .stm_mode=GPIO_MODE_INPUT, .dir=GPIO_DIR_IN, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,  .mux=0,   .logic_level=GPIO_LVL_LOW,  },
    {.pad={.port=PORT_D, .pin=0},  .testable=true, .name="DWM1000_CS", .stm_mode=GPIO_API_MODE_OUTPUT, .dir=GPIO_DIR_OUT, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,  .mux=0,   .logic_level=GPIO_LVL_HI,  },
    {.pad={.port=PORT_C, .pin=11}, .testable=true, .name="DWM1000_WKP", .stm_mode=GPIO_API_MODE_OUTPUT,  .dir=GPIO_DIR_OUT, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,  .mux=0,    .logic_level=GPIO_LVL_HI,  },
#endif /*HAS_DWM1000*/

	#ifdef HAS_FDA801
    {.pad = {.port=PORT_A, .pin=3},  .testable=true, .name="EN1",      .connector1="CN9.1",  .connector2="J10.23",  .stm_mode=GPIO_API_MODE_OUTPUT,         .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,             .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_D, .pin=7},  .testable=true, .name="EN2",      .connector1="CN9.2",  .connector2="J10.25",  .stm_mode=GPIO_API_MODE_OUTPUT,         .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,             .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_C, .pin=0},  .testable=true, .name="EN3",      .connector1="CN9.3",  .connector2="J10.27",  .stm_mode=GPIO_API_MODE_OUTPUT,         .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,             .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_C, .pin=1},  .testable=true, .name="MUTE",     .connector1="CN9.7",  .connector2="J10.31",  .stm_mode=GPIO_API_MODE_OUTPUT,         .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,             .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_C, .pin=3},  .name="CD/DIAG",  .connector1="CN9.5",  .connector2="J10.19",  .stm_mode=GPIO_API_MODE_INPUT_EXINT_RISING_FALLING, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,             .logic_level=GPIO_LVL_HI},
#endif /*HAS_FDA801*/

#ifdef HAS_I2S4
    {.pad = {.port=PORT_E, .pin=2},  .name="I2S4_CK",  .connector1="CN9.14", .connector2="J10.1",   .stm_mode=GPIO_API_MODE_ALT1,             .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=GPIO_AF5_SPI4, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_E, .pin=6},  .name="I2S4_SD",  .connector1="CN9.20", .connector2="J10.5",   .stm_mode=GPIO_API_MODE_ALT1,             .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=GPIO_AF5_SPI4, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_E, .pin=4},  .name="I2S4_WS",  .connector1="CN9.16", .connector2="J10.3",   .stm_mode=GPIO_API_MODE_ALT1,             .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_HIGH,      .mux=GPIO_AF5_SPI4, .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_USART2
    {.pad = {.port=PORT_D, .pin=5},  .name="USART2_TX",  .connector1="CN9.6",  .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF7_USART2, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_D, .pin=6},  .name="USART2_RX",  .connector1="CN9.4",  .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF7_USART2, .logic_level=GPIO_LVL_HI},
#endif /*HAS_USART2*/

#ifdef HAS_I2S1
    {.pad = {.port=PORT_A, .pin=15}, .name="I2S1_WS",    .connector1="CN7.9",  .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW, .mux=GPIO_AF5_SPI1, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_B, .pin=3},  .name="I2S1_CK",    .connector1="CN7.15", .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW, .mux=GPIO_AF5_SPI1, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_B, .pin=5},  .name="I2S1_SD",    .connector1="CN7.13", .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW, .mux=GPIO_AF5_SPI1, .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_I2S2
    {.pad = {.port=PORT_B, .pin=12}, .name="I2S2_A_WS",  .connector1="CN7.7",  .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW, .mux=GPIO_AF5_SPI2, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_B, .pin=13}, .name="I2S2_A_CK",  .connector1="CN7.5",  .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW, .mux=GPIO_AF5_SPI2, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_B, .pin=15}, .name="I2S2_A_SD",  .connector1="CN7.3",  .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW, .mux=GPIO_AF5_SPI2, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_C, .pin=2},  .name="I2S_ext_SD", .connector1="CN10.9", .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW, .mux=GPIO_AF6_I2S2ext, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_C, .pin=6},  .name="I2S2_A_MCK", .connector1="CN7.1",  .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW, .mux=GPIO_AF5_SPI2, .logic_level=GPIO_LVL_HI},
#endif /*HAS_I2S2*/

#ifdef HAS_SI4737
    {.pad = {.port=PORT_D, .pin=14}, .name="SI4737_RCLK",.connector1="CN7.16",  .connector2="J2.7",         .stm_mode=GPIO_API_MODE_ALT1,     .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW, .mux=GPIO_AF2_TIM4, .logic_level=GPIO_LVL_LOW},
    {.pad = {.port=PORT_E, .pin=0},  .name="SI4737_RST", .connector1="CN10.33", .connector2="J2.11",        .stm_mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,       .logic_level=GPIO_LVL_LOW},
#endif /*HAS_SI4737*/

#ifdef HAS_MCO1
    {.pad = {.port= , .pin=}, .name="MCO1", .connector1="?", .stm_mode=GPIO_API_MODE_ALT1,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,  .mux=GPIO_AF0_MCO},
#endif

#ifdef HAS_MCO2
    {.pad = {.port=PORT_C, .pin=9}, .name="MCO2", .connector1="CN8.4", .stm_mode=GPIO_API_MODE_ALT1,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,  .mux=GPIO_AF0_MCO},
#endif

#ifdef HAS_SPI2
    {.pad={.port=PORT_A, .pin=9}, .name="SPI2_SCK",  .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF5_SPI2,   .logic_level=GPIO_LVL_LOW},
    {.pad={.port=PORT_A, .pin=12}, .name="SPI2_MISO", .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF5_SPI2,   .logic_level=GPIO_LVL_LOW},
    {.pad={.port=PORT_A, .pin=10}, .name="SPI2_MOSI", .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF5_SPI2,   .logic_level=GPIO_LVL_LOW},
#endif /*HAS_SPI2*/

#ifdef HAS_SPI3
    {.pad={.port=PORT_C, .pin=10}, .name="SPI3_SCK",  .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF6_SPI3,   .logic_level=GPIO_LVL_LOW},
    {.pad={.port=PORT_B, .pin=4 }, .name="SPI3_MISO", .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF6_SPI3,   .logic_level=GPIO_LVL_LOW},
    {.pad={.port=PORT_C, .pin=12}, .name="SPI3_MOSI", .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF6_SPI3,   .logic_level=GPIO_LVL_LOW},
#endif /*HAS_SPI2*/

#ifdef HAS_UART3
    {.pad = {.port=PORT_D, .pin=8},  .name="USART3_TX",  .connector1="CN12.10",.stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF7_USART3, .logic_level=GPIO_LVL_HI},
#ifdef HAS_CLI
    {.pad = {.port=PORT_D, .pin=9},  .name="USART3_RX",  .connector1="CN11.69",.stm_mode=GPIO_API_MODE_ALT1,  .pull=GPIO__PULL_UP, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF7_USART3, .logic_level=GPIO_LVL_HI},
#endif /*HAS_CLI*/
#endif /*HAS_UART3*/

#ifdef HAS_LED_MONO
    {.pad = {.port=PORT_B, .pin=7},  .testable=true, .name="LedBlue",    .connector1="CN11.21", .stm_mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_B, .pin=14}, .testable=true, .name="LedRed",     .connector1="CN12.28", .stm_mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .logic_level=GPIO_LVL_HI},
#endif/*HAS_LED*/
    /*{.pad = {.port=PORT_B, .pin=14, .name="I2S_ext_SD",                      .stm_mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW, .mux=GPIO_AF6_I2S2ext, .logic_level=GPIO_LVL_HI},*/
};



uint32_t gpio_get_cnt(void) {
    return ARRAY_SIZE(GpioConfig);
}
