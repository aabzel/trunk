#ifndef USB_GENERAL_DRV_H
#define USB_GENERAL_DRV_H

#include <stdbool.h>

#ifdef HAS_STM32
#include "usb_custom_drv.h"
#endif /*HAS_STM32*/

#include "usb_config.h"
#include "usb_types.h"
#include "usb_diag.h"

bool usb_mcal_init(void);

#endif /* USB_GENERAL_DRV_H */
