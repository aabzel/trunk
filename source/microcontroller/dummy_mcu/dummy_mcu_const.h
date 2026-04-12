#ifndef DUMMY_MCU_CONST_H
#define DUMMY_MCU_CONST_H

#include "macro_utils.h"

/*sensitivity*/
#define ADC_CHANNELS_COUNT 0
#define ADC_COUNT 4
//#define TIMER_COUNT 9
//#define TIMER_MAX_NUM 11
//#define TIMER_MAX_COUNT (TIMER_COUNT+1)

#define MAX_IRQ_NUM (153U) /*See page  CMU4_IRQn    */

#define CPU_MAX_HZ MHZ_TO_HZ_U(300)
#define CPU_CORE_COUNT 3
#define LSI_FREQ 32000
#define MCU_NAME "DUMMY_MCU"
#define MCU_PACKAGE "LQFP176"
//#define SYS_FREQ 100000000
//#define AHB1_CLOCK_HZ SYS_FREQ
//#define APB1_CLOCK_HZ (AHB1_CLOCK_HZ/2)
//#define APB2_CLOCK_HZ (AHB1_CLOCK_HZ/2)

// control
#define DMA_COUNT 2
#define DMA_CHANNEL_COUNT 32
#define EIM_COUNT 1
#define MPU_COUNT 1
#define MAM_COUNT 3

// storage
//#define RAM_START 0x21000000
#define RAM_START 0x20000000
#define RAM_END (RAM_START + RAM_SIZE)
#define RAM_SIZE (128 * K_BYTES)
#define ROM_SIZE (8 * 1024 * K_BYTES)
#define ROM_START 0x01000000U

#define DFLASH_START 0x04000000
//#ifndef DFLASH_SIZE
//#define DFLASH_SIZE (256* K_BYTES)
//#endif

//Main Flash memory contains bank 1 only, 256 KB, including 128 sectors, 2 K per sector.
#define FLASH_SECTOR_SIZE (4* K_BYTES)
#define FLASH_SECTOR_CNT ((ROM_SIZE)/(FLASH_SECTOR_SIZE))
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
#define CAN_COUNT 1
#define GPIO_PIN_MAX 31
#define GPIO_COUNT 1
#define I2C_COUNT 2
#define QSPI_COUNT 1
#define SPI_COUNT 2
#define UART_COUNT 3
#define USART_COUNT 3
#define UART_MAX_NUM USART_COUNT
#define MAILBOX_CHANNEL_CNT 8


#endif /* DUMMY_MCU_CONST_H */
