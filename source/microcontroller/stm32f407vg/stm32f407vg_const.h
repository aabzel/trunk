#ifndef STM32F407VG_CONST_H
#define STM32F407VG_CONST_H

#include "macro_utils.h"

/* Sensetivity */
#define GPIO_COUNT 114
#define EXT_INT_COUNT 16
#define TIMER_COUNT 14
#define TIMER_MAX_NUM (TIMER_COUNT+1)
#define ADC_COUNT 3
#define ADC_CHANNELS_COUNT 24
#define GPIO_PIN_MAX 15
#define TRNG_COUNT 1
#define MAX_IRQ_NUM 81 //  FPU_IRQn                    = 81      /*!< FPU global interrupt
#define TIMER_MAX_COUNT (TIMER_COUNT+1)


// computing
#define CPU_MAX_HZ 168000000
#define DAC_COUNT 2
#define DMA_COUNT 2
#define DMA_STREAM_COUNT 8
#define DMA_CHANNEL_COUNT DMA_STREAM_COUNT
#define I2C_COUNT 3
#define UART_COUNT 4
#define I2S_COUNT 3
#define UART_MAX_NUM (UART_COUNT+1)
#define SDIO_COUNT 1
#define SPI_COUNT 3
#define CAN_COUNT 2
#define USB_COUNT 2
#define LSI_FREQ 32000

#define MCU_NAME "stm32f407vg"
#define MCU_PACKAGE  "LQFP100"

/*storage*/
#define RAM_END (RAM_START + RAM_SIZE)
#define RAM_SIZE (192 * K_BYTES)
#define RAM_START 0x20000000
#define ROM_END (ROM_START + ROM_SIZE)
#define ROM_SIZE (1024 * K_BYTES)
#define ROM_START 0x08000000
#define NOR_FLASH_START ROM_START
#define NOR_FLASH_END (ROM_END)

#endif /* STM32F407VG_CONST_H */
