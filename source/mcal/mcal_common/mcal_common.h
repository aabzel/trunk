#ifndef COMMON_MCAL_API_INCLUDES_H
#define COMMON_MCAL_API_INCLUDES_H

#ifdef __cplusplus
 extern "C" {
#endif

#ifdef HAS_ADC
#include "adc_mcal.h"
#endif

#ifdef HAS_CAN
#include "can_mcal.h"
#endif

#ifdef HAS_CORE
#include "core_driver.h"
#endif

#ifdef HAS_CRYP
#include "cryp_mcal.h"
#endif

#ifdef HAS_DMA
#include "dma_mcal.h"
#endif

#ifdef HAS_MAM
#include "mam_mcal.h"
#endif

#ifdef HAS_MPU
#include "mpu_mcal.h"
#endif

#ifdef HAS_DMA_CHANNEL
#include "dma_channel_mcal.h"
#endif

#ifdef HAS_EIM
#include "eim_mcal.h"
#endif

#ifdef HAS_ERM
#include "erm_mcal.h"
#endif

#ifdef HAS_EXT_INT
#include "ext_int_mcal.h"
#endif

#ifdef HAS_FCSMU
#include "fcsmu_mcal.h"
#endif

#ifdef HAS_GPIO
#include "gpio_mcal.h"
#endif

#ifdef HAS_I2C
#include "i2c_mcal.h"
#endif

#ifdef HAS_I2S
#include "i2s_mcal.h"
#endif

#ifdef HAS_INTERRUPT
#include "interrupt_mcal.h"
#endif

#ifdef HAS_LOCKSTEP
#include "flash_mcal.h"
#endif

#ifdef HAS_FLASH
#include "flash_mcal.h"
#endif

#ifdef HAS_MAILBOX
#include "mailbox_mcal.h"
#endif

#ifdef HAS_RTC
#include "rtc_mcal.h"
#endif

#ifdef HAS_SPI
#include "spi_mcal.h"
#endif

#ifdef HAS_SOFTWARE_TIMER
#include "software_timer.h"
#endif

#ifdef HAS_SDIO
#include "sdio_mcal.h"
#endif

#ifdef HAS_SYSTICK
#include "systick_mcal.h"
#endif

#ifdef HAS_TIMER
#include "timer_mcal.h"
#endif

#ifdef HAS_UART
#include "uart_mcal.h"
#endif

#ifdef HAS_USB
#include "usb_mcal.h"
#endif

#ifdef HAS_USB_DEVICE
#include "usbd_conf.h"
#endif

#ifdef HAS_USB_HOST
#include "usbh_conf.h"
#endif

#ifdef __cplusplus
}
#endif

#endif /* COMMON_MCAL_API_INCLUDES_H */
