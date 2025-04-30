#ifndef AT32F435ZM_CONST_H
#define AT32F435ZM_CONST_H

#include "macro_utils.h"
/* instead of in perform
   #include "microcontroller_const.h"

*/
#define MCU_NAME "at32f435zm"
#define MCU_PACKAGE "LQFP144"
#define MAX_IRQ_NUM (114) /*See page 53 in RM*/

/*sensitivity*/
#define ADC_CHANNELS_COUNT 18
#define ADC_COUNT 3
#define TIMER_COUNT 18
#define TIMER_MAX_NUM 20
#define TRNG_COUNT 1

// clocking
#define CPU_MAX_HZ 288000000
#define LSI_FREQ 32000
#define SYS_FREQ CPU_MAX_HZ
#define AHB1_CLOCK_HZ SYS_FREQ
#define APB1_CLOCK_HZ (AHB1_CLOCK_HZ/2)
#define APB2_CLOCK_HZ (AHB1_CLOCK_HZ/2)

// control
#define DAC_COUNT 2
#define DMA_COUNT 2
#define DMA_CHANNEL_COUNT 7

// storage
#define RAM_END (RAM_START + RAM_SIZE)
#define RAM_SIZE (384 * K_BYTES)
#define FLASH_PAGE_SIZE (4 * K_BYTES)
#define RAM_START 0x20000000
#define ROM_SIZE (4032 * K_BYTES)
#define FLASH_SECTOR_CNT ((ROM_SIZE)/(FLASH_PAGE_SIZE))
#define ROM_END (ROM_START + ROM_SIZE)
#define ROM_START 0x08000000
#define NOR_FLASH_START ROM_START
#define FLASH_SECTOR_SIZE (4 * K_BYTES)
#define FLASH_BLOCK_SIZE (64* K_BYTES)
#define FLASH_BANK_1_SIZE (2048 * K_BYTES)
#define FLASH_BANK_2_SIZE (1984 * K_BYTES)
#define NOR_FLASH_END (ROM_END)

/* connectivity interfaces */
#define GPIO_PIN_MAX 15
#define GPIO_COUNT 116
#define CAN_COUNT 2
#define I2C_COUNT 3
#define I2S_COUNT 4
#define SDIO_COUNT 2
#define SPI_COUNT 4
#define QSPI_COUNT 2
#define UART_COUNT 4
#define USART_COUNT 4
#define USB_COUNT 2

#define TIMER_MAX_COUNT (TIMER_COUNT+1)

#endif /* AT32F435ZM_CONST_H */
