#include "usb_config.h"

#include "data_utils.h"
#include "usb_types.h"
#include "usb_const.h"

#ifdef HAS_USB_DEVICE
#include "usbd_conf.h"
#include "usbd_fs_desc_serial.h"
#endif

static uint8_t TxArrayStaticMem[1204]={0};

const UsbConfig_t UsbConfig[] = {
#ifdef HAS_USB_DEVICE
      {
        .num = USB_DEVICE_NUM,
        .role = USB_MCAL_ROLE_DEVICE,
        .valid = true,
        .TxFifoArray = TxArrayStaticMem,
        .tx_buff_size = ARRAY_SIZE(TxArrayStaticMem),
        .interrupt_on = true,
        .name = "VirvualComPort",
        .Descriptors = &FS_Desc,
        .speed = USB_MCAL_SPEED_FS,
        .device_speed = USB_DEVICE_SPEED_FS,

        .PadDP={.port=PORT_A, .pin=12,},
        .PadDM={.port=PORT_A, .pin=11,},


      },
#endif /*HAS_USB_DEVICE*/

#ifdef HAS_USB_HOST
    { .num = USB_HOST_NUM,
      .valid = true,
      .name = "Host",
      .interrupt_on = true,
      .role = USB_MCAL_ROLE_HOST,
      .speed = USB_MCAL_SPEED_FS,
	  .host_speed = USB_HOST_SPEED_FS,
      .PadDP={.port=PORT_?, .pin=?,},
      .PadDM={.port=PORT_?, .pin=?,},
    },
#endif
};

UsbHandle_t UsbInstance[] = {
#ifdef HAS_USB_DEVICE
        {
         .num = USB_DEVICE_NUM,
         .valid = true, 
         .speed = USB_MCAL_SPEED_FS,
         .device_speed = USB_DEVICE_SPEED_FS,
         .role = USB_MCAL_ROLE_DEVICE,
        },
#endif

#ifdef HAS_USB_HOST
        {
         .num = USB_HOST_NUM,
         .valid = true,
         .speed = USB_MCAL_SPEED_FS,
         .host_speed = USB_HOST_SPEED_FS,
         .role = USB_MCAL_ROLE_HOST,
        },
#endif
};

COMPONENT_GET_CNT(Usb, usb)

