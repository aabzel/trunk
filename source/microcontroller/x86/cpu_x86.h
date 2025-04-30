#ifndef CPU_X86_H
#define CPU_X86_H


#include "macro_utils.h"
#ifdef HAS_GPIO
#include "gpio_types.h"
#endif

typedef int16_t IRQn_Type;

#define ADC_CHANNELS_COUNT 24
#define ADC_COUNT 3
#define DMA_CHANNEL_COUNT 0
#define AHB1_CLOCK_HZ SYS_FREQ
#define APB1_CLOCK_HZ (AHB1_CLOCK_HZ/2)
#define APB2_CLOCK_HZ (AHB1_CLOCK_HZ/2)
#define CAN_COUNT 2
#define CPU_MAX_HZ 288000000
#define DAC_COUNT 2
#define DMA_COUNT 2
#define DMA_STREAM_COUNT 22
#define GPIO_COUNT 0
#define GPIO_PIN_MAX 0
#define LSI_FREQ 32000
#define MAX_IRQ_NUM (114) /*See page 53 in RM*/
#define MCU_NAME "cpu_x86"
#define MCU_PACKAGE "LQFP144"
#define RAM_END (RAM_START + RAM_SIZE)
#define RAM_SIZE (384 * K_BYTES)
#define FLASH_PAGE_SIZE (4 * K_BYTES)
#define RAM_START 0x20000000
#define ROM_SIZE (4032 * K_BYTES)
#define FLASH_SECTOR_CNT ((ROM_SIZE)/(FLASH_PAGE_SIZE))
#define ROM_END (ROM_START + ROM_SIZE)
#define ROM_START 0x08000000
#define NOR_FLASH_START ROM_START
#define SYS_FREQ 100000000
#define TIMER_COUNT 18
#define TRNG_COUNT 1

/*interfaces*/
#define I2C_COUNT 3
#define I2S_COUNT 4
#define SDIO_COUNT 2
#define SPI_COUNT 4
#define QSPI_COUNT 2
#define UART_COUNT 4
#define USART_COUNT 4
#define USB_COUNT 2

#define NOR_FLASH_END (ROM_END)
#define TIMER_MAX_COUNT (TIMER_COUNT+1)
/*MBR does not need GPIO*/
#if defined(HAS_GPIO) && defined(HAS_PINS)
extern const PinData_t PinConfig[];
uint16_t pin_get_cnt(void);
#endif

#endif /* CPU_X86_H */
