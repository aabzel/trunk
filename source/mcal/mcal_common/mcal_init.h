#ifndef MCAL_INIT_H
#define MCAL_INIT_H

#ifndef HAS_MCAL
#error "+HAS_MCAL"
#endif

#ifdef HAS_ADC
#include "adc_mcal.h"
#define ADC_INIT {.init_function=adc_mcal_init, .name="ADC",}, \
  {.init_function=adc_channel_mcal_init, .name="AdcChannels",},
#else
#define ADC_INIT
#endif

#ifdef HAS_CRYP_HW
#include "cryp_custom_mcal.h"
#define CRYP_HW_INIT {.init_function=cryp_hw_init, .name="CrypHw",},
#else
#define CRYP_HW_INIT
#endif

#ifdef HAS_DMA
#include "dma_mcal.h"
#define DMA_INIT   \
  {.init_function=dma_mcal_init, .name="DMA",},       \
  {.init_function=dma_channel_mcal_init, .name="DmaChannels",},
#else
#define DMA_INIT
#endif

#ifdef HAS_FLASH
#include "flash_mcal.h"

#ifdef HAS_LOG
#define FLASH_INIT_NAME .name = "Flash",
#else
#define FLASH_INIT_NAME
#endif

#define FLASH_INIT {.init_function = flash_init, FLASH_INIT_NAME},
#else
#define FLASH_INIT
#endif

#ifdef HAS_GPIO
#include "gpio_mcal.h"

#ifdef HAS_LOG
#define GPIO_INIT_NAME .name = "GPIO",
#else
#define GPIO_INIT_NAME
#endif


#define GPIO_INIT {.init_function=gpio_mcal_init, GPIO_INIT_NAME},
#else
#define GPIO_INIT
#endif

#ifdef HAS_IOMUX
#include "iomux_mcal.h"
#define IOMUX_INIT {.init_function=iomux_mcal_init, .name="IoMux",},
#else
#define IOMUX_INIT
#endif


#ifdef HAS_I2C
#include "i2c_mcal.h"
#define I2C_INIT {.init_function=i2c_mcal_init, .name="I2C",},
#else
#define I2C_INIT
#endif

#ifdef HAS_I2S
#include "i2s_mcal.h"
#define I2S_INIT {.init_function=i2s_mcal_init, .name="I2S",},
#else
#define I2S_INIT
#endif

#ifdef HAS_I2S_FULL_DUPLEX
#include "i2s_full_duplex.h"
#define I2S_FULL_DUPLEX_INIT {.init_function=i2s_full_duplex_mcal_init, .name="I2sFullDuplex",},
#else
#define I2S_FULL_DUPLEX_INIT
#endif

#ifdef HAS_SPI
#include "spi_mcal.h"
#define SPI_INIT {.init_function=spi_mcal_init, .name="SPI",},
#else
#define SPI_INIT
#endif

#ifdef HAS_SPIFI
#include "spifi_mcal.h"

#ifdef HAS_LOG
#define SPIFI_INIT_NAME .name = "SPiFi",
#else
#define SPIFI_INIT_NAME
#endif

#define SPIFI_INIT {.init_function = spifi_mcal_init, SPIFI_INIT_NAME},
#else
#define SPIFI_INIT
#endif


#ifdef HAS_PWM_INIT
#include "pwm_mcal.h"
#define PWM_INIT {.init_function=pwm_mcal_init, .name="Pwm",},
#else
#define PWM_INIT
#endif /*HAS_PWM*/

#ifdef HAS_EXT_INT
#include "ext_int_mcal.h"
#define EXT_INT_INIT { .init_function=ext_int_mcal_init, .name="ExtInt",},
#else
#define EXT_INT_INIT
#endif /*HAS_EXT_INT*/

#ifdef HAS_TIMER
#include "timer_mcal.h"
#define TIMER_INIT  {.init_function=timer_mcal_init,  .name= "Timer",},
#else
#define TIMER_INIT
#endif /*HAS_TIM*/

#ifdef HAS_INTERRUPT
#include "interrupt_mcal.h"

#ifdef HAS_LOG
#define INTERRUPT_INIT_NAME .name = "Int",
#else
#define INTERRUPT_INIT_NAME
#endif

#define  INTERRUPT_INIT  {.init_function = interrupt_mcal_init, INTERRUPT_INIT_NAME },
#else
#define  INTERRUPT_INIT
#endif

#ifdef HAS_MPU
#include "mpu_mcal.h"
#define MPU_INIT {.init_function=mpu_mcal_init, .name="MNU",},
#else
#define MPU_INIT
#endif /*HAS_MPU*/

#ifdef HAS_MCU
#include "microcontroller_init.h"
#else
#define MICROCONTROLLER_INIT
#endif

#ifdef HAS_RTC
#include "rtc_mcal.h"
#define RTC_INIT {.init_function=rtc_mcal_init, .name="RTC",},
#else
#define RTC_INIT
#endif

#if defined(HAS_NORTOS) && defined(HAS_SYSTICK)
#include "systick_mcal.h"
#define SYSTICK_INIT {.init_function=systick_init, .name= "SysTick",},
#else
#define SYSTICK_INIT
#endif /*HAS_NORTOS and HAS_SYSTICK*/

#ifdef HAS_USB
#include "usb_mcal.h"
#define USB_INIT {.init_function=usb_mcal_init, .name="USB",},
#else
#define USB_INIT
#endif

