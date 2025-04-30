
#ifndef STM32F413ZH_CONST_H
#define STM32F413ZH_CONST_H

#include <stm32f413xx.h>

#include "macro_utils.h"

#define MAX_IRQ_NUM DFSDM2_FLT3_IRQn

#define RAM_SIZE (320 * K_BYTES)
#define RAM_START 0x20000000
#define RAM_END (RAM_START + RAM_SIZE)

#define NOR_FLASH_BASE   0x08000000
#define ROM_SIZE (1536 * K_BYTES)
#define NOR_FLASH_END (NOR_FLASH_BASE+ROM_SIZE)
#define ROM_START 0x08000000
#define ROM_END (ROM_START + ROM_SIZE)

#define MCU_NAME "stm32f413hz"

#define ADC_COUNT 1
#define SAI_COUNT 1 /*???*/
#define DMA_COUNT 2
#define DMA_STREAM_COUNT 8
#define I2C_COUNT 3
#define I2S_COUNT 5
#define CAN_COUNT 3
#define SDIO_COUNT 1
#define SPI_COUNT 5
#define USB_COUNT 1
#define QSPI_COUNT 1
#define TIMER_COUNT 14
#define TIMER_MAX_NUM 14
#define UART_COUNT 10
#define MAX_PWM_CH (14*4)
#define TIMER_MAX_COUNT 14
#define GPIO_PIN_MAX (15)
#define GPIO_COUNT (114)
#define PIN_COUNT (144)
#define CPU_MAX_HZ (100000000)

#define LSI_FREQ 32000

#define SYS_FREQ 60000000U
#define AHB1_CLOCK_HZ SYS_FREQ
#define APB2_CLOCK_HZ AHB1_CLOCK_HZ
#define APB1_CLOCK_HZ (AHB1_CLOCK_HZ/2)

#endif /* STM32F413ZH_CONST_H */
