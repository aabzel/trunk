#include "usb_host_diag.h"

#include <stdio.h>

#include "array_diag.h"
#include "usb_host.h"
#include "usb_mcal.h"
#include "usbh_def.h"
#include "usbh_hid_keybd.h"

const char* UsbHostSpeed2Str(USBH_SpeedTypeDef usbh_speed) {
    const char* name = "?";
    switch((uint8_t)usbh_speed) {
    case USBH_SPEED_HIGH:
        name = "Hi";
        break;
    case USBH_SPEED_LOW:
        name = "Low";
        break;
    case USBH_SPEED_FULL:
        name = "Full";
        break;
    }
    return name;
}

const char* UsbHidType2Str(HID_TypeTypeDef hid_type) {
    const char* name = "?";
    switch((uint8_t)hid_type) {
    case HID_MOUSE:
        name = "Mouse";
        break;
    case HID_KEYBOARD:
        name = "KeyBoard";
        break;
    }
    return name;
}

const char* KeyBoardInfo2Str(const HID_KEYBD_Info_TypeDef* const Node) {
    static char name[20];
    if(Node) {
        snprintf(name, sizeof(name), "state:%u,lctrl:%u,lshift:%u,lalt:%u,lgui:%u,rctrl:%u,rshift:%u,ralt:%u,rgui:%u",
                 Node->state, Node->lctrl, Node->lshift, Node->lalt, Node->lgui, Node->rctrl, Node->rshift, Node->ralt,
                 Node->rgui);
    }
    return name;
}

const char* UsbHostStatus2Str(USBH_StatusTypeDef status) {
    const char* name = "?";
    switch((uint8_t)status) {
    case USBH_OK:
        name = "Ok";
        break;
    case USBH_BUSY:
        name = "Busy";
        break;
    case USBH_FAIL:
        name = "FAIL";
        break;
    case USBH_NOT_SUPPORTED:
        name = "NOT_SUPPORTED";
        break;
    case USBH_UNRECOVERED_ERROR:
        name = "UNRECOVERED_ERROR";
        break;
    case USBH_ERROR_SPEED_UNKNOWN:
        name = "ERROR_SPEED_UNKNOWN";
        break;
    }
    return name;
}

bool usb_host_diag(void) {
    bool res = false;
    LOG_INFO(USB_HOST, "Diag");
    UsbHandle_t* Node = UsbGetNode(USB_HOST_NUM);
    if(Node) {
        USBH_HandleTypeDef* phost = &(Node->hUsbHost);
        if(phost) {
            uint8_t kbd_led[2] = {0x00, 0x00};
            USBH_StatusTypeDef status = USBH_HID_GetReport(phost, 0x02U, 0, (uint8_t*)kbd_led, sizeof(kbd_led));
            LOG_INFO(USB_HOST, "%s", UsbHostStatus2Str(status));
            res = array_i8_print((int8_t*)kbd_led, 2);

            HID_TypeTypeDef hid_type = USBH_HID_GetDeviceType(phost);
            LOG_INFO(USB_HOST, "HidType: %s", UsbHidType2Str(hid_type));

            USBH_SpeedTypeDef usbh_speed = USBH_LL_GetSpeed(phost);
            LOG_INFO(USB_HOST, "%s", UsbHostSpeed2Str(usbh_speed));
            // uint8_t pipe = 0;
            // uint8_t toggle USBH_LL_GetToggle(phost, pipe);
            // uint8_t pipe = 0;
            // uint32_t packet_size = USBH_LL_GetLastXferSize(phost, pipe);

            HID_KEYBD_Info_TypeDef* KeyBoardNode = USBH_HID_GetKeybdInfo(phost);
            if(KeyBoardNode) {
                LOG_INFO(USB_HOST, "%s", KeyBoardInfo2Str(KeyBoardNode));
                res = array_i8_print((int8_t*)KeyBoardNode->keys, 8);
            }

            status = USBH_Get_StringDesc(phost, phost->device.DevDesc.iManufacturer, phost->device.Data, 0xFFU);
            LOG_INFO(USB_HOST, "%s", UsbHostStatus2Str(status));
            res = true;
        }
    }

    return res;
}
