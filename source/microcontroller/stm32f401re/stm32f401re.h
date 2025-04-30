
#ifndef STM32F401RE_H
#define STM32F401RE_H

#include <stm32f401xe.h>

#include "macro_utils.h"
#include "gpio_types.h"

#define MAX_IRQ_NUM SPI4_IRQn

#define RAM_SIZE (96 * K_BYTES)
#define RAM_START 0x20000000
#define RAM_END (RAM_START + RAM_SIZE)

#define ROM_SIZE (512 * K_BYTES)
#define ROM_START 0x08000000
#define ROM_END (ROM_START + ROM_SIZE)

#define MCU_NAME "STM32F401RE"

#define ADC_BIT 12
#define ADC_COUNT 1
#define SPI_COUNT 4
#define TIMER_16BIT_COUNT 5
#define TIMER_32BIT_COUNT 2
#define TIMER_COUNT 8
#define TIMER_MAX_COUNT 11
#define I2C_COUNT 3
#define I2S_COUNT 2
#define DMA_CNT 2
#define DMA_STREAM_CNT 8
#define GPIO_PIN_MAX 15
#define GPIO_COUNT 50
#define SDIO_COUNT 1
#define USB_COUNT 1
#define UART_COUNT 3
#define PACKAGE "LQFP64"

#define LSI_FREQ 32000

#define SYS_FREQ_MAX 84000000U
#define SYS_FREQ SYS_FREQ_MAX //60MHz 150ms

#define AHB1_CLOCK_HZ SYS_FREQ
#define APB2_CLOCK_HZ AHB1_CLOCK_HZ
#define APB1_CLOCK_HZ (AHB1_CLOCK_HZ/2)

#define NOR_FLASH_START ROM_START

extern const PinData_t PinConfig[];

uint16_t pin_get_cnt(void);

#endif /* STM32F401RE_H */
