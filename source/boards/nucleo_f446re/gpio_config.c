#include "gpio_config.h"

#include "data_utils.h"
#include "gpio_mcal.h"
#include "gpio_types.h"
#include "stm32f4xx_hal.h"
#include "sys_config.h"
#include "gpio_custom_const.h"

const GpioConfig_t GpioConfig[] = {
#ifdef HAS_LED
    {.pad={.port=PORT_A, .pin=5}, .testable=true,  .dir=GPIO_DIR_OUT, .name="LED_G", .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, /* .speed=GPIO_SPEED_FREQ_LOW, */       .mux=0,               .logic_level=GPIO_LVL_LOW},
#endif /**/
    {.pad={.port=PORT_C, .pin=13},  .testable=false,  .dir=GPIO_DIR_IN, .name="UserBtn", .mode=GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .pull=GPIO__PULL_UP, /* .speed=GPIO_SPEED_FREQ_LOW, */ .mux=0,  .logic_level=GPIO_LVL_LOW,},

#ifdef HAS_DWM1000
    {.pad={.port=PORT_A, .pin=1},  .testable=true,  .dir=GPIO_DIR_OUT,.name="DWM1000_CS", .mode=GPIO_API_MODE_OUTPUT, .dir=GPIO_DIR_OUT, .pull=GPIO__PULL_AIR, /* .speed=GPIO_SPEED_FREQ_LOW, */  .mux=0,   .logic_level=GPIO_LVL_HI,  },
    {.pad={.port=PORT_C, .pin=7},  .testable=false, .name="DWM1000_RST", .mode=GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .pull=GPIO__PULL_AIR, /* .speed=GPIO_SPEED_FREQ_LOW, */  .mux=0,   .logic_level=GPIO_LVL_HI,  },
    {.pad={.port=PORT_C, .pin=8},  .testable=false, .dir=GPIO_DIR_IN, .name="DWM1000_IRQ", .mode=GPIO_API_MODE_INPUT, .dir=GPIO_DIR_IN, .pull=GPIO__PULL_AIR, /* .speed=GPIO_SPEED_FREQ_LOW, */  .mux=0,   .logic_level=GPIO_LVL_LOW,  },
    {.pad={.port=PORT_C, .pin=11}, .testable=true,  .dir=GPIO_DIR_OUT, .name="DWM1000_WKP", .mode=GPIO_API_MODE_OUTPUT,  .dir=GPIO_DIR_OUT, .pull=GPIO__PULL_AIR, /* .speed=GPIO_SPEED_FREQ_LOW, */  .mux=0,    .logic_level=GPIO_LVL_HI,  },
#endif /*HAS_DWM1000*/

#ifdef HAS_MCO
    {.pad={.port=PORT_A, .pin=8}, .name="MCO_1",  .dir=GPIO_DIR_OUT,  .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */  .mux= GPIO_AF0_MCO,},
    {.pad={.port=PORT_C, .pin=9}, .name="MCO_2",  .dir=GPIO_DIR_OUT,  .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */  .mux= GPIO_AF0_MCO,},
#endif /*HAS_MCO*/

#ifdef HAS_ADC
    {.pad={.port=PORT_A, .pin=0}, .name="ADC_CH0",  .dir=GPIO_DIR_IN,  .mode=GPIO_API_MODE_ANALOG,      .pull=GPIO__PULL_AIR, /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */  .mux= 0,},
#endif /**/

#ifdef HAS_I2C1
    {.pad={.port=PORT_B, .pin=6}, .name="I2C1_SCL", .dir=GPIO_DIR_OUT,   .mode=GPIO_API_MODE_I2C,      .pull=GPIO__PULL_UP, /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */  .mux= GPIO_AF4_I2C1,},
    {.pad={.port=PORT_B, .pin=7}, .name="I2C1_SDA",   .mode=GPIO_API_MODE_I2C,      .pull=GPIO__PULL_UP, /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */  .mux= GPIO_AF4_I2C1,},
#endif /*HAS_I2C1*/

#ifdef HAS_I2S2
    {.pad={.port=PORT_C, .pin=1}, .name="I2S2_SD",   .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */  .mux= GPIO_AF7_SPI2,},
    {.pad={.port=PORT_A, .pin=6}, .name="I2S2_MCK", .dir=GPIO_DIR_OUT,   .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */  .mux= GPIO_AF6_SPI2,},
    {.pad={.port=PORT_B, .pin=10}, .name="I2S2_CK",   .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */  .mux= GPIO_AF5_SPI2,},
    {.pad={.port=PORT_B, .pin=12}, .name="I2S2_WS",   .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */  .mux= GPIO_AF5_SPI2,},
#endif /*HAS_I2S2*/

#ifdef HAS_I2C3
    {.pad = {.port = PORT_C, .pin = 9}, .name="I2C3_SDA",   .mode=GPIO_API_MODE_I2C,      .pull=GPIO__PULL_UP, /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */  .mux= GPIO_AF4_I2C3,},
    {.pad = {.port = PORT_A, .pin = 8}, .name="I2C3_SCL", .dir=GPIO_DIR_OUT,   .mode=GPIO_API_MODE_I2C,      .pull=GPIO__PULL_UP, /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */  .mux= GPIO_AF4_I2C3,},
#endif /*HAS_I2C3*/


#ifdef HAS_UART1
    {.pad={.port=PORT_A, .pin=9},  .name="USART1_TX", .dir=GPIO_DIR_OUT, .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */ .mux=GPIO_AF7_USART1, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_A, .pin=10}, .name="USART1_RX", .dir=GPIO_DIR_IN, .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP, /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */  .mux=GPIO_AF7_USART1, .logic_level=GPIO_LVL_HI},
