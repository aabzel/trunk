#include "gpio_config.h"

#include <stdlib.h>

#include "data_utils.h"
#include "gpio_mcal.h"
#include "sys_config.h"
#include "ioc.h"

const GpioConfig_t GpioConfig[] = {
#ifdef HAS_LED
    {.pad={.port=0, .pin=7}, .config_number=0, .name="LedGreem",     .pull=GPIO__PULL_AIR,     .logic_level=GPIO_LVL_HI, .pinConfig=DIO_LED_GREEN | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_HIGH,},
    {.pad={.port=0, .pin=6}, .config_number=1, .name="LedRed",       .pull=GPIO__PULL_AIR,     .logic_level=GPIO_LVL_LOW, .pinConfig=DIO_LED_GREEN | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW, },
#endif/*HAS_LED*/

#ifdef HAS_BUTTON
	{.pad.port=0, .pad.pin=13, .config_number=0, .name="SW1",   .connector2="pin34",        .pull=GPIO__PULL_AIR,     .logic_level=GPIO_LVL_HI},
	{.pad.port=0, .pad.pin=14, .config_number=0, .name="SW2",   .connector2="pin34",        .pull=GPIO__PULL_AIR,     .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_LOG
    {.pad.port=0, .pad.pin=3, .config_number=3, .name="USART0_TX",          .pull=GPIO__PULL_AIR,    .logic_level=GPIO_LVL_HI, .pinConfig=GPIO_CFG_OUT_STD,},
#ifdef HAS_CLI
    {.pad.port=0, .pad.pin=2, .config_number=2, .name="USART0_RX",          .pull=GPIO__PULL_AIR,    .logic_level=GPIO_LVL_HI, .pinConfig=GPIO_CFG_IN_NOPULL,},
#endif /*HAS_CLI*/
#endif /*HAS_LOG*/

#ifdef HAS_I2C1
	{.pad.port=0, .pad.pin=4, .config_number=0, .name="I2C1_SCL",  .connector2="JP1.?", .mode=GPIO_MODE_AF_OD,      .pull=GPIO__PULL_UP,    .logic_level=GPIO_LVL_HI},
	{.pad.port=0, .pad.pin=5, .config_number=0, .name="I2C1_SDA",   .connector2="JP1.?", .mode=GPIO_MODE_AF_OD,      .pull=GPIO__PULL_UP,    .logic_level=GPIO_LVL_HI},
#endif

#ifdef HAS_SPI0
#endif

};

uint32_t gpio_get_cnt(void) {
    return ARRAY_SIZE(GpioConfig);
}

/*
 *  Callback function for the GPIO interrupt on CONFIG_GPIO_BUTTON_0.
 *  Note: GPIO interrupts are cleared prior to invoking callbacks.
 */
void gpioButtonFxn0(uint_least8_t index) {
    /* Toggle an LED */
    gpio_toggle((uint32_t)DIO_LED_GREEN);
    gpio_toggle((uint32_t)DIO_LED_RED);
}
/*
 *  Callback function for the GPIO interrupt on CONFIG_GPIO_BUTTON_1.
 *  This may not be used for all boards.
 *  Note: GPIO interrupts are cleared prior to invoking callbacks.
 */
void gpioButtonFxn1(uint_least8_t index) {
    /* Toggle an LED */
    gpio_toggle((uint32_t)DIO_LED_GREEN);
    gpio_toggle((uint32_t)DIO_LED_RED);
}

/*line order matters!*/
GPIO_CallbackFxn gpioCallbackFunctions[GPIO_COUNT] = {
/*0*/   NULL, /* LED Red */
/*1*/   NULL, /* LED Green */
};

#define CC26X2R1_LAUNCHXL_UART0_RX              IOID_2          /* RXD */
#define CC26X2R1_LAUNCHXL_UART0_TX              IOID_3          /* TXD */

/*line order matters!*/
PIN_Config BoardGpioInitTableLUT[] = {
/*0*/    DIO_LED_GREEN | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MED,/* LED Green */
/*1*/    DIO_LED_RED | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MED,/* LED Red */
         CC26X2R1_LAUNCHXL_UART0_RX | PIN_INPUT_EN | PIN_PULLDOWN ,       /* UART RX via debugger back channel */
         CC26X2R1_LAUNCHXL_UART0_TX | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL, /* UART TX via debugger back channel */
         PIN_TERMINATE
};

uint16_t pin_config_get_cnt(void){
	uint16_t cnt = 0;
	cnt = ARRAY_SIZE(BoardGpioInitTableLUT);
	return cnt;
}

/*line order matters!*/
GPIO_PinConfig gpioPinConfigs[GPIO_COUNT] = {
/*0*/    DIO_LED_GREEN | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_HIGH, /* LED Green */
/*1*/    DIO_LED_RED | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW, /* LED Red */
/*2*/    CC26X2R1_LAUNCHXL_UART0_RX | GPIO_CFG_IN_NOPULL,  /* Rx*/
/*3*/    CC26X2R1_LAUNCHXL_UART0_TX | GPIO_CFG_OUTPUT,  /* Tx */

};

