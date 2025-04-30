
#include "usb_drv.h"

#include "log.h"

#ifdef HAS_USB_AUDIO
#include "audio_usb.h"
#endif

bool usb_init(void){
    bool res = false;
    LOG_INFO(USB, "Init");
#ifdef HAS_USB_AUDIO
    int ret = -1;
#if (CONFIG_AUDIO_DEV==GATEWAY)
    ret = audio_usb_init();
#endif
    if(0==ret) {
        LOG_INFO(USB_AUDIO, "InitOk");
        res = true;
    } else {
        LOG_ERROR(USB_AUDIO, "InitErr %d", ret);
        res = false;
    }
#endif

    return res;
}

