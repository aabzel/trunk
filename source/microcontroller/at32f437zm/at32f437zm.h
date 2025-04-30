#ifndef AT32F437ZM_H
#define AT32F437ZM_H

#include "at32f435_437.h"
#ifdef HAS_MCAL_AT32
#include "at32f435_437_misc.h"
#endif

#include "macro_utils.h"
#ifdef HAS_GPIO
#include "gpio_types.h"
#endif

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

/*security*/
#define TRNG_COUNT 1

/*control*/
#define MAX_IRQ_NUM DMA2_Channel7_IRQn
#define DAC_COUNT 2
#define DMA_COUNT 2
#define DMA_STREAM_COUNT 22
#define GPIO_PIN_MAX 15
#define GPIO_COUNT 116

/*sensitivity*/
#define LSI_FREQ 32000
#define TIMER_COUNT 18
#define ADC_CHANNELS_COUNT 24
#define ADC_COUNT 3
#define TIMER_MAX_COUNT (TIMER_COUNT+1)

/*interfaces*/
#define CAN_COUNT 2
#define I2C_COUNT 3
#define I2S_COUNT 4
#define SDIO_COUNT 2
#define SPI_COUNT 4
#define QSPI_COUNT 2
#define UART_COUNT 4
#define USART_COUNT 4
#define USB_COUNT 2

/*MBR does not need GPIO*/
#if defined(HAS_GPIO) && defined(HAS_PINS)
extern const PinData_t PinConfig[];
uint16_t pin_get_cnt(void);
#endif

#endif /* AT32F437ZM_H */