#endif /*HAS_UART1*/


#ifdef HAS_UART2
    {.pad={.port=PORT_A, .pin=2}, .name="USART2_TX", .dir=GPIO_DIR_OUT, .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */ .mux=GPIO_AF7_USART2, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_A, .pin=3}, .name="USART2_RX", .dir=GPIO_DIR_IN, .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP, /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */ .mux=GPIO_AF7_USART2, .logic_level=GPIO_LVL_HI},
#endif /*HAS_UART2*/

#ifdef HAS_UART3
    {.pad={.port=PORT_B, .pin=10}, .name="USART3_TX", .dir=GPIO_DIR_OUT, .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */ .mux=GPIO_AF7_USART3, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_B, .pin=11}, .name="USART3_RX", .dir=GPIO_DIR_IN, .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_UP, /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */ .mux=GPIO_AF7_USART3, .logic_level=GPIO_LVL_HI},
#endif /*HAS_UART3*/


#ifdef HAS_SPI1
    {.pad={.port=PORT_A, .pin=5}, .name="SPI1_SCK/LED",  .dir=GPIO_DIR_OUT, .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */ .mux=GPIO_AF5_SPI1,   .logic_level=GPIO_LVL_LOW},
    {.pad={.port=PORT_A, .pin=6}, .name="SPI1_MISO", .dir=GPIO_DIR_IN,    .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */ .mux=GPIO_AF5_SPI1,   .logic_level=GPIO_LVL_LOW},
    {.pad={.port=PORT_A, .pin=7}, .name="SPI1_MOSI",   .dir=GPIO_DIR_OUT,   .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */ .mux=GPIO_AF5_SPI1,   .logic_level=GPIO_LVL_LOW},
#endif /*HAS_SPI1*/

#ifdef HAS_SPI2
    {.pad={.port=PORT_B, .pin=10}, .name="SPI2_SCK",  .dir=GPIO_DIR_OUT,  .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */ .mux=GPIO_AF5_SPI2,   .logic_level=GPIO_LVL_LOW},
    {.pad={.port=PORT_B, .pin=14}, .name="SPI2_MISO", .dir=GPIO_DIR_IN,  .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */ .mux=GPIO_AF5_SPI2,   .logic_level=GPIO_LVL_LOW},
    {.pad={.port=PORT_B, .pin=15}, .name="SPI2_MOSI",  .dir=GPIO_DIR_OUT, .mode=GPIO_API_MODE_ALT1,      .pull=GPIO__PULL_AIR, /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */ .mux=GPIO_AF5_SPI2,   .logic_level=GPIO_LVL_LOW},
#endif /*HAS_SPI2*/

#ifdef HAS_SD_CARD
    {.pad.port=PORT_B, .pad.pin=4, .name="SD_CARD_CS",  .dir=GPIO_DIR_OUT, .testable=true, .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, /* /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */ */ .mux=0, .logic_level=GPIO_LVL_HI},
#endif /**/

#ifdef HAS_SX1262
    {.pad={.port=PORT_B, .pin=3}, .name="LoRaBusy",  .mode=GPIO_API_MODE_INPUT,      .pull=GPIO__PULL_AIR, /* .speed=GPIO_SPEED_FREQ_LOW, */       .mux=0,               .logic_level=GPIO_LVL_LOW},
    {.pad={.port=PORT_A, .pin=8}, .name="LoRa_CS",  .dir=GPIO_DIR_OUT,  .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, /* .speed=GPIO_SPEED_FREQ_VERY_HIGH, */ .mux=0,               .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_A, .pin=0}, .name="LoRaRst",  .dir=GPIO_DIR_OUT,  .mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO__PULL_AIR, /* .speed=GPIO_SPEED_FREQ_LOW, */       .mux=0,               .logic_level=GPIO_LVL_HI},
#endif /*HAS_SX1262*/

};

uint32_t gpio_get_cnt(void) {
    return ARRAY_SIZE(GpioConfig);
}
