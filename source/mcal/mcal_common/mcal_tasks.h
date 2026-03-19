#ifndef MCAL_TASKS_H
#define MCAL_TASKS_H


#ifdef HAS_CRYP_PROC
#include "cryp_mcal.h"
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
#define GPIO_TASK {.name="GPIO", .period_us=GPIO_POLL_PERIOD_US, .limiter.function=gpio_proc,},
#else
#define GPIO_TASK
#endif

#ifdef HAS_MAM_PROC
#include "mam_mcal.h"
#define MAM_TASK {.name="Mam", .period_us=MAM_POLL_PERIOD_US, .limiter.function=mam_proc,},
#else
#define MAM_TASK
#endif
#ifdef HAS_DMA_CHANNEL_PROC
#include "dma_channel_mcal.h"
#define DMA_CHANNEL_TASK {.name="DmaCh", .period_us = DMA_CHANNEL_PERIOD_US, .limiter.function = dma_channel_proc,},
#else
#define DMA_CHANNEL_TASK
#endif

#ifdef HAS_DMA_PROC
/*To poll status register*/
#include "dma_mcal.h"
#define DMA_TASK     {.name="Dma", .period_us = DMA_PERIOD_US, .limiter.function = dma_proc,},
#else
#define DMA_TASK
#endif

#ifdef HAS_TIMER_PROC
#define TIMER_TASKS
#else
#define TIMER_TASKS
#endif

#ifdef HAS_LOCKSTEP_PROC
#include "lockstep_mcal.h"

#define LOCKSTEP_TASK                                   \
    {                                                   \
     .name = "LockStep",                                \
     .period_us = LOCKSTEP_POLL_PERIOD_US,              \
     .limiter.function = lockstep_proc,                 \
    },
#else
#define LOCKSTEP_TASK
#endif



#ifdef HAS_UART_PROC
#include "uart_mcal.h"

#ifdef HAS_UART_HEARTBEAT
#define UART_HEARTBEAT_TASK  {.name="UART_HB", .period_us=UART_HEARTBEAT_PERIOD_US, .limiter.function=uart_heartbeat_proc,},
#else
#define UART_HEARTBEAT_TASK
#endif

#define UART_TASKS                \
          UART_HEARTBEAT_TASK     \
          {.name="UART", .period_us=UART_POLL_PERIOD_US, .limiter.function=uart_proc,},
#else
#define UART_TASKS
#endif


#ifdef HAS_USB_PROC
#include "usb_mcal.h"
#define USB_MCAL_TASKS                            \
        {                                         \
         .period_us = USB_POLL_PERIOD_US,         \
         .limiter.function =  usb_proc,           \
         .name = "Usb",                           \
        },

#else
#define USB_MCAL_TASKS
#endif

#ifdef HAS_FLASH_PROC
#include "flash_mcal.h"
#define FLASH_TASKS                         \
        {.name="FLASH",                     \
         .period_us=FLASH_POLL_PERIOD_US,   \
         .limiter.function=flash_proc,      \
		},
#else
#define FLASH_TASKS
#endif

#ifdef HAS_EEPROM_PROC
#include "eeprom_mcal.h"
#define EEPROM_TASKS                       \
    {                                      \
     .name = "EEPROM",                     \
     .period_us = EEPROM_POLL_PERIOD_US,   \
     .limiter.function = eeprom_proc,      \
    },
#else
#define EEPROM_TASKS
#endif

#ifdef HAS_MULTICORE_PROC
#include "multicore_mcal.h"
#define MULTICORE_TASK                       \
    {                                         \
     .name = "MultiCore",                     \
     .period_us = MULTICORE_POLL_PERIOD_US,   \
     .limiter.function = multicore_proc,      \
    },
#else
#define MULTICORE_TASK
#endif

#ifdef HAS_MAILBOX_PROC
#include "mailbox_mcal.h"

#define MAILBOX1_TASK                                  \
    {                                                  \
     .name = "MailBox1",                               \
     .period_us = MAILBOX_POLL_PERIOD_US,              \
     .limiter.function = mailbox1_proc,                \
    },                                                 \
    {                                                  \
     .name = "MailBox1Channel",                        \
     .period_us = MAILBOX_CHANNEL_POLL_PERIOD_US,      \
     .limiter.function = mailbox1_channel_proc,        \
    },

#define MAILBOX2_TASK                                  \
    {                                                  \
     .name = "MailBox2",                               \
     .period_us = MAILBOX_POLL_PERIOD_US,              \
     .limiter.function = mailbox2_proc,                \
    },                                                 \
    {                                                  \
     .name = "MailBox2Channel",                        \
     .period_us = MAILBOX_CHANNEL_POLL_PERIOD_US,      \
     .limiter.function = mailbox2_channel_proc,        \
    },

