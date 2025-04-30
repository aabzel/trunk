#ifndef COMMON_MCAL_API_INCLUDES_H
#define COMMON_MCAL_API_INCLUDES_H

#ifdef __cplusplus
 extern "C" {
#endif


#ifdef HAS_ADC
#include "adc_mcal.h"
#endif /*HAS_ADC*/

#ifdef HAS_CAN
#include "can_mcal.h"
#endif /*HAS_CAN*/

#ifdef HAS_CORE
#include "core_driver.h"
#endif

#ifdef HAS_CRYP
#include "cryp_api.h"
#include "cryp_config.h"
#endif

#ifdef HAS_DMA
#include "dma_mcal.h"
#endif /*HAS_DMA*/

#ifdef HAS_EXT_INT
#include "ext_int_mcal.h"
#endif /*HAS_EXT_INT*/

#ifdef HAS_GPIO
#include "gpio_mcal.h"
#endif /*HAS_GPIO*/

#ifdef HAS_I2C
#include "i2c_mcal.h"
#endif /*HAS_I2C*/

#ifdef HAS_I2S
#include "i2s_mcal.h"
#endif /*HAS_I2S*/

#ifdef HAS_INTERRUPT
#include "interrupt_mcal.h"
#endif

#ifdef HAS_RTC
#include "rtc_mcal.h"
#endif /*HAS_RTC*/

#ifdef HAS_SPI
#include "spi_mcal.h"
#endif /*HAS_SPI*/

#ifdef HAS_SOFTWARE_TIMER
#include "software_timer.h"
#endif /*HAS_SOFTWARE_TIMER*/

#ifdef HAS_SDIO
#include "sdio_mcal.h"
#endif /*HAS_SDIO*/

#ifdef HAS_SYSTICK
#include "systick_mcal.h"
#endif /*HAS_SYS_TICK*/

#ifdef HAS_TIMER
#include "timer_mcal.h"
#endif /*HAS_TIMER*/

#ifdef HAS_UART
#include "uart_mcal.h"
#endif /*HAS_UART*/

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
