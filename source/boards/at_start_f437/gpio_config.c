#include "gpio_config.h"

#include "data_utils.h"
#include "gpio_mcal.h"
#include "gpio_types.h"
#include "sys_config.h"
#include "gpio_custom_const.h"

//#include "c_defines_generated.h"

const GpioConfig_t GpioConfig[] = {

    {.pad = {.port=PORT_B, .pin=6}, .dir=GPIO_DIR_OUT, .name="DebugDmaTx", .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_LOW},
    {.pad = {.port=PORT_B, .pin=7}, .dir=GPIO_DIR_OUT, .name="DebugDmaRx", .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_LOW},
    {.pad = {.port=PORT_B, .pin=8}, .dir=GPIO_DIR_OUT, .name="DebugTimer8", .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_LOW},
    {.pad = {.port=PORT_B, .pin=11}, .dir=GPIO_DIR_OUT, .name="DebugProc", .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_LOW},

    {.pad = {.port=PORT_B, .pin=5}, .dir=GPIO_DIR_IN, .mux=2, .mode=GPIO_API_MODE_ALT1, .name="SPK_INT", .function="TMR3_CH2", .connector2="TP342", .pull=GPIO__PULL_DOWN, .logic_level=GPIO_LVL_HI},
#ifdef HAS_I2C2
    {.pad = {.port=PORT_F, .pin=0}, .name="I2C2_SDA", .mux=4, .dir=GPIO_DIR_INOUT_OPEN_DRAIN, .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_F, .pin=1}, .name="I2C2_SCL", .mux=4, .dir=GPIO_DIR_OUT_OPEN_DRAIN, .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_I2S2
    {.pad = {.port=PORT_C, .pin=7}, .connector2="J1.25", .mux=5, .dir=GPIO_DIR_OUT,.name="I2S2_CK", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_DOWN, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_B, .pin=9}, .connector2="J1.68", .mux=5, .dir=GPIO_DIR_OUT, .name="I2S2_WS", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_C, .pin=3}, .connector2="J2.29", .mux=5, .dir=GPIO_DIR_OUT, .name="I2S2_SD", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_C, .pin=2}, .connector2="J2.28", .mux=6, .dir=GPIO_DIR_IN, .name="I2S2_SDEXT", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .logic_level=GPIO_LVL_HI},
   // {.pad = {.port=PORT_C, .pin=2}, .connector2="J2.28", .mux=6, .dir=GPIO_DIR_IN, .name="I2S2_SDEXT", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_DOWN, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_A, .pin=3}, .connector2="J2.37", .mux=5, .dir=GPIO_DIR_OUT, .name="I2S2_MCK", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_LOW},

//    { .pad = {.port=PORT_B, .pin=0,}, .name="SOUND_DEBUG1", .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .mux=0, .logic_level=GPIO_LVL_LOW},
    { .pad = {.port=PORT_B, .pin=1,}, .name="SOUND_DEBUG2", .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .mux=0, .logic_level=GPIO_LVL_LOW},
#endif /*HAS_I2S2*/

#ifdef HAS_I2S3
    {.pad = {.port=PORT_C, .pin=10}, .connector2="PC10,J1.39", .mux=6, .dir=GPIO_DIR_OUT,.name="I2S3_CK", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_DOWN, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_B, .pin=0}, .connector2="PB0,J2.46", .mux=7, .dir=GPIO_DIR_OUT, .name="I2S3_SD", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_C, .pin=11}, .connector2="PC11,J1.40", .mux=5, .dir=GPIO_DIR_OUT, .name="I2S3_SDEXT", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_A, .pin=4}, .connector2="PA4,J2.40", .mux=6, .dir=GPIO_DIR_OUT, .name="I2S3_WS", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .logic_level=GPIO_LVL_HI},
#endif /*HAS_I2S3*/

    {.pad = {.port=PORT_A, .pin=8,}, .dir=GPIO_DIR_OUT, .function="TMR1_CH1", .name="MCLK", .mux=1, .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_HI},
    //{.pad = {.port=PORT_E, .pin=11}, .dir=GPIO_DIR_OUT, .function="TMR1_CH2", .name="J2.64", .mux=1, .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_HI},

