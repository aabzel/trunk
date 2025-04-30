
#ifndef STM32F407VE_H
#define STM32F407VE_H

#include <stm32f407xx.h>

#include "macro_utils.h"
#ifdef HAS_GPIO
#include "gpio_types.h"
#endif

#define MCU_NAME "stm32f407ve"
#define MCU_PACKAGE "LQFP100"

// connectivity
#define I2C_COUNT 3
#define UART_COUNT 4
#define UART_MAX_NUM 7
#define USB_COUNT 2
#define SDIO_COUNT 1
#define SPI_COUNT 3
#define CAN_COUNT 2
#define GPIO_COUNT 82
#define I2S_COUNT 2

//sensitivity
#define ADC_COUNT 3
#define ADC_CHANNELS_COUNT 16
#define MAX_IRQ_NUM FPU_IRQn
#define TIMER_COUNT 14
#define TIMER_MAX_NUM 15
//#define TIMER_MAX_COUNT (TIMER_COUNT+1)
#define TRNG_COUNT 0


// control
#define LSI_FREQ 32000
#define DAC_COUNT 2
#define DMA_COUNT 2
#define GPIO_PIN_MAX 15
#define DMA_STREAM_COUNT 8

// computing
#define CPU_MAX_HZ 168000000
#define AHB1_CLOCK_HZ SYS_FREQ
#define APB1_CLOCK_HZ (AHB1_CLOCK_HZ/4)
#define APB2_CLOCK_HZ (AHB1_CLOCK_HZ/2)
#define SYS_FREQ 48000000

// storage
#define RAM_START 0x20000000
#define ROM_START 0x08000000
#define RAM_SIZE (192 * K_BYTES)
#define RAM_END (RAM_START + RAM_SIZE)
#define ROM_END (ROM_START + ROM_SIZE)
#define ROM_SIZE (512 * K_BYTES)
#define NOR_FLASH_END (ROM_END)
#define NOR_FLASH_START ROM_START

/*MBR does not need GPIO*/
#if defined(HAS_GPIO) && defined(HAS_PINS)
extern const PinData_t PinConfig[];
uint16_t pin_get_cnt(void);
#endif

#endif /* STM32F407VE_H */
