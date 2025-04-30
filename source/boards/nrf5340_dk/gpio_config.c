#include "gpio_config.h"

#include "data_utils.h"
#include "gpio_mcal.h"

const GpioConfig_t GpioConfig[] = {
#ifdef HAS_LED
#ifdef HAS_CORE_APP
    {.pad={.port=0, .pin=2}, .testable=true, .name="LedVirt", .dir=GPIO_DIR_INOUT, .logic_level=GPIO_LVL_LOW,   .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=0, .pin=3}, .testable=true, .name="LedVirt", .dir=GPIO_DIR_INOUT, .logic_level=GPIO_LVL_LOW,   .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=0, .pin=31}, .testable=true, .name="Led4Green", .dir=GPIO_DIR_INOUT, .logic_level=GPIO_LVL_LOW,  .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=0, .pin=28}, .testable=true, .name="Led1Green", .dir=GPIO_DIR_INOUT, .logic_level=GPIO_LVL_LOW,   .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=0, .pin=29}, .testable=true, .name="Led2Green", .dir=GPIO_DIR_INOUT, .logic_level=GPIO_LVL_LOW,   .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=0, .pin=30}, .testable=true, .name="Led3Green", .dir=GPIO_DIR_INOUT, .logic_level=GPIO_LVL_UNDEF,   .mcu_sel=GPIO_CORE_MUX_APP,},
#endif /*HAS_CORE_APP*/

#ifdef HAS_CORE_NET
    {.pad={.port=0, .pin=30}, .testable=true, .name="Led3Green", .dir=GPIO_DIR_OUT, .logic_level=GPIO_LVL_HI,  .mcu_sel=NRF_GPIO_PIN_MUX_NET,},
    {.pad={.port=0, .pin=31}, .testable=true, .name="Led4Green", .dir=GPIO_DIR_OUT, .logic_level=GPIO_LVL_HI,  .mcu_sel=NRF_GPIO_PIN_MUX_NET,},
#endif /*HAS_CORE_NET*/
#endif/*HAS_LED*/

#ifdef HAS_UART2
    {.pad={.port=1, .pin=1}, .testable=false, .name="USART2_TX", .dir=GPIO_DIR_OUT, .pull=GPIO__PULL_AIR, .mcu_sel=GPIO_CORE_MUX_APP,       },
    {.pad={.port=1, .pin=0}, .testable=false, .name="USART2_RX", .dir=GPIO_DIR_IN, .pull=GPIO__PULL_UP, .mcu_sel=GPIO_CORE_MUX_APP,       },
#endif /*HAS_UART2*/

#ifdef HAS_LOG
    {.pad={.port=0, .pin=20}, .testable=false, .name="USART0_TX", .dir=GPIO_DIR_OUT, .mcu_sel=GPIO_CORE_MUX_APP,     },
#ifdef HAS_CLI
    {.pad={.port=0, .pin=22}, .testable=false, .name="USART0_RX", .dir=GPIO_DIR_IN, .pull=GPIO__PULL_UP, .mcu_sel=GPIO_CORE_MUX_APP,     },
#endif /*HAS_CLI*/
#endif /*HAS_LOG*/

#ifdef HAS_PWM
    {.pad={.port=1, .pin=6}, .testable=false, .name="PWM", .mode=GPIO_MODE_HW_PWM, .dir=GPIO_DIR_INOUT, .logic_level=GPIO_LVL_LOW,  .mcu_sel=GPIO_CORE_MUX_APP,},
#endif /*HAS_PWM*/

#ifdef HAS_BT1026
    {.pad={.port=0, .pin=27}, .testable=true, .name="Bt1026Rst", .dir=GPIO_DIR_INOUT, .logic_level=GPIO_LVL_HI, .mcu_sel=GPIO_CORE_MUX_APP,},
    //{.pad={.port=1, .pin=11}, .testable=true, .name="Bt1026Enable", .dir=GPIO_DIR_INOUT, .logic_level=GPIO_LVL_HI, .mcu_sel=GPIO_CORE_MUX_APP,},
#endif /*HAS_BT1026*/

#ifdef HAS_BUTTON
    {.pad={.port=0, .pin=23}, .testable=true, .name="Button1", .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_UP,  .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=0, .pin=24}, .testable=true, .name="Button2", .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_UP,  .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=0, .pin=8}, .testable=true, .name="Button3", .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_UP,  .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=0, .pin=9}, .testable=true, .name="Button4", .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_UP,  .mcu_sel=GPIO_CORE_MUX_APP,},
#endif/*HAS_BUTTON*/