#ifdef HAS_DAC
    {.pad = {.port=PORT_A, .pin=4}, .mux=0, .dir=GPIO_DIR_OUT_PUSH_PULL, .name="DAC1_OUT", .mode=GPIO_API_MODE_ANALOG, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_A, .pin=5}, .mux=0, .dir=GPIO_DIR_OUT_PUSH_PULL, .name="DAC2_OUT", .mode=GPIO_API_MODE_ANALOG, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_HI},
#endif

    {.pad = {.port=PORT_C, .pin=0,}, .dir=GPIO_DIR_OUT, .name="DEBUG", .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_LOW},
    {.pad = {.port=PORT_C, .pin=4,}, .dir=GPIO_DIR_OUT, .name="DEBUG", .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_LOW},
#ifdef HAS_LED
    {.pad = {.port=PORT_D, .pin=13,}, .dir=GPIO_DIR_OUT, .name="LED_Red", .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_LOW},
    {.pad = {.port=PORT_D, .pin=14,}, .dir=GPIO_DIR_OUT, .name="LED_Yellow", .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_LOW},
    {.pad = {.port=PORT_D, .pin=15,}, .dir=GPIO_DIR_OUT, .name="LED_Green", .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_LOW},
#endif /*HAS_LED*/


#ifdef HAS_PWM
    {.pad = {.port=PORT_F, .pin=12}, .mux=2, .dir=GPIO_DIR_OUT, .function="TMR20_CH1", .name="DIGIT_EXT1", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_F, .pin=13}, .mux=2, .dir=GPIO_DIR_OUT, .function="TMR20_CH2", .name="DIGIT_EXT2", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_F, .pin=14}, .mux=2, .dir=GPIO_DIR_OUT, .function="TMR20_CH3", .name="PWM_ADC1", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_F, .pin=15}, .mux=2, .dir=GPIO_DIR_OUT, .function="TMR20_CH4", .name="PWM_ADC2", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_E, .pin=5}, .mux=2, .dir=GPIO_DIR_OUT, .function="TMR3_CH3", .name="ENS", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_LOW},
#endif

#ifdef HAS_SPI1
    {.pad = {.port=PORT_A, .pin=6}, .mux=5, .dir=GPIO_DIR_IN, .name="SPI1_MISO", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_A, .pin=7}, .mux=5, .dir=GPIO_DIR_OUT, .name="SPI1_MOSI", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_A, .pin=5}, .mux=5, .dir=GPIO_DIR_OUT,.name="SPI1_SCK", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_HI},
#endif /*HAS_SPI1*/

#ifdef HAS_SPI4
//    {.pad = {.port=PORT_E, .pin=11},.mux=0, .dir=GPIO_DIR_OUT,.dir=GPIO_DIR_OUT, .name="SPI4_CS", .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_LOW},
    {.pad = {.port=PORT_E, .pin=2}, .mux=5, .dir=GPIO_DIR_OUT, .name="SPI4_SCK", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_DOWN, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_D, .pin=0}, .mux=5, .dir=GPIO_DIR_IN, .name="SPI4_MISO", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_E, .pin=6}, .mux=5, .dir=GPIO_DIR_OUT, .name="SPI4_MOSI", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .logic_level=GPIO_LVL_HI},
#endif /*HAS_SPI4*/

#ifdef HAS_LIS3DH
    {.pad = {.port=PORT_G, .pin=14,}, .dir=GPIO_DIR_OUT, .name="LIS3DH_CS", .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_UP, .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_W25M02GV
    {.pad = {.port=PORT_G, .pin=8,}, .dir=GPIO_DIR_OUT, .name="W25M02GV_HOLD", .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_UP, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_G, .pin=10,}, .dir=GPIO_DIR_OUT, .name="W25M02GV_WP", .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_UP, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_G, .pin=14,}, .dir=GPIO_DIR_OUT, .name="W25M02GV_CS", .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_UP, .logic_level=GPIO_LVL_HI},
