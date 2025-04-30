#include "usb_host.h"

#include "log.h"
#include "usb_config.h"
#include "usb_drv.h"
#include "usbh_core.h"

#ifdef HAS_HID
#include "usbh_hid.h"
#endif

ApplicationTypeDef Appli_state = APPLICATION_IDLE;

static void USBH_UserProcess(USBH_HandleTypeDef* phost, uint8_t id) {
    /* USER CODE BEGIN CALL_BACK_1 */
    switch(id) {
    case HOST_USER_SELECT_CONFIGURATION:
        break;

    case HOST_USER_DISCONNECTION:
        Appli_state = APPLICATION_DISCONNECT;
        break;

    case HOST_USER_CLASS_ACTIVE:
        Appli_state = APPLICATION_READY;
        break;

    case HOST_USER_CONNECTION:
        Appli_state = APPLICATION_START;
        break;

    default:
        break;
    }
}

bool usb_host_init(void) {
    bool res = false;
    LOG_INFO(USB, "Host Init");
    set_log_level(USB_HOST, LOG_LEVEL_WARNING);
    USBH_StatusTypeDef ret;
    UsbHandle_t* UsbNode = UsbGetNode(USB_HOST_NUM);
    if(UsbNode) {
        const UsbConfig_t* UsbConfNode = UsbGetConfNode(USB_HOST_NUM);
        /* Init host Library, add supported class and start the library. */
        // ret = USBH_Init(&UsbNode->hUsbHost, USBH_UserProcess, HOST_HS UsbConfNode->speed);
        ret = USBH_Init(&UsbNode->hUsbHost, USBH_UserProcess, UsbConfNode->host_speed);
        if(USBH_OK == ret) {
            res = true;
        } else {
            res = false;
        }
#ifdef HAS_HID
        if(res) {
            ret = USBH_RegisterClass(&UsbNode->hUsbHost, USBH_HID_CLASS);
            if(USBH_OK == ret) {
                res = true;
            } else {
                res = false;
            }
        }
#endif
        if(res) {
            ret = USBH_Start(&UsbNode->hUsbHost);
            if(USBH_OK == ret) {
                res = true;
            } else {
                res = false;
            }
        }
    } else {
        LOG_ERROR(USB, "NodeErr");
    }
    return res;
}

bool usb_host_process(void) {
    bool res = true;
    UsbHandle_t* UsbNode = UsbGetNode(USB_HOST_NUM);
    if(UsbNode) {
        USBH_HandleTypeDef* phost = &(UsbNode->hUsbHost);
        if(phost) {
            USBH_Process(phost);
        }
    }
    return res;
}