#ifdef HAS_I2C1
    {.pad={.port=1, .pin=3}, .testable=false, .name="I2C1_SCL", .dir=GPIO_DIR_OUT, .mcu_sel=GPIO_CORE_MUX_APP, .pull=GPIO__PULL_UP,},
    {.pad={.port=1, .pin=2}, .testable=false, .name="I2C1_SDA", .dir=GPIO_DIR_INOUT_OD, .mcu_sel=GPIO_CORE_MUX_APP, .pull=GPIO__PULL_UP,},
#endif /*HAS_I2C1*/

#ifdef HAS_I2C2
    {.pad={.port=0, .pin=5}, .testable=false, .name="I2C2_SCL", .dir=GPIO_DIR_OUT, .mcu_sel=GPIO_CORE_MUX_APP, .pull=GPIO__PULL_UP,  .logic_level=GPIO_LVL_LOW,},
    {.pad={.port=0, .pin=4}, .testable=false, .name="I2C2_SDA", .dir=GPIO_DIR_INOUT_OD, .mcu_sel=GPIO_CORE_MUX_APP, .pull=GPIO__PULL_UP,  .logic_level=GPIO_LVL_LOW,},
#endif /*HAS_I2C2*/

#ifdef HAS_I2S
    {.pad={.port=0, .pin=6}, .testable=false, .name="I2S_SCK", .dir=GPIO_DIR_INOUT,  .pull=GPIO__PULL_DOWN, .mcu_sel=GPIO_CORE_MUX_APP,  .logic_level=GPIO_LVL_LOW,},
    {.pad={.port=0, .pin=7}, .testable=false, .name="I2S_LRCK", .dir=GPIO_DIR_INOUT, .pull=GPIO__PULL_DOWN, .mcu_sel=GPIO_CORE_MUX_APP,  .logic_level=GPIO_LVL_LOW,},
    {.pad={.port=0, .pin=25}, .testable=false, .name="I2S_SDOUT", .dir=GPIO_DIR_OUT, .pull=GPIO__PULL_DOWN, .mcu_sel=GPIO_CORE_MUX_APP,  .logic_level=GPIO_LVL_LOW,},
    {.pad={.port=1, .pin=4}, .testable=false, .name="I2S_SDIN", .dir=GPIO_DIR_IN, .pull=GPIO__PULL_DOWN,  .mcu_sel=GPIO_CORE_MUX_APP,  .logic_level=GPIO_LVL_LOW,},
  //  {.pad={.port=1, .pin=5}, .testable=false, .name="I2S_MCLK", .dir=GPIO_DIR_OUT, .mcu_sel=GPIO_CORE_MUX_APP,},
#endif /*HAS_I2S*/

#ifdef HAS_FDA801
    //{.pad={.port=1, .pin=4}, .testable=false, .name="CD/DIAG", .connector1="P3.3_D2", .connector2="J10.19", .dir=GPIO_DIR_UNDEF, .logic_level=GPIO_LVL_UNDEF, .mcu_sel=GPIO_CORE_MUX_UNDEF,},
    {.pad={.port=0, .pin=10}, .testable=true, .name="MUTE", .dir=GPIO_DIR_INOUT, .logic_level=GPIO_LVL_HI, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=0, .pin=4}, .testable=true, .name="EN1", .dir=GPIO_DIR_INOUT, .logic_level=GPIO_LVL_LOW, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=0, .pin=5}, .testable=true, .name="EN2", .dir=GPIO_DIR_INOUT, .logic_level=GPIO_LVL_HI, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=0, .pin=26}, .testable=true, .name="EN3", .dir=GPIO_DIR_INOUT, .logic_level=GPIO_LVL_LOW, .mcu_sel=GPIO_CORE_MUX_APP,},
#endif /*HAS_FDA801*/

#ifdef HAS_DWM1000
    {.pad={.port=1, .pin=9}, .testable=false, .name="DWM1000_RST", .dir=GPIO_DIR_IN, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_HI, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=1, .pin=10}, .testable=false, .name="DWM1000_IRQ", .dir=GPIO_DIR_IN, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_LOW, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=1, .pin=11}, .testable=true, .name="DWM1000_WKP", .dir=GPIO_DIR_INOUT, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_HI, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=1, .pin=12}, .testable=true, .name="DWM1000_CS", .dir=GPIO_DIR_INOUT, .pull=GPIO__PULL_UP, .logic_level=GPIO_LVL_HI, .mcu_sel=GPIO_CORE_MUX_APP,},
#endif /*HAS_DWM1000*/

#ifdef HAS_DWM3000
    {.pad={.port=1, .pin=9}, .testable=false, .name="DWM3000_RST", .dir=GPIO_DIR_IN, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_HI, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=1, .pin=10}, .testable=false, .name="DWM3000_IRQ", .dir=GPIO_DIR_IN, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_LOW, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=1, .pin=11}, .testable=true, .name="DWM3000_WKP", .dir=GPIO_DIR_OUT, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_HI, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=1, .pin=12}, .testable=true, .name="DWM3000_CS", .dir=GPIO_DIR_OUT, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_HI, .mcu_sel=GPIO_CORE_MUX_APP,},