#ifdef HAS_EEPROM
#include "eeprom_mcal.h"
#define EEPROM_INIT {.init_function=eeprom_mcal_init, .name="Eeprom",},
#else
#define EEPROM_INIT
#endif

#if defined(HAS_CLOCK) && defined(HAS_MICROCONTROLLER)
#include "clock/clock.h"

#ifdef HAS_LOG
#define CLOCK_INIT_NAME .name = "Clk",
#else
#define CLOCK_INIT_NAME
#endif

#define CLOCK_INIT {.init_function = clock_init, CLOCK_INIT_NAME},
#else
#define CLOCK_INIT
#endif

#ifdef HAS_QSPI
#include "qspi_mcal.h"
#define QSPI_INIT {.init_function=qspi_mcal_init, .name="QSPI",},
#else
#define QSPI_INIT
#endif /*HAS_QSPI*/

#ifdef HAS_SWD
#include "swd_mcal.h"
#define SWD_INIT {.init_function=swd_mcal_init, .name="Swd",},
#else
#define SWD_INIT
#endif

#ifdef HAS_SDIO
#include "sdio_mcal.h"
#define SDIO_INIT {.init_function=sdio_mcal_init, .name="SDIO",},
#else
#define SDIO_INIT
#endif

#ifdef HAS_PDM
#include "pdm_mcal.h"
#define PDM_INIT {.init_function=pdm_mcal_init, .name="Pdm",},
#else
#define PDM_INIT
#endif /*HAS_PDM*/

#ifdef HAS_POWER
#include "power_mcal.h"
#define POWER_INIT { .init_function  =power_mcal_init, .name="Power",},
#else
#define POWER_INIT
#endif /*HAS_POWER*/


#ifdef HAS_BOOT_MANAGER
#include "boot_manager.h"
#define BOOT_MANAGER_INIT { .init_function  =boot_manager_init, .name="BootManager",},
#else
#define BOOT_MANAGER_INIT
#endif /*HAS_POWER*/




#ifdef HAS_INPUT_CAPTURE
#include "input_capture_mcal.h"
#define INPUT_CAPTURE_INIT {.init_function=input_capture_mcal_init, .name="InputCapture",},
#else
#define INPUT_CAPTURE_INIT
#endif /*HAS_INPUT_CAPTURE*/

#ifdef HAS_WATCHDOG
#include "watchdog_mcal.h"
#define WATCHDOG_INIT {.init_function=watchdog_mcal_init, .name="WatchDog",},
#else
#define WATCHDOG_INIT
#endif /*HAS_WATCHDOG*/

#ifdef HAS_CAN
#include "can_mcal.h"
#define CAN_MCAL_INIT {.init_function=can_mcal_init, .name="CAN",},
#else
#define CAN_MCAL_INIT
#endif /*HAS_CAN*/

#ifdef HAS_IPC
#include "ipc_mcal.h"
#define IPC_INIT {.init_function=ipc_init, .name="IPC",},
#else
#define IPC_INIT
#endif

#ifdef HAS_HW_DAC
#include "dac_mcal.h"
#define HW_DAC_INIT {.init_function=dac_init, .name="DAC",},
#else
#define HW_DAC_INIT
#endif /*HAS_HW_DAC*/

#ifdef HAS_RNG
#include "rng_mcal.h"
#define RNG_INIT {.init_function=rng_init, .name="RNG",},
#else
#define RNG_INIT
#endif /*HAS_RNG*/

#ifdef HAS_UART
#include "uart_mcal.h"

#ifdef HAS_LOG
#define UART_INIT_NAME .name = "UART",
#else
#define UART_INIT_NAME
#endif

#define UART_INIT {.init_function=uart_mcal_init, UART_INIT_NAME},
#else
#define UART_INIT
#endif /*HAS_UART*/


/*Order matters*/
#define MCAL_INIT_CONTROL      \
    HW_DAC_INIT                \
    WATCHDOG_INIT              \
    MPU_INIT                   \
    PWM_INIT

/*Order matters*/
#define MCAL_WIRE_IF      \
    UART_INIT             \
    SWD_INIT              \
    QSPI_INIT             \
    SDIO_INIT             \
    I2C_INIT              \
    SPI_INIT              \
    CAN_MCAL_INIT         \
    USB_INIT              \
    I2S_INIT              \
    I2S_FULL_DUPLEX_INIT

/*Order matters*/
#define MCAL_INIT_SECURITY      \
    RNG_INIT                    \
    CRYP_HW_INIT




#define MCAL_INIT_SENSITIVITY         \
    EXT_INT_INIT                      \
    RTC_INIT                          \
    ADC_INIT                          \
    INPUT_CAPTURE_INIT                \
    PDM_INIT

/*Order matters*/
#define MCAL_INIT         \
    INTERRUPT_INIT        \
    CLOCK_INIT            \
    POWER_INIT            \
    SYSTICK_INIT          \
    GPIO_INIT             \
    IOMUX_INIT            \
    TIMER_INIT            \
    DMA_INIT              \
    EEPROM_INIT           \
    FLASH_INIT            \
    MCAL_WIRE_IF          \
    MCAL_INIT_SENSITIVITY \
    MCAL_INIT_SECURITY    \
    IPC_INIT              \
    SPIFI_INIT            \
    BOOT_MANAGER_INIT     \
    MCAL_INIT_CONTROL     \
    MICROCONTROLLER_INIT


#endif /* MCAL_INIT_H */
