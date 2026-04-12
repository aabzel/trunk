#include "usb_config.h"

#include "data_utils.h"
#include "usb_types.h"
#include "usb_const.h"

#ifdef HAS_USB_DEVICE
#include "usbd_conf.h"
#include "usbd_desc.h"

#ifdef HAS_HID
#include "usbd_hid.h"
#endif /*HAS_HID*/

#endif /*HAS_USB_DEVICE*/

const UsbConfig_t UsbConfig[]= {
#ifdef HAS_USB_DEVICE
      { .num=USB_DEVICE_NUM,
        .valid = true,
        .name="Device",
        .hs_desc=&USB_Dev_Desc,
        .speed=USB_SPEED_HS,
		.device_speed = USB_DEVICE_SPEED_HS,
        .role=USB_ROLE_DEVICE,
#ifdef HAS_HID
        .usbd_hid=&USBD_HID,
#endif /*HAS_HID*/
      },
#endif /*HAS_USB_DEVICE*/

#ifdef HAS_USB_HOST
    { .num = USB_HOST_NUM,
      .valid = true,
      .name = "Host",
      .role = USB_ROLE_HOST,
      .speed = USB_SPEED_FS,
	  .host_speed = USB_HOST_SPEED_FS,
    },
#endif
};

UsbHandle_t UsbInstance[]={
#ifdef HAS_USB_DEVICE
        {.num=USB_DEVICE_NUM, 
         .valid = true, 
         .speed = USB_SPEED_HS,
         .device_speed = USB_DEVICE_SPEED_HS,
         .role=USB_ROLE_DEVICE,},
#endif

#ifdef HAS_USB_HOST
        {.num=USB_HOST_NUM,
         .valid = true,
         .speed = USB_SPEED_FS,
         .host_speed = USB_HOST_SPEED_FS,
         .role=USB_ROLE_HOST,},
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
    assert_param(2==cnt);
    return cnt;
}

