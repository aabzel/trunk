#include "usb_device_diag.h"

#include "usb_mcal.h"
//#include "usbd_def.h"

const char* UsbDeviceErrToStr(const USBD_StatusTypeDef status) {
    const char* name = "?";
    switch(status) {
    case USBD_OK:
        name = "OK";
        break;
    case USBD_BUSY:
        name = "BUSY";
        break;
    case USBD_EMEM:
        name = "EMEM";
        break;
    case USBD_FAIL:
        name = "FAIL";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

bool UsbDeviveDiag(const USBD_HandleTypeDef* const Node) {
    bool res = false;
    if(Node) {
        LOG_INFO(USB_DEVICE, "Id:%u", Node->id);
        LOG_INFO(USB_DEVICE, "DevConfig:%u", Node->dev_config);
        LOG_INFO(USB_DEVICE, "DevDefault_config:%u", Node->dev_default_config);
        LOG_INFO(USB_DEVICE, "DevConfig_status:%u", Node->dev_config_status);
        LOG_INFO(USB_DEVICE, "DevSpeed:%u", Node->dev_speed);
        LOG_INFO(USB_DEVICE, "ep0State:%u", Node->ep0_state);
        LOG_INFO(USB_DEVICE, "ep0Data_len:%u", Node->ep0_data_len);
        LOG_INFO(USB_DEVICE, "DevState:%u", Node->dev_state);
        LOG_INFO(USB_DEVICE, "DevOldState:%u", Node->dev_old_state);
        LOG_INFO(USB_DEVICE, "Devaddress:%u", Node->dev_address);
        LOG_INFO(USB_DEVICE, "Devconnection_status:%u", Node->dev_connection_status);
        LOG_INFO(USB_DEVICE, "Devtest_mode:%u", Node->dev_test_mode);
        LOG_INFO(USB_DEVICE, "Devremote_wakeup:%u", Node->dev_remote_wakeup);
        // LOG_INFO(USB_DEVICE, "classId:%u", Node->classId);
        LOG_INFO(USB_DEVICE, "ConfIdx:%u", Node->ConfIdx);
        //    LOG_INFO(USB_DEVICE, "NumClasses:%u", Node->NumClasses);
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
