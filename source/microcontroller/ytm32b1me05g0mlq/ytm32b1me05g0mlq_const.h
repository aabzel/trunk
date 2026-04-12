#ifndef YTM32B1ME05G0MLQ_CONST_H
#define YTM32B1ME05G0MLQ_CONST_H



#include "macro_utils.h"

/*sensitivity*/
#define ADC_CHANNELS_COUNT 24
#define ADC_COUNT 2
//#define TIMER_COUNT 9
//#define TIMER_MAX_NUM 11
//#define TIMER_MAX_COUNT (TIMER_COUNT+1)
#define TRNG_COUNT 1
#define MAX_IRQ_NUM (191) /*See page  ALIGN_0_IRQn    */


#define CPU_MAX_HZ MHZ_TO_HZ_U(120)
#define LSI_FREQ 32000
#define MCU_NAME "YTM32B1ME05G0MLQ"
#define MCU_PACKAGE "LQFP144"
//#define SYS_FREQ 100000000
//#define AHB1_CLOCK_HZ SYS_FREQ
//#define APB1_CLOCK_HZ (AHB1_CLOCK_HZ/2)
//#define APB2_CLOCK_HZ (AHB1_CLOCK_HZ/2)

// control
#define DAC_COUNT 1
#define DMA_COUNT 1
#define DMA_CHANNEL_COUNT 16

// storage
#define RAM_START 0x20000000
#define RAM_END (RAM_START + RAM_SIZE)
#define RAM_SIZE (128 * K_BYTES)
#define ROM_SIZE (1024 * K_BYTES)
#define ROM_START 0x00000000
//Main Flash memory contains bank 1 only, 256 KB, including 128 sectors, 2 K per sector.
#define FLASH_SECTOR_SIZE (2 * K_BYTES)
#define FLASH_PAGE_SIZE (FLASH_SECTOR_SIZE)
#define FLASH_SECTOR_CNT ((ROM_SIZE)/(FLASH_PAGE_SIZE))
#define ROM_END (ROM_START + ROM_SIZE)
#define NOR_FLASH_START ROM_START
#define NOR_FLASH_END (ROM_END)
#define FLASH_BANK_1_SIZE ROM_SIZE
#define FLASH_BANK_2_SIZE 0
#define FLASH_BLOCK_SIZE FLASH_SECTOR_SIZE

#ifndef FLASH_BASE
#define FLASH_BASE ((uint32_t)ROM_START)
#endif

/*interfaces*/
#define CAN_COUNT 6
#define GPIO_PIN_MAX 31
#define GPIO_COUNT 126
#define I2C_COUNT 3
#define I2S_COUNT 0
#define QSPI_COUNT 6
#define SPI_COUNT 6
#define SDIO_COUNT 0
#define UART_COUNT 6
#define USART_COUNT 6
#define USB_COUNT 0


#endif /* YTM32B1ME05G0MLQ_CONST_H */