#define MAILBOX3_TASK                                  \
    {                                                  \
     .name = "MailBox3",                               \
     .period_us = MAILBOX_POLL_PERIOD_US,              \
     .limiter.function = mailbox3_proc,                \
    },                                                 \
    {                                                  \
     .name = "MailBox3Channel",                        \
     .period_us = MAILBOX_CHANNEL_POLL_PERIOD_US,      \
     .limiter.function = mailbox3_channel_proc,        \
    },
#else
#define MAILBOX_TASK
#define MAILBOX1_TASK
#define MAILBOX2_TASK
#define MAILBOX3_TASK
#endif

#ifdef HAS_I2C_PROC
#include "i2c_mcal.h"
#define I2C_TASKS                       \
    {.name="I2C",                       \
     .period_us=I2C_POLL_PERIOD_US,     \
	 .limiter.function=i2c_proc,        \
	 },
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

#ifdef HAS_I2S_FULL_DUPLEX_PROC
#include "i2s_full_duplex.h"
#define I2S_FULL_DUPLEX_TASKS                         \
    {.name="I2sFullDuplex",                           \
	 .period_us=I2S_FULL_DUPLEX_POLL_PERIOD_US,       \
	 .limiter.function=i2s_full_duplex_proc,          \
    },
#else
#define I2S_FULL_DUPLEX_TASKS
#endif

#ifdef HAS_INPUT_CAPTURE_PROC
#include "input_capture_mcal.h"
#define INPUT_CAPTURE_TASKS                                                                            \
    {.name="InCapt", \
	 .period_us=INPUT_CAPTURE_POLL_PERIOD_US, \
	 .limiter.function=input_capture_proc,\
    },
#else
#define INPUT_CAPTURE_TASKS
#endif

#ifdef HAS_SDIO_PROC
#include "sdio_mcal.h"

#define SDIO_TASK {.name = "SDIO",                    \
                   .period_us = SDIO_POLL_PERIOD_US,                    \
                   .limiter.function = sdio_proc,},
#else
#define SDIO_TASK
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


#ifdef HAS_WATCHDOG_TASK
#include "watchdog_mcal.h"
#define WATCHDOG_TASK                                                                            \
    {.name="WatchDog", .period_us=WATCHDOG_POLL_PERIOD_US, .limiter.function=watchdog_proc,},
#else
#define WATCHDOG_TASK
#endif


#ifdef HAS_MPU_PROC
#include "mpu_mcal.h"
#define MPU_TASK                                                                            \
    {.name="Mpu", .period_us=MPU_POLL_PERIOD_US, .limiter.function=mpu_proc,},
#else
#define MPU_TASK
#endif

#ifdef HAS_EXT_INT_PROC
#include "ext_int_mcal.h"
#define EXT_INT_TASK                                                                            \
    {.name = "ExtInt", .period_us = EXT_INT_POLL_PERIOD_US, .limiter.function = ext_int_proc,},
#else
#define EXT_INT_TASK
#endif

#define MCAL_SENSITIVITY_TASKS          \
    ADC_TASKS                           \
    EXT_INT_TASK                        \
    TIMER_TASKS                         \
    WATCHDOG_TASK                       \
    MPU_TASK                            \
    LOCKSTEP_TASK                       \
    INPUT_CAPTURE_TASKS

#define MCAL_CONNECTIVITY_TASKS         \
    I2C_TASKS                           \
    I2S_TASKS                           \
    I2S_FULL_DUPLEX_TASKS               \
    MAILBOX1_TASK                       \
    SDIO_TASK                           \
    SPI_TASKS                           \
    SPIFI_TASKS                         \
    UART_TASKS                          \
    USB_MCAL_TASKS

#define MCAL_STORAGE_TASKS           \
    EEPROM_TASKS                     \
    FLASH_TASKS

#define MCAL_COMPUTING_TASKS         \
    CRYP_TASKS

#define MCAL_CONTROL_TASKS           \
    DMA_TASK                        \
    GPIO_TASK

#define MCAL_TASKS                  \
    MCAL_SENSITIVITY_TASKS          \
    MCAL_CONNECTIVITY_TASKS         \
    MCAL_COMPUTING_TASKS            \
    MCAL_CONTROL_TASKS              \
    MCAL_STORAGE_TASKS

#endif /* MCAL_TASKS_H */
