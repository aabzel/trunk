#ifndef USB_HOST_DRV_H
#define USB_HOST_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "stm32f4xx.h"
#include "artery_at32f4xx.h"

#include "usb_config.h"

#ifdef HAS_USB_HOST_DIAG
#include "usb_host_diag.h"
#endif

#include "usb_host_const.h"

bool usb_host_init(void);
bool usb_host_process(void);
void usb_proc_task(void* argument);

#ifdef __cplusplus
}
#endif

#endif /* USB_HOST_DRV_H */
