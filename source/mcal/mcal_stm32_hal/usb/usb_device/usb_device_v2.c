#include "usb_device.h"

#include <ctype.h>
#include <stdio.h>

#include "data_utils.h"
#include "key_board_drv.h"
#include "keyboard_diag.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "usb_config.h"
#include "usb_drv.h"
#include "usbd_core.h"
#include "usbd_desc.h"

#include "usb_device_types.h"

#ifdef HAS_HID
#include "usbd_hid.h"
#endif

#ifdef HAS_MSC
#include "usbd_msc.h"
#include "usbd_storage_if.h"
#endif

/* USB Device Core handle declaration. */
// USBD_HandleTypeDef hUsbDeviceHS;

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

bool usb_device_init(void) {
    bool res = false;
    LOG_INFO(USB, "Device Init");
    set_log_level(HID, LOG_LEVEL_WARNING);
    USBD_StatusTypeDef ret = USBD_FAIL;
    UsbHandle_t* UsbNode = UsbGetNode(USB_DEVICE_NUM);
    if(UsbNode) {
        const UsbConfig_t* UsbConfNode = UsbGetConfNode(USB_DEVICE_NUM);
        if(UsbConfNode) {
            ret = USBD_Init(&UsbNode->hUsbDevice, &USB_Dev_Desc, UsbConfNode->speed);
            if(USBD_OK == ret) {
                LOG_INFO(USB, "DevInitOk");
                res = true;
            } else {
                res = false;
            }
        }
#ifdef HAS_HID
        if(res) {
            // ret = USBD_RegisterClass(&UsbNode->hUsbDevice, &USBD_CUSTOM_HID);
            ret = USBD_RegisterClass(&UsbNode->hUsbDevice, &USBD_HID);
            if(USBD_OK == ret) {
                LOG_INFO(HID, "RegisterHidOk");
                res = true;
            } else {
                res = false;
            }
        }
#endif /*HAS_HID*/

#ifdef HAS_MSC
        ret = USBD_RegisterClass(&UsbNode->hUsbDevice, &USBD_MSC);
        if(USBD_OK == ret) {
            LOG_INFO(USB, "RegMSCOk");
            res = true;
        } else {
            res = false;
        }
        if(res) {
            ret = USBD_MSC_RegisterStorage(&UsbNode->hUsbDevice, &USBD_Storage_Interface_fops_HS);
            if(USBD_OK == ret) {
                res = true;
                LOG_INFO(USB, "MSCRegStoreOk");
            } else {
                res = false;
            }
        }
#endif /*HAS_MSC*/

#if defined(HAS_MSC) && defined(HAS_HID)
        USBD_Init(&USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &USBD_MSC_HID_cb, &USR_cb);
        LOG_INFO(USB, "MSC+HIDRegStoreOk");
#endif /* HAS_MSC HAS_HID */
        if(res) {
            ret = USBD_Start(&UsbNode->hUsbDevice);
            if(USBD_OK == ret) {
                LOG_INFO(USB, "DevStartOk");
                res = true;
            } else {
                res = false;
            }
        }
    }
    return res;
}

bool HID_IsIdle(USBD_HandleTypeDef* pdev) {
    bool res = false;
    if(HID_IDLE == ((USBD_HID_HandleTypeDef*)pdev->pClassData)->state) {
        res = true;
    }
    return res;
}

#ifdef HAS_HID
bool usb_dev_send(KeyBoard_t* key_code) {
    bool res = false;
    LOG_DEBUG(HID, "SentKeyCode %s", KeyBoard2Str(key_code));
    UsbHandle_t* UsbNode = UsbGetNode(USB_DEVICE_NUM);
    if(UsbNode) {
        // uint8_t status=USBD_CUSTOM_HID_SendReport(&UsbNode->hUsbDevice,(uint8_t *) key_code, sizeof(KeyBoard_t));
        uint8_t status = USBD_HID_SendReport(&UsbNode->hUsbDevice, (uint8_t*)key_code, sizeof(KeyBoard_t));
        if(USBD_OK == status) {
            res = true;
        } else {
            res = false;
            LOG_ERROR(HID, "SendErr Status: %u=%s", status, UsbErr2Str(status));
        }
    }
    return res;
}
#endif

