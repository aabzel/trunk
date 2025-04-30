#include "gpio_config.h"

#include "data_utils.h"
#include "gpio_mcal.h"
#include "gpio_types.h"
//#include "c_defines_generated.h" //Just for macro highlight

GpioConfig_t GpioConfig[] = {
    {.pad.port=1, .pad.pin=14, .testable=false, .name="Spare", .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_LOW, .mcu_sel=GPIO_CORE_MUX_APP,},
#ifdef HAS_DWS3000
    {.pad.port=1, .pad.pin=10, .testable=false, .name="IRQ", .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_LOW, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad.port=1, .pad.pin=13, .testable=true, .name="WakeUp", .dir=GPIO_DIR_INOUT, .logic_level=GPIO_LVL_HI, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad.port=1, .pad.pin=11, .testable=true, .name="Dwm3000Rst", .dir=GPIO_DIR_INOUT, .logic_level=GPIO_LVL_HI, .mcu_sel=GPIO_CORE_MUX_APP,},

    {.pad.port=1, .pad.pin=8, .testable=true, .name="GPIO5", .dir=GPIO_DIR_INOUT, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_LOW, .mcu_sel=GPIO_CORE_MUX_APP,       },
    {.pad.port=1, .pad.pin=9, .testable=true, .name="GPIO6", .dir=GPIO_DIR_INOUT, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_LOW, .mcu_sel=GPIO_CORE_MUX_APP,       },

#endif /*HAS_DWS3000*/

#ifdef HAS_LED
#ifdef HAS_CORE_APP
    {.pad.port=0, .pad.pin=31, .testable=true, .name="LED1", .dir=GPIO_DIR_INOUT, .logic_level=GPIO_LVL_LOW, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad.port=1, .pad.pin=0, .testable=false, .name="LED2", .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_LOW, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad.port=1, .pad.pin=1, .testable=false, .name="LED3", .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_LOW, .mcu_sel=GPIO_CORE_MUX_APP,},

    {.pad.port=0, .pad.pin=7, .testable=true, .name="RGB1_Red", .dir=GPIO_DIR_INOUT, .logic_level=GPIO_LVL_LOW, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad.port=0, .pad.pin=25, .testable=true, .name="RGB1_Green", .dir=GPIO_DIR_INOUT, .logic_level=GPIO_LVL_LOW, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad.port=0, .pad.pin=26, .testable=true, .name="RGB1_Blue", .dir=GPIO_DIR_INOUT, .logic_level=GPIO_LVL_LOW, .mcu_sel=GPIO_CORE_MUX_APP,},

    {.pad.port=0, .pad.pin=28, .testable=true, .name="RGB2_Red", .dir=GPIO_DIR_INOUT, .logic_level=GPIO_LVL_LOW, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad.port=0, .pad.pin=29, .testable=true, .name="RGB2_Green", .dir=GPIO_DIR_INOUT, .logic_level=GPIO_LVL_LOW, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad.port=0, .pad.pin=30, .testable=true, .name="RGB2_Blue", .dir=GPIO_DIR_INOUT, .logic_level=GPIO_LVL_LOW, .mcu_sel=GPIO_CORE_MUX_APP,},
#endif /*HAS_CORE_APP*/

#ifdef HAS_CORE_NET
    {.pad.port=0, .pad.pin=30, .testable=true, .name="LED3Green", .dir=GPIO_DIR_OUT, .logic_level=GPIO_LVL_HI, .mcu_sel=NRF_GPIO_PIN_MUX_NET,},
    {.pad.port=0, .pad.pin=31, .testable=true, .name="LED4Green", .dir=GPIO_DIR_OUT, .logic_level=GPIO_LVL_HI, .mcu_sel=NRF_GPIO_PIN_MUX_NET,},
#endif /*HAS_CORE_NET*/
#endif /*HAS_LED*/

#ifdef HAS_LOG
    {.pad.port=1, .pad.pin=5, .testable=false, .name="USART0_TX", .dir=GPIO_DIR_OUT, .mcu_sel=GPIO_CORE_MUX_APP,     },
#ifdef HAS_CLI
    {.pad.port=1, .pad.pin=4, .testable=false, .name="USART0_RX", .dir=GPIO_DIR_IN, .pull=GPIO__PULL_UP, .mcu_sel=GPIO_CORE_MUX_APP,     },
#endif /*HAS_CLI*/
#endif /*HAS_LOG*/

#ifdef HAS_I2S
    {.pad.port=0, .pad.pin=14, .testable=false, .name="Sck", .dir=GPIO_DIR_INOUT, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad.port=0, .pad.pin=16, .testable=false, .name="LrCk", .dir=GPIO_DIR_INOUT, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad.port=0, .pad.pin=15, .testable=false, .name="SdOut", .dir=GPIO_DIR_OUT, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad.port=0, .pad.pin=13, .testable=false, .name="SdIn", .dir=GPIO_DIR_IN, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad.port=0, .pad.pin=12, .testable=false, .name="MClk", .dir=GPIO_DIR_OUT, .mcu_sel=GPIO_CORE_MUX_APP,},
#endif /*HAS_I2S*/

#ifdef HAS_I2C
    {.pad.port=1, .pad.pin=3, .testable=false, .name="SCL", .dir=GPIO_DIR_OUT, .mcu_sel=GPIO_CORE_MUX_APP, .pull=GPIO__PULL_UP,},
    {.pad.port=1, .pad.pin=2, .testable=false, .name="SDA", .dir=GPIO_DIR_INOUT_OD, .mcu_sel=GPIO_CORE_MUX_APP, .pull=GPIO__PULL_UP,},
#endif /*HAS_I2C*/

#ifdef HAS_BUTTON
    {.pad.port=0, .pad.pin=2, .testable=false, .name="Button1", .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_UP, .connector1="SW1", .connector2="D34",.mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad.port=0, .pad.pin=3, .testable=false, .name="Button2", .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_UP, .connector1="SW2", .connector2="D35",.mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad.port=0, .pad.pin=4, .testable=false, .name="Button3", .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_UP, .connector1="SW3", .connector2="D19",.mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad.port=0, .pad.pin=6, .testable=false, .name="Button4", .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_UP, .connector1="SW4", .connector2="D20",.mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad.port=0, .pad.pin=5, .testable=false, .name="Button5", .dir=GPIO_DIR_IN, .logic_level=GPIO_LVL_UNDEF, .pull=GPIO__PULL_UP, .connector1="SW5", .connector2="D20",.mcu_sel=GPIO_CORE_MUX_APP,},
#endif /*HAS_BUTTON*/

#ifdef HAS_SPI4
    {.pad = {.port=0, .pin=8}, .testable=false, .name="SPI4_SCK", .pull=GPIO__PULL_AIR, .dir=GPIO_DIR_OUT, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad = {.port=0, .pin=10}, .testable=false, .name="SPI4_MISO", .pull=GPIO__PULL_AIR, .dir=GPIO_DIR_IN, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad = {.port=0, .pin=9}, .testable=false, .name="SPI4_MOSI", .pull=GPIO__PULL_AIR, .dir=GPIO_DIR_OUT, .mcu_sel=GPIO_CORE_MUX_APP,},
#endif /*HAS_SPI4*/

#ifdef HAS_SD_CARD
    {.pad = {.port = 0, .pin = 11,}, .testable = true, .name="CsSdCard", .logic_level=GPIO_LVL_HI, .pull = GPIO__PULL_AIR, .dir = GPIO_DIR_INOUT, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad = {.port = 0, .pin = 17,}, .testable = true, .name="CsCodec", .logic_level=GPIO_LVL_HI, .pull = GPIO__PULL_AIR, .dir = GPIO_DIR_INOUT, .mcu_sel=GPIO_CORE_MUX_APP,},
    {.pad = {.port = 0, .pin = 22,}, .testable = true, .name="SPI_SELECT", .logic_level=GPIO_LVL_HI, .pull = GPIO__PULL_AIR, .dir = GPIO_DIR_INOUT, .mcu_sel=GPIO_CORE_MUX_APP,},
#endif /*HAS_SD_CARD*/

};

uint32_t gpio_get_cnt(void) {
    return ARRAY_SIZE(GpioConfig);
}