#endif

    //{.pad = {.port=PORT_A, .pin=8}, .dir=GPIO_DIR_OUT, .function="TMR1_CH1", .name="MCLK", .mux=1, .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_HI},

#ifdef HAS_BUTTON
    {.pad = {.port=PORT_A, .pin=0}, .dir=GPIO_DIR_IN,.name="Button", .connector1="R19", .mode=GPIO_API_MODE_INPUT_EXINT, /*.int_edge = PIN_INT_EDGE_RISING,*/ .pull=GPIO__PULL_DOWN, .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_UART1
    {.pad = {.port=PORT_A, .pin=9}, .dir=GPIO_DIR_OUT,.name="USART1_TX", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .mux=7, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_A, .pin=10}, .dir=GPIO_DIR_IN, .name="USART1_RX", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .mux=7, .logic_level=GPIO_LVL_HI},
#endif /*HAS_UART1*/

#ifdef HAS_UART2
    {.pad = {.port=PORT_D, .pin=5}, .dir=GPIO_DIR_OUT,.name="USART2_TX", .mux=7, .connector1="J1.47", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_A, .pin=15}, .dir=GPIO_DIR_IN, .name="USART2_RX", .mux=8, .connector1="J1.38", .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .logic_level=GPIO_LVL_HI},
#endif /*HAS_UART2*/

#ifdef HAS_UART6
    {.pad = {.port=PORT_C, .pin=6}, .dir=GPIO_DIR_OUT,.name="USART6_TX", .mux=8, .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .logic_level=GPIO_LVL_HI},
    {.pad = {.port=PORT_C, .pin=7}, .dir=GPIO_DIR_IN, .name="USART6_RX", .mux=8, .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .logic_level=GPIO_LVL_HI},
#endif /*HAS_USART6*/


#if 0

#ifdef HAS_USB_DEVICE
    {.pad.port=PORT_B, .pad.pin=15, .mode=GPIO_API_MODE_ALT1,.name="OTG_HS_DP", .connector1="USB_OTG.D+", .connector2="", .mode=GPIO_MODE_AF_PP, .pull=GPIO__PULL_AIR, .mux=GPIO_AF12_OTG_HS_FS, .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_B, .pad.pin=14,.mode=GPIO_API_MODE_ALT1, .name="OTG_HS_DM", .connector1="USB_OTG.D-", .connector2="", .mode=GPIO_MODE_AF_PP, .pull=GPIO__PULL_AIR, .mux=GPIO_AF12_OTG_HS_FS, .logic_level=GPIO_LVL_HI},
#endif /*HAS_USB_DEVICE*/

#ifdef HAS_USB_HOST
    {.pad.port=PORT_A, .pad.pin=9, .name="OTG_FS_VBUS", .connector1="PA9", .connector2="USB_HOST.1", .mode=GPIO_MODE_INPUT, .pull=GPIO__PULL_AIR, .speed=GPIO_SPEED_FREQ_LOW, .mux=0, .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_A, .pad.pin=11, .mode=GPIO_API_MODE_ALT1,.name="OTG_FS_DM", .connector1="D-", .connector2="USB_HOST.2", .mode=GPIO_MODE_AF_PP, .pull=GPIO__PULL_AIR, .mux=GPIO_AF10_OTG_FS, .logic_level=GPIO_LVL_HI},
    {.pad.port=PORT_A, .pad.pin=12, .mode=GPIO_API_MODE_ALT1,.name="OTG_FS_DP", .connector1="D+", .connector2="USB_HOST.3", .mode=GPIO_MODE_AF_PP, .pull=GPIO__PULL_AIR, .mux=GPIO_AF10_OTG_FS, .logic_level=GPIO_LVL_HI},
#endif

#endif
};

uint32_t gpio_get_cnt(void) {
    return ARRAY_SIZE(GpioConfig);
}
