#include "usb_drv.h"

#include "log.h"
#ifdef HAS_USB_DEVICE
#include "usb_device.h"
#endif


#ifdef HAS_USB
bool usb_init(void) {
    LOG_INFO(USB, "Init");
    bool res = false;

#ifdef HAS_USB_DEVICE
    res = usb_device_init();
#endif /*HAS_USB_DEVICE*/

    return res;
}
#endif /*HAS_USB*/




