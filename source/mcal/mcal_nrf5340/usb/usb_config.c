#include "usb_config.h"

#include "data_utils.h"
#include "usb_types.h"

const UsbConfig_t UsbConfig[]= {
#ifdef HAS_USB_DEVICE
		{ .usb_num=1, .valid = true, .name="Device",
		},
#endif /*HAS_USB_DEVICE*/

};

UsbHandle_t UsbInstance[]={
#ifdef HAS_USB_DEVICE
		{.usb_num=1, .valid = true,},
#endif
};

uint32_t usb_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(UsbConfig);
    cnt2 = ARRAY_SIZE(UsbInstance);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
}