#endif /*HAS_DWM3000*/

#ifdef HAS_DWS3000
    {.pad={.port=1, .pin=1}, .testable=true, .name="GPIO5", .dir=GPIO_DIR_OUT, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_HI, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=1, .pin=0}, .testable=true, .name="GPIO6", .dir=GPIO_DIR_OUT, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_HI, .mcu_sel=GPIO_CORE_MUX_APP,},
#endif /*HAS_DWS3000*/

#ifdef HAS_PDM
    {.pad={.port=1, .pin=10}, .testable=false, .name="PDM_CLK", .dir=GPIO_DIR_OUT, .logic_level=GPIO_LVL_LOW,  .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=1, .pin=11}, .testable=false, .name="PDM_DIN", .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_LOW,  .mcu_sel=GPIO_CORE_MUX_APP,},
#endif /*HAS_PDM*/

#ifdef HAS_SD_CARD
    {.pad={.port = 0, .pin = 26}, .testable=true, .name="SD_CARD_CS", .dir=GPIO_DIR_OUT, .pull=GPIO__PULL_UP, .logic_level=GPIO_LVL_HI, .mcu_sel=GPIO_CORE_MUX_APP,},
#endif /*HAS_SD_CARD*/

#ifdef HAS_SPI2
    {.pad={.port=0, .pin=17}, .testable=false, .name="SPI2_SCK", .pull=GPIO__PULL_AIR, .dir=GPIO_DIR_OUT, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=0, .pin=13}, .testable=false, .name="SPI2_SI", .pull=GPIO__PULL_UP, .dir=GPIO_DIR_INOUT, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=0, .pin=14}, .testable=false, .name="SPI2_SO", .pull=GPIO__PULL_UP, .dir=GPIO_DIR_INOUT, .mcu_sel=GPIO_CORE_MUX_APP,},
#endif /*HAS_SPI2*/

#ifdef HAS_SPI3
    {.pad={.port=1, .pin=13}, .testable=false, .name="SPI4_MOSI", .pull = GPIO__PULL_UP, .dir=GPIO_DIR_OUT, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=1, .pin=14}, .testable=false, .name="SPI4_MISO", .pull = GPIO__PULL_UP, .dir=GPIO_DIR_IN, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=1, .pin=15}, .testable=false, .name="SPI4_CLK", .pull = GPIO__PULL_AIR, .dir=GPIO_DIR_OUT, .mcu_sel=GPIO_CORE_MUX_APP,},
#endif /*HAS_SPI3*/

#ifdef HAS_SPI4
    {.pad={.port=1, .pin=5}, .testable=false, .name="SPI4_MOSI", .pull = GPIO__PULL_UP, .dir=GPIO_DIR_OUT, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=1, .pin=6}, .testable=false, .name="SPI4_MISO", .pull = GPIO__PULL_UP, .dir=GPIO_DIR_IN, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=0, .pin=27}, .testable=false, .name="SPI4_CLK", .pull = GPIO__PULL_AIR, .dir=GPIO_DIR_OUT, .mcu_sel=GPIO_CORE_MUX_APP,},
#endif /*HAS_SPI4*/

#ifdef HAS_MX25R6435F
    {.pad={.port=0, .pin=18}, .testable=true, .name="MX25_CS",  .pull=GPIO__PULL_AIR, .dir=GPIO_DIR_OUT,   .logic_level=GPIO_LVL_HI, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=0, .pin=15}, .testable=true, .name="MX25_WP",  .pull=GPIO__PULL_AIR, .dir=GPIO_DIR_INOUT, .logic_level=GPIO_LVL_HI, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad={.port=0, .pin=16}, .testable=true, .name="MX25_Rst", .pull=GPIO__PULL_AIR, .dir=GPIO_DIR_INOUT, .logic_level=GPIO_LVL_HI, .mcu_sel=GPIO_CORE_MUX_APP,},
#endif /*HAS_MX25R6435F*/

#ifdef HAS_AD9833
    {.pad={.port=1, .pin=8}, .testable=true, .name="AD9833_CS",  .pull=GPIO__PULL_AIR, .dir=GPIO_DIR_OUT,   .logic_level=GPIO_LVL_HI, .mcu_sel=GPIO_CORE_MUX_APP,},
#endif /*HAS_AD9833*/
};

uint32_t gpio_get_cnt(void) {
    return ARRAY_SIZE(GpioConfig);
}

