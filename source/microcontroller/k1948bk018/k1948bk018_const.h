#ifndef K1948BK018_CONST_H
#define K1948BK018_CONST_H

//#include "macro_utils.h"
/* instead of in perform
   #include "microcontroller_const.h"

*/
#ifndef K_BYTES
#define K_BYTES 1024UL
#endif

#define MCU_NAME "K1948BK018"
#define MCU_PACKAGE "QFN64"

/*sensitivity*/
#define ADC_CHANNELS_COUNT 8
#define ADC_COUNT 1
#define TIMER_COUNT 6
#define TIMER_MAX_NUM 6


// clocking
#define CPU_MAX_HZ (32000000U)
#define LSI_FREQ 32768
#define SYS_FREQ CPU_MAX_HZ
#define AHB1_CLOCK_HZ SYS_FREQ


// control
#define DAC_COUNT 1
#define DMA_COUNT 1
#define DMA_CHANNEL_COUNT 1

// storage
#define EXT_ROM_SIZE (4UL * 1024UL * 1024UL)
#define ROM_SIZE (8 * K_BYTES)
#define RAM_SIZE (16 * K_BYTES)
//#define FLASH_PAGE_SIZE (4 * K_BYTES)

#define ROM_START 0x01000000
#define RAM_START 0x02000000
#define EXT_ROM_START 0x80000000
#define EXT_ROM_END (EXT_ROM_START+EXT_ROM_SIZE)
#define RAM_END (RAM_START + RAM_SIZE)
#define FLASH_SECTOR_CNT ((ROM_SIZE)/(FLASH_PAGE_SIZE))
#define ROM_END (ROM_START + ROM_SIZE)
#define NOR_FLASH_START ROM_START
//
#define NOR_FLASH_END (ROM_END)

/* connectivity interfaces */
#define GPIO_PIN_MAX 15
#define GPIO_COUNT 37

#define I2C_COUNT 2
#define SPI_COUNT 2
#define QSPI_COUNT 1
#define SPIFI_COUNT 1
#define UART_COUNT 2
#define UART_MAX_NUM 2
#define TIMER_MAX_COUNT (TIMER_COUNT+1)

/*
  see Table 70 List of interrupt lines for devices connected to the interrupt controller
 */
typedef enum {
    INT_NUM_TIMER32_0 = 0,
    INT_NUM_USART_0 = 1,
    INT_NUM_USART_1 = 2,
    INT_NUM_SPI_0 = 3,
    INT_NUM_SPI_1 = 4,
    INT_NUM_GPIO = 5,
    INT_NUM_I2C_0 = 6,
    INT_NUM_I2C_1 = 7,
    INT_NUM_WDT = 8,
    INT_NUM_TIMER16_0 = 9,
    INT_NUM_TIMER16_1 = 10,
    INT_NUM_TIMER16_2 = 11,
    INT_NUM_TIMER32_1 = 12,
    INT_NUM_TIMER32_2 = 13,
    INT_NUM_SPIFI = 14,
    INT_NUM_RTC = 15,
    INT_NUM_EEPROM = 16,
    INT_NUM_WDT_PER = 17,
    INT_NUM_WDT_SPIFI = 18,
    INT_NUM_WDT_EEPROM = 19,
    INT_NUM_DMA = 20,
    INT_NUM_CLK_MON = 21,
    INT_NUM_AVCC_LOW = 22,
    INT_NUM_AVCC_UP = 23,
    INT_NUM_VCC_LOW = 24,
    INT_NUM_VCC_UP = 25,
    INT_NUM_BAT_LOW = 26,
    INT_NUM_BROUWN_OUT = 27,
    INT_NUM_TEMP = 28,
    INT_NUM_ADC = 29,
    INT_NUM_DAC0 = 30,
    INT_NUM_DAC1 = 31,
    INT_NUM_UNDEF = 32,
} IRQn_Type;

#define MAX_IRQ_NUM (INT_NUM_DAC1)

#endif /* K1948BK018_CONST_H */


