
#ifndef STM32F429ZI_H
#define STM32F429ZI_H

#include <stm32f429xx.h>

#include "macro_utils.h"
#include "gpio_types.h"

#define MAX_IRQ_NUM DMA2D_IRQn

#define RAM_SIZE (256 * K_BYTES)
#define RAM_START 0x20000000
#define RAM_END (RAM_START + RAM_SIZE)

#define ROM_START 0x08000000
#define ROM_SIZE (2048 * K_BYTES)
#define ROM_END (ROM_START + ROM_SIZE)
#define NOR_FLASH_END (ROM_START+ROM_SIZE)

#define MCU_NAME "STM32F429ZI"

/*Analog*/
#define ADC_BIT 12
#define ADC_COUNT 3
#define ADC_CHANNEL_COUNT 24
#define DAC_COUNT 2
#define DAC_BIT 12

#define DMA_COUNT 2
#define DMA_STREAM_COUNT 8

/*Connectivity*/
#define CAN_COUNT 2
#define GPIO_COUNT 114
#define GPIO_PIN_MAX 15
#define ETHERNET_COUNT 1
#define I2C_COUNT 3
#define I2S_COUNT 2
#define SDIO_COUNT 1
#define SPI_COUNT 6
#define RNG_COUNT 1
#define USB_COUNT 2
#define UART_COUNT 8


#define TIMER_16BIT_COUNT 5
#define TIMER_32BIT_COUNT 2
#define TIMER_COUNT 14
#define TIMER_MAX_COUNT 14
#define DMA_CNT 2
#define DMA_STREAM_CNT 8
#define PACKAGE "LQFP144"

#define LSI_FREQ 32000

#define SYS_FREQ_MAX 180000000U
#define SYS_FREQ 100000000

#define AHB1_CLOCK_HZ SYS_FREQ
#define APB2_CLOCK_HZ AHB1_CLOCK_HZ
#define APB1_CLOCK_HZ (AHB1_CLOCK_HZ/2)

#define NOR_FLASH_START ROM_START

extern const PinData_t PinConfig[];

uint16_t pin_get_cnt(void);

#endif /* STM32F429ZI_H */
