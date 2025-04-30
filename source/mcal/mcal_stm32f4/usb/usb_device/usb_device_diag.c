#include "usb_device_diag.h"

#include "usb_mcal.h"
//#include "usbd_def.h"

#if 0
const char* UsbErr2Str(uint8_t status) {
    const char* name = "?";
    switch(status) {
    case USBD_OK:
        name = "USBD_OK";
        break;
    case USBD_BUSY:
        name = "USBD_BUSY";
        break;
    case USBD_FAIL:
        name = "USBD_FAIL";
        break;
    }
    return name;
}
#endif

bool UsbDeviveDiag(const USBD_HandleTypeDef* const UsbDeviceNode) {
    bool res = false;
    if(UsbDeviceNode) {
        LOG_INFO(HID, "Id:%u", UsbDeviceNode->id);
        LOG_INFO(HID, "DevConfig:%u", UsbDeviceNode->dev_config);
        LOG_INFO(HID, "DevDefault_config:%u", UsbDeviceNode->dev_default_config);
        LOG_INFO(HID, "DevConfig_status:%u", UsbDeviceNode->dev_config_status);
        LOG_INFO(HID, "DevSpeed:%u", UsbDeviceNode->dev_speed);
        LOG_INFO(HID, "ep0State:%u", UsbDeviceNode->ep0_state);
        LOG_INFO(HID, "ep0Data_len:%u", UsbDeviceNode->ep0_data_len);
        LOG_INFO(HID, "DevState:%u", UsbDeviceNode->dev_state);
        LOG_INFO(HID, "DevOldState:%u", UsbDeviceNode->dev_old_state);
        LOG_INFO(HID, "Devaddress:%u", UsbDeviceNode->dev_address);
        LOG_INFO(HID, "Devconnection_status:%u", UsbDeviceNode->dev_connection_status);
        LOG_INFO(HID, "Devtest_mode:%u", UsbDeviceNode->dev_test_mode);
        LOG_INFO(HID, "Devremote_wakeup:%u", UsbDeviceNode->dev_remote_wakeup);
        LOG_INFO(HID, "classId:%u", UsbDeviceNode->classId);
        LOG_INFO(HID, "ConfIdx:%u", UsbDeviceNode->ConfIdx);
        LOG_INFO(HID, "NumClasses:%u", UsbDeviceNode->NumClasses);
        //  USBD_SetupReqTypedef    request;
        // USBD_DescriptorsTypeDef *pDesc;
        // USBD_ClassTypeDef       *pClass[USBD_MAX_SUPPORTED_CLASS];
    }
    return res;
}

bool usb_device_diag(void) {
    bool res = false;
    UsbHandle_t* Node = UsbGetNode(USB_DEVICE_NUM);
    if(Node) {
        res = UsbDeviveDiag(&Node->hUsbDevice);
    }

    return res;
}
