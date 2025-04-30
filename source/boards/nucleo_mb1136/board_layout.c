#include "board_layout.h"

#include "data_utils.h"
#include "gpio_mcal.h"
#include "gpio_types.h"
#include "stm32f4xx_hal.h"
#include "sys_config.h"

#ifndef USE_HAL_DRIVER
#error "that wile only for STM32 MCUs"
#endif /*USE_HAL_DRIVER*/

#include "gpio_stm_const.h"

const PinConfig_t PinConfigLut[] = {
    /*{.pad.port=GPIO_PORT_PIN2PAD(PORT_A,5),  .name="LED_G",     .mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO_NOPULL, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .pin_state=GPIO_PIN_RESET},*/
    {.pad.port=PORT_C, .pad.pin=13, .name="UserBtn",   .mode=GPIO_MODE_INPUT,      .pull=GPIO_NOPULL},
    {.pad.port=PORT_B, .pad.pin=3,  .name="LoRaBusy",  .mode=GPIO_MODE_INPUT,      .pull=GPIO_NOPULL, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .pin_state=GPIO_PIN_RESET},
    {.pad.port=PORT_A, .pad.pin=8,  .name="LoRa_CS",   .mode= GPIO_API_MODE_OUTPUT, .pull=GPIO_NOPULL, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=0,               .pin_state=GPIO_PIN_SET},
    {.pad.port=PORT_A, .pad.pin=5,  .name="SPI1_SCK",  .mode=GPIO_API_MODE_ALT1,      .pull=GPIO_NOPULL, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF5_SPI1,   .pin_state=GPIO_PIN_RESET},
    {.pad.port=PORT_A, .pad.pin=6,  .name="SPI1_MISO", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO_NOPULL, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF5_SPI1,   .pin_state=GPIO_PIN_RESET},
    {.pad.port=PORT_A, .pad.pin=7,  .name="SPI1_MOSI", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO_NOPULL, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF5_SPI1,   .pin_state=GPIO_PIN_RESET},
    {.pad.port=PORT_A, .pad.pin=2,  .name="USART2_TX", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO_NOPULL, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF7_USART2, .pin_state=GPIO_PIN_SET},
    {.pad.port=PORT_A, .pad.pin=3,  .name="USART2_RX", .mode=GPIO_API_MODE_ALT1,      .pull=GPIO_NOPULL, .speed=GPIO_SPEED_FREQ_VERY_HIGH, .mux=GPIO_AF7_USART2, .pin_state=GPIO_PIN_SET},
    {.pad.port=PORT_A, .pad.pin=0,  .name="LoRaRst",   .mode=GPIO_API_MODE_OUTPUT,  .pull=GPIO_NOPULL, .speed=GPIO_SPEED_FREQ_LOW,       .mux=0,               .pin_state=GPIO_PIN_SET},
};

uint32_t pin_get_cnt(void) {
    return ARRAY_SIZE(PinConfigLut);
}
