#ifndef MCAL_TASKS_H
#define MCAL_TASKS_H


#ifdef HAS_CRYP_PROC
#define CRYP_TASKS
#else
#define CRYP_TASKS
#endif

#ifdef HAS_ADC_PROC
#include "adc_mcal.h"
#define ADC_TASKS                                                                            \
    {.name="ADC", .period_us=ADC_POLL_PERIOD_US, .limiter.function=adc_proc,},               \
    {.name="AdcChan", .period_us=ADC_CHANNEL_PERIOD_US, .limiter.function=adc_channel_proc,},
#else
#define ADC_TASKS
#endif /**/

#ifdef HAS_GPIO_PROC
#include "gpio_mcal.h"
#define GPIO_TASKS {.name="GPIO", .period_us=GPIO_POLL_PERIOD_US, .limiter.function=gpio_proc,},
#else
#define GPIO_TASKS
#endif

#ifdef HAS_DMA_PROC
#define DMA_TASKS
#else
#define DMA_TASKS
#endif

#ifdef HAS_TIMER_PROC
#define TIMER_TASKS
#else
#define TIMER_TASKS
#endif


#ifdef HAS_UART_PROC
#include "uart_mcal.h"
#define UART_TASKS {.name="UART", .period_us=UART_POLL_PERIOD_US, .limiter.function=uart_proc,},
#else
#define UART_TASKS
#endif

#ifdef HAS_USB_PROC
#define USB_MCAL_TASKS
#else
#define USB_MCAL_TASKS
#endif

#ifdef HAS_FLASH_PROC
#include "flash_mcal.h"
#define FLASH_TASKS     \
        {.name="FLASH",     \
         .period_us=FLASH_POLL_PERIOD_US,   \
         .limiter.function=flash_proc, \
		},
#else
#define FLASH_TASKS
#endif



#ifdef HAS_EEPROM_PROC
#include "eeprom_mcal.h"
#define EEPROM_TASKS \
    {                     \
     .name="EEPROM",    \
     .period_us=EEPROM_POLL_PERIOD_US,   \
     .limiter.function=eeprom_proc, \
    },
#else
#define EEPROM_TASKS
#endif


#ifdef HAS_I2C_PROC
#include "i2c_mcal.h"
#define I2C_TASKS                                                                            \
    {.name="I2C", .period_us=I2C_POLL_PERIOD_US, .limiter.function=i2c_proc,},
#else
#define I2C_TASKS
#endif

#ifdef HAS_I2S_PROC
#include "i2s_mcal.h"
#define I2S_TASKS                                                                            \
    {.name="I2S", .period_us=I2S_POLL_PERIOD_US, .limiter.function=i2s_proc,},
#else
#define I2S_TASKS
#endif

#ifdef HAS_SPI_PROC
#include "spi_mcal.h"

#define SPI_TASKS {.name = "SPI",                    \
                   .period_us = SPI_POLL_PERIOD_US,                    \
				   .limiter.function = spi_proc,},
#else
#define SPI_TASKS
#endif

#ifdef HAS_SPIFI_PROC
#include "spifi_mcal.h"

#define SPIFI_TASKS {.name = "SPIFI",                                      \
                     .period_us = SPIFI_POLL_PERIOD_US,                    \
				     .limiter.function = spifi_proc,},
#else
#define SPIFI_TASKS
#endif


#ifdef HAS_I2S_FULL_DUPLEX_PROC
#include "i2s_full_duplex.h"
#define I2S_FULL_DUPLEX_TASKS                                                                            \
    {.name="I2sFullDuplex", .period_us=I2S_FULL_DUPLEX_POLL_PERIOD_US, .limiter.function=i2s_full_duplex_proc,},
#else
#define I2S_FULL_DUPLEX_TASKS
#endif

#ifdef HAS_INPUT_CAPTURE_PROC
#include "input_capture_mcal.h"
#define INPUT_CAPTURE_TASKS                                                                            \
    {.name="InCapt", .period_us=INPUT_CAPTURE_POLL_PERIOD_US, .limiter.function=input_capture_proc,},
#else
#define INPUT_CAPTURE_TASKS
#endif



#ifdef HAS_WATCHDOG_TASK
#include "watchdog_mcal.h"
#define WATCHDOG_TASK                                                                            \
    {.name="WatchDog", .period_us=WATCHDOG_POLL_PERIOD_US, .limiter.function=watchdog_proc,},
#else
#define WATCHDOG_TASK
#endif

#define MCAL_SENSITIVITY_TASKS         \
    ADC_TASKS                          \
    TIMER_TASKS                        \
    WATCHDOG_TASK                      \
    INPUT_CAPTURE_TASKS

#define MCAL_CONNECTIVITY_TASKS         \
    I2C_TASKS                           \
    I2S_TASKS                           \
    I2S_FULL_DUPLEX_TASKS               \
    SPI_TASKS                           \
    SPIFI_TASKS                         \
    UART_TASKS                          \
    USB_MCAL_TASKS

#define MCAL_STORAGE_TASKS         \
    EEPROM_TASKS                   \
    FLASH_TASKS

#define MCAL_COMPUTING_TASKS         \
    CRYP_TASKS

#define MCAL_CONTROL_TASKS          \
    DMA_TASKS                       \
    GPIO_TASKS

#define MCAL_TASKS                  \
    MCAL_SENSITIVITY_TASKS          \
    MCAL_CONNECTIVITY_TASKS         \
    MCAL_COMPUTING_TASKS            \
    MCAL_CONTROL_TASKS              \
    MCAL_STORAGE_TASKS

#endif /* MCAL_TASKS_H */
