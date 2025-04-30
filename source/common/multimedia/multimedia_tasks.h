#ifndef MULTIMEDIA_TASKS_H
#define MULTIMEDIA_TASKS_H

#ifdef HAS_USB_TO_I2S
#include "usb_to_i2s_drv.h"
#define USB_TO_I2S_TASKS {.name="USB_TO_I2S", .period_us=USB_TO_I2S_PERIOD_US, .limiter.function=usb_to_i2s_proc,},
#else
#define USB_TO_I2S_TASKS
#endif


#define MULTIMEDIA_TASKS   \
    USB_TO_I2S_TASKS




#endif /* MULTIMEDIA_TASKS_H */
