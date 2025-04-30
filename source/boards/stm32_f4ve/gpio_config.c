#include "gpio_config.h"

#include "data_utils.h"
#include "gpio_mcal.h"
#include "sys_config.h"

const GpioConfig_t GpioConfig[] = {
#ifdef HAS_I2C1
    {.pad={.port=PORT_B, .pin=6}, .name="I2C1_SCL", .mode=GPIO_API_MODE_I2C, .pull=GPIO__PULL_UP, .mux=GPIO_AF4_I2C1, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_B, .pin=7}, .name="I2C1_SDA", .mode=GPIO_API_MODE_I2C, .pull=GPIO__PULL_UP, .mux=GPIO_AF4_I2C1, .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_LED
    {.pad={.port=PORT_A, .pin=6}, .name="Led/D2", .connector1="-", .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .mux=0, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_A, .pin=7}, .name="Led/D3", .connector1="-", .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .mux=0, .logic_level=GPIO_LVL_HI},
#endif/*HAS_LED*/

#ifdef HAS_BUTTON
    {.pad={.port=PORT_A, .pin=0}, .name="WK_UP", .connector1="PA.0", .connector2="pin34", .mode=GPIO_API_MODE_INPUT_EXINT_FAILLING, .pull=GPIO__PULL_UP, .mux=0, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_E, .pin=4}, .name="K0", .connector1="PE.4", .connector2="pin34", .mode=GPIO_API_MODE_INPUT_EXINT_FAILLING, .pull=GPIO__PULL_UP, .mux=0, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_E, .pin=3}, .name="K1", .connector1="PE.3", .connector2="pin34", .mode=GPIO_API_MODE_INPUT_EXINT_FAILLING, .pull=GPIO__PULL_UP, .mux=0, .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_LTR390
    {.pad={.port=PORT_B, .pin=1}, .name="INT", .mode=GPIO_API_MODE_INPUT_EXINT_FAILLING, .pull=GPIO__PULL_UP, .mux=0, .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_UART1
    {.pad={.port=PORT_A, .pin=9},  .name="UART1_TX", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .mux=GPIO_AF7_USART1, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_A, .pin=10}, .name="UART1_RX", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP,  .mux=GPIO_AF7_USART1, .logic_level=GPIO_LVL_HI},
#endif /*HAS_UART1*/

#ifdef HAS_SI4703
    {.pad={.port=PORT_C, .pin=3}, .name="SI4703_RST", .connector1="UEXT.8", .connector2="JP1.3", .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .mux=0, .logic_level=GPIO_LVL_LOW},
    {.pad={.port=PORT_C, .pin=2}, .name="SI4703_SEN", .connector1="UEXT.7", .connector2="JP1.4", .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .mux=0, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_D, .pin=0}, .name="SI4703_GPIO1", .connector1="PD.3", .connector2="JP1.2", .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .mux=0, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_D, .pin=1}, .name="SI4703_GPIO2", .connector1="PD.4", .connector2="JP1.1", .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .mux=0, .logic_level=GPIO_LVL_HI},
#endif /*HAS_SI4703*/

#ifdef HAS_SPI
    {.pad={.port=PORT_B, .pin=3}, .name="SPI_CLK", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .mux=GPIO_AF4_I2C1, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_B, .pin=4}, .name="SPI_MOSI", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .mux=GPIO_AF4_I2C1, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_B, .pin=5}, .name="SPI_MISO", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .mux=GPIO_AF4_I2C1, .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_I2C2
    {.pad={.port=PORT_B, .pin=10}, .name="I2C2_SCL", .mode=GPIO_API_MODE_I2C, .pull=GPIO__PULL_UP, .mux=GPIO_AF4_I2C2, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_B, .pin=11}, .name="I2C2_SDA", .mode=GPIO_API_MODE_I2C, .pull=GPIO__PULL_UP, .mux=GPIO_AF4_I2C2, .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_I2C3
    //{.pad={.port=PORT_X, .pin=x}, .name="I2C3_SCL", .connector1="Host", .connector2="", .mode=GPIO_API_MODE_I2C, .pull=GPIO__PULL_UP, .mux=xxxxxxx, .logic_level=xxxxxx},
    //{.pad={.port=PORT_X, .pin=x}, .name="I2C3_SDA", .connector1="Host", .connector2="", .mode=GPIO_API_MODE_I2C, .pull=GPIO__PULL_UP, .mux=xxxxxxx, .logic_level=xxxxxx},
#endif

#ifdef HAS_USB_DEVICE
    {.pad={.port=PORT_B, .pin=15}, .name="OTG_HS_DP", .connector1="USB_OTG.D+", .connector2="", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .mux=GPIO_AF12_OTG_HS_FS, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_B, .pin=14}, .name="OTG_HS_DM", .connector1="USB_OTG.D-", .connector2="", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .mux=GPIO_AF12_OTG_HS_FS, .logic_level=GPIO_LVL_HI},
#endif /*HAS_USB_DEVICE*/

#ifdef HAS_USB_HOST
    {.pad={.port=PORT_A, .pin=9}, .name="OTG_FS_VBUS", .connector1="PA9", .connector2="USB_HOST.1", .mode=GPIO_MODE_INPUT, .pull=GPIO__PULL_AIR, .mux=0, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_A, .pin=11}, .name="OTG_FS_DM", .connector1="D-", .connector2="USB_HOST.2", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .mux=GPIO_AF10_OTG_FS, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_A, .pin=12}, .name="OTG_FS_DP", .connector1="D+", .connector2="USB_HOST.3", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .mux=GPIO_AF10_OTG_FS, .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_SDIO
    {.pad={.port=PORT_C, .pin=10}, .name="SD_D2", .connector1="SD.1", .connector2="", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_C, .pin=11}, .name="SD_D3", .connector1="SD.2", .connector2="", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_D, .pin=2}, .name="SD_CMD", .connector1="SD.3", .connector2="PD.5", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_C, .pin=12}, .name="SD_CLK", .connector1="SD.5", .connector2="", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_C, .pin=8}, .name="SD_D0", .connector1="SD.7", .connector2="", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_C, .pin=9}, .name="SD_D1", .connector1="SD.8", .connector2="", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .mux=GPIO_AF12_SDIO, .logic_level=GPIO_LVL_HI},
#endif /*HAS_SDIO*/

#ifdef HAS_UART6
    {.pad={.port=PORT_C, .pin=6}, .name="USART6_TX", .connector1="UEXT.3",.mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .mux=GPIO_AF8_USART6, .logic_level=GPIO_LVL_HI},
    {.pad={.port=PORT_C, .pin=7}, .name="USART6_RX", .connector1="UEXT.4",.mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .mux=GPIO_AF8_USART6, .logic_level=GPIO_LVL_HI},
#endif /*HAS_LOG*/
};

uint32_t gpio_get_cnt(void) {
    return ARRAY_SIZE(GpioConfig);
}
