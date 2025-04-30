#ifndef MCAL_COMMANDS_H
#define MCAL_COMMANDS_H

#ifdef HAS_LOG
#include "log.h"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_MCAL
#error "+HAS_MCAL"
#endif

#ifndef HAS_MCAL_COMMANDS
#error "+HAS_MCAL_COMMANDS"
#endif

#ifdef HAS_ADC_COMMANDS
#include "adc_commands.h"
#else
#define ADC_COMMANDS
#endif

#ifdef HAS_BOOT_MANAGER_COMMANDS
#include "boot_manager_commands.h"
#else
#define BOOT_MANAGER_COMMANDS
#endif

#ifdef HAS_CRYP_COMMANDS
#include "cryp_commands.h"
#else
#define CRYP_COMMANDS
#endif

#ifdef HAS_FLASH_COMMANDS
#include "flash_commands.h"
#else
#define FLASH_COMMANDS
#endif

#ifdef HAS_EEPROM_COMMANDS
#include "eeprom_commands.h"
#else
#define EEPROM_COMMANDS
#endif

#ifdef HAS_GPIO_COMMANDS
#include "gpio_commands.h"
#else
#define GPIO_COMMANDS
#endif

#ifdef HAS_I2C_COMMANDS
#include "i2c_commands.h"
#else
#define I2C_COMMANDS
#endif

#ifdef HAS_I2S_COMMANDS
#include "i2s_commands.h"
#else
#define I2S_COMMANDS
#endif

#ifdef HAS_I2S_FULL_DUPLEX_COMMANDS
#include "i2s_full_duplex_commands.h"
#else
#define I2S_FULL_DUPLEX_COMMANDS
#endif


#ifdef HAS_WATCHDOG_COMMANDS
#include "WATCHDOG_commands.h"
#else
#define WATCHDOG_COMMANDS
#endif

#ifdef HAS_SPI_COMMANDS
#include "spi_commands.h"
#else
#define SPI_COMMANDS
#endif

#ifdef HAS_SPIFI_COMMANDS
#include "spifi_commands.h"
#else
#define SPIFI_COMMANDS
#endif

#ifdef HAS_CAN_COMMANDS
#include "can_commands.h"
#else
#define CAN_COMMANDS
#endif

#ifdef HAS_DMA_COMMANDS
#include "dma_commands.h"
#else
#define DMA_COMMANDS
#endif

#ifdef HAS_TIMER_COMMANDS
#include "timer_commands.h"
#else
#define TIMER_COMMANDS
#endif

#ifdef HAS_PWM_COMMANDS
#include "pwm_commands.h"
#else
#define PWM_COMMANDS
#endif

#ifdef HAS_UART_COMMANDS
#include "uart_commands.h"
#else
#define UART_COMMANDS
#endif



#ifdef HAS_SYSTICK_COMMANDS
#include "systick_commands.h"
#else
#define SYSTICK_COMMANDS
#endif

#ifdef HAS_CLOCK_COMMANDS
#include "clock_commands.h"
#else
#define CLOCK_COMMANDS
#endif

#ifdef HAS_EXT_INT_COMMANDS
#include "ext_int_commands.h"
#else
#define EXT_INT_COMMANDS
#endif

#ifdef HAS_RTC_COMMANDS
#include "rtc_commands.h"
#else
#define RTC_COMMANDS
#endif

#ifdef HAS_QSPI_COMMANDS
#include "qspi_commands.h"
#else
#define QSPI_COMMANDS
#endif

#ifdef HAS_INPUT_CAPTURE_COMMANDS
#include "input_capture_commands.h"
#else
#define INPUT_CAPTURE_COMMANDS
#endif

#ifdef HAS_SWD_COMMANDS
#include "swd_commands.h"
#else
#define SWD_COMMANDS
#endif

#ifdef HAS_SDIO_COMMANDS
#include "sdio_commands.h"
#else
#define SDIO_COMMANDS
#endif

#ifdef HAS_IOMUX_COMMANDS
#include "iomux_commands.h"
#else
#define IOMUX_COMMANDS
#endif


#ifdef HAS_USB_COMMANDS
#include "usb_commands.h"
#else
#define USB_COMMANDS
#endif

#ifdef HAS_POWER_COMMANDS
#include "power_commands.h"
#else
#define POWER_COMMANDS
#endif


#define MCAL_CONTROL_COMMANDS         \
    POWER_COMMANDS                    \
    BOOT_MANAGER_COMMANDS             \
    DMA_COMMANDS                      \
    IOMUX_COMMANDS                    \
    GPIO_COMMANDS                     \
    PWM_COMMANDS                      \
    WATCHDOG_COMMANDS

#define MCAL_INTERFACE_COMMANDS         \
    SDIO_COMMANDS                       \
    QSPI_COMMANDS                       \
    I2C_COMMANDS                        \
    CAN_COMMANDS                        \
    I2S_COMMANDS                        \
    I2S_FULL_DUPLEX_COMMANDS            \
    SWD_COMMANDS                        \
    SPI_COMMANDS                        \
    SPIFI_COMMANDS                      \
    UART_COMMANDS                       \
    USB_COMMANDS

#define MCAL_CONNECTIVITY_COMMANDS      \
    MCAL_INTERFACE_COMMANDS

#define MCAL_SENSITIVITY_COMMANDS \
    ADC_COMMANDS                  \
    INPUT_CAPTURE_COMMANDS        \
    RTC_COMMANDS                  \
    TIMER_COMMANDS                \
    EXT_INT_COMMANDS              \
    SYSTICK_COMMANDS              \
    CLOCK_COMMANDS

#define MCAL_STORAGE_COMMANDS \
    EEPROM_COMMANDS           \
    FLASH_COMMANDS            \

#define MCAL_SECURITY_COMMANDS \
    CRYP_COMMANDS              \
    TRNG_COMMANDS

#define MCAL_COMMANDS            \
    MCAL_SENSITIVITY_COMMANDS    \
    MCAL_STORAGE_COMMANDS        \
    MCAL_SECURITY_COMMANDS       \
    MCAL_CONTROL_COMMANDS        \
    MCAL_CONNECTIVITY_COMMANDS



#endif /* MCAL_COMMANDS_H */