bool usb_keyboard_unpress(uint32_t time_out_ms) {
    bool res = false;
    KeyBoard_t key_code;
    memset(&key_code, 0, sizeof(KeyBoard_t));
    res = usb_dev_send(&key_code);
    if(false == res) {
        LOG_ERROR(KEYBOARD, "UnPressErr");
    }
    wait_ms(time_out_ms);
    return res;
}
#ifdef HAS_KEYBOARD
bool usb_dev_press_key(KeyBoard_t key_code, uint32_t wait_pause_ms) {
    bool res = false;
    LOG_DEBUG(KEYBOARD, "PressKey");
    res = false;
#ifdef HAS_HID
    res = usb_dev_send(&key_code);
    if(false == res) {
        LOG_ERROR(KEYBOARD, "PressErr");
    }
#endif

    wait_ms(wait_pause_ms);

    res = usb_keyboard_unpress(wait_pause_ms);
    return res;
}
#endif

bool usb_device_proc(void) {
    bool res = false;
    keyBoardCode.modifier.byte = 0x00;
    keyBoardCode.modifier.left_shift = 1,
    keyBoardCode.key_code[0] = 0x05; // Press B key
    keyBoardCode.key_code[1] = 0x06; // Press C key

    res = usb_dev_press_key(keyBoardCode, 50);

    return res;
}

#ifdef HAS_KEYBOARD
bool usb_key_board_press(uint8_t ascii_code, uint32_t time_out_ms) {
    bool res = false;
    keyBoardCode.modifier.byte = 0;
    LOG_DEBUG(KEYBOARD, "Press: [%c]=0x%02x", ascii_code, ascii_code);
    int ret = isupper(ascii_code);
    if(ret) {
        LOG_DEBUG(KEYBOARD, "UpperCase");
        keyBoardCode.modifier.left_shift = 1;
        ascii_code = tolower(ascii_code);
    }
    const KeyCodeInfo_t* KeyInfo = Ascii2KeyInfo(ascii_code);
    if(KeyInfo) {
        keyBoardCode.key_code[0] = KeyInfo->key_code;
        if(KeyInfo->is_upper_case) {
            LOG_DEBUG(KEYBOARD, "UpperCase");
            keyBoardCode.modifier.left_shift = 1;
        }
    } else {
        LOG_DEBUG(KEYBOARD, "Undef [%c] Error", ascii_code);
        keyBoardCode.key_code[0] = 0x38;
        keyBoardCode.modifier.left_shift = 1;
    }
    keyBoardCode.key_code[1] = 0x00;
    res = usb_dev_press_key(keyBoardCode, time_out_ms);
    if(false == res) {
        LOG_ERROR(KEYBOARD, "PushKeyErr");
    }
    return res;
}
#endif

bool usb_key_board_send_text(char* text, uint32_t time_out) {
    bool res = false;
    size_t len = strlen(text);
    if(len) {
        LOG_INFO(KEYBOARD, "SendText [%s] Len:%u", text, len);
        uint32_t i = 0;
        for(i = 0; i < len; i++) {
            res = usb_key_board_press(text[i], time_out); // 40
            if(false == res) {
                LOG_ERROR(KEYBOARD, "SendErr %u", text[i]);
            }
        }
    }
    return res;
}

bool usb_key_board_send_array(uint8_t* array, uint32_t size, uint32_t time_out) {
    bool res = false;
    if(array && size) {
        uint32_t i = 0;
        for(i = 0; i < size; i++) {
            res = usb_key_board_press(array[i], time_out); // 40
            if(false == res) {
                LOG_ERROR(KEYBOARD, "SendErr 0x%x=%c", array[i], array[i]);
            }
        }
    }
    return res;
}
