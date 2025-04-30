
#ifndef NRF5340_APP_CONST_H
#define NRF5340_APP_CONST_H

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif /*HAS_MICROCONTROLLER*/

#include "macro_utils.h"

#define RAM_START 0x20000000
#define RAM_SIZE (512 * K_BYTES)

#define ROM_START 0x00000000
#define NOR_FLASH_BASE 0x00000000
#define ROM_SIZE (1024 * K_BYTES)

#define I2S_COUNT 1

/*Successive approximation*/
/*(see page 523) 7.29 SAADC — Successive approximation analog-todigital converter*/
#define ADC_COUNT 1          /*?*/
#define ADC_BITNESS 12       /*?*/
#define ADC_CHANNELS_COUNT 8 /*see Figure 26: Application core block diagram*/
#define ADC_CHANNELS_MAX 7   /*see Figure 26: Application core block diagram*/
#define ADC_CHANNELS_MIN 0   /*see Figure 26: Application core block diagram*/

#define I2C_COUNT 4 /*TWIM*/
#define PDM_COUNT 1
#define SPI_COUNT 5
#define SPIS_COUNT 4
#define RTC_COUNT 2
#define SPIM_COUNT 5
#define TIMER_COUNT 3
#define PWM_COUNT 4 /*7.23 PWM — Pulse width modulation*/
#define PWM_CHANNEL_COUNT 4
#define QSPI_COUNT 1

#define UART_COUNT 4
#define USBD_COUNT 1

#define TIMER_MAX_COUNT TIMER_COUNT

#define FLASH_START_APP_CORE (ROM_START)
#define FLASH_END_APP_CORE (ROM_START + ROM_SIZE)

#define NOR_FLASH_END (ROM_START + ROM_SIZE)
#define FLASH_SIZE_APP_CORE (ROM_SIZE)
#define ON_CHIP_NOR_FLASH_APP_PAGE_SIZE (4 * K_BYTES)
#define ON_CHIP_NOR_FLASH_PAGE_SIZE (ON_CHIP_NOR_FLASH_APP_PAGE_SIZE)

#endif /* NRF5340_APP_CONST_H */
