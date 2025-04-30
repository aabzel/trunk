#ifndef AT32F437ZM_CONST_H
#define AT32F437ZM_CONST_H


#include "macro_utils.h"

#define CPU_MAX_HZ 288000000
#define SYS_FREQ CPU_MAX_HZ
#define AHB1_CLOCK_HZ SYS_FREQ
#define APB1_CLOCK_HZ (AHB1_CLOCK_HZ/2)
#define APB2_CLOCK_HZ (AHB1_CLOCK_HZ/2)
#define MCU_NAME "at32f437zm"
#define MCU_PACKAGE "LQFP144"

/*storage*/
#define FLASH_PAGE_SIZE (4 * K_BYTES)
#define RAM_START 0x20000000
#define ROM_START 0x08000000
#define RAM_END (RAM_START + RAM_SIZE)
#define RAM_SIZE (384 * K_BYTES)
#define ROM_SIZE (4032 * K_BYTES)
#define ROM_END (ROM_START + ROM_SIZE)
#define FLASH_SECTOR_CNT ((ROM_SIZE)/(FLASH_PAGE_SIZE))
#define NOR_FLASH_START ROM_START
#define NOR_FLASH_END (ROM_END)
#define FLASH_SECTOR_SIZE (4 * K_BYTES)
#define FLASH_BLOCK_SIZE (64* K_BYTES)
#define FLASH_BANK_1_SIZE (2048 * K_BYTES)
#define FLASH_BANK_2_SIZE (1984 * K_BYTES)

#ifndef MCUID_MEMORY
//#define MCUID_MEMORY MCUID_MEMORY_4096K
#endif

/*security*/
#define TRNG_COUNT 1

/*control*/
#define MAX_IRQ_NUM 114   // 114 DMA2_Channel7_IRQn
#define DAC_COUNT 2
#define DMA_COUNT 2
#define DMA_CHANNEL_COUNT 7
#define GPIO_PIN_MAX 15
#define GPIO_COUNT 116

/*sensitivity*/
#define EXT_INT_COUNT 15
#define LSI_FREQ 32000
#define TIMER_COUNT 18
#define ADC_CHANNELS_COUNT 24
#define ADC_COUNT 3
#define TIMER_MAX_COUNT (TIMER_COUNT+1)
#define TIMER_MAX_NUM 20

/*interfaces*/
#define CAN_COUNT 2
#define I2C_COUNT 3
#define SPI_COUNT 4
#define I2S_COUNT (SPI_COUNT+2)
#define SDIO_COUNT 2
#define QSPI_COUNT 2
#define UART_COUNT 4
#define USART_COUNT 4
#define USB_COUNT 2


#endif /* AT32F437ZM_CONST_H */
