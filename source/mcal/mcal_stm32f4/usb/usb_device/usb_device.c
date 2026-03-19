#include "usb_device.h"

#include <ctype.h>
#include <stdio.h>

#include "data_utils.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "usb_device_types.h"
#include "usb_mcal.h"
#include "string_reader_const.h"
#include "usbd_cdc.h"
#include "usbd_core.h"
#include "code_generator.h"

#ifdef HAS_USB_FS
#include "usbd_fs_cdc_if.h"
#endif

#ifdef HAS_USB_HS
#include "usbd_hs_cdc_if.h"
#endif

#ifdef HAS_USB_SERIAL
#include "usb_serial.h"
#endif

#ifdef HAS_KEYBOARD
#include "key_board_drv.h"
#include "keyboard.h"
#endif

#ifdef HAS_PCAN_PRO
#include "usb_device_pcan_desc.h"
#include "pcanpro_usbd.h"
#endif

#ifdef HAS_HID
#include "usbd_hid.h"
#endif

#ifdef HAS_MSC
#include "usbd_msc.h"
#include "usbd_storage_if.h"
#endif

uint8_t usb_device_speed_to_id(const UsbSpeed_t speed) {
    uint8_t id = DEVICE_FS;
    switch (speed) {
        case USB_MCAL_SPEED_FS:
            id = DEVICE_FS;
            break;
        case USB_MCAL_SPEED_HS:
            id = DEVICE_HS;
            break;
        default:
            id = DEVICE_FS;
            break;
    }
    return id;
}

bool usb_device_status_to_res(const USBD_StatusTypeDef status) {
    bool res = false;
    switch (status) {
        case USBD_OK:
            res = true;
            break;
        case USBD_BUSY:
            res = false;
            break;
        case USBD_EMEM:
            res = false;
            break;
        case USBD_FAIL:
            res = false;
            break;
        default:
            res = false;
            break;
    }
    return res;
}

USBD_StatusTypeDef usb_device_res_to_ret(const bool res) {
    USBD_StatusTypeDef status = USBD_FAIL;
    if(res){
        status = USBD_OK;
    }
    return status;
}

/* USB Device Core handle declaration. */
// USBD_HandleTypeDef hUsbDeviceHS;
uint32_t key_insert_timeout_ms = BUTTON_INSERT_TIMEOUT_MS;

USBD_HandleTypeDef* UsbDeviceGetHandle(const uint8_t num) {
    USBD_HandleTypeDef *pHandle = NULL;
    UsbHandle_t *Node = UsbGetNode(num);
    if (Node) {
        pHandle = &Node->hUsbDevice;
    }
    return pHandle;
}

PCD_HandleTypeDef* UsbDeviceGetPcdHandle(const uint8_t num) {
    PCD_HandleTypeDef *pPcdHandle = NULL;
    UsbHandle_t *Node = UsbGetNode(num);
    if (Node) {
        pPcdHandle = &Node->PcdHandle;
    }
    return pPcdHandle;
}

#ifdef HAS_MSC
static bool usb_device_init_msd(UsbHandle_t *const Node) {
    bool res = false;
    USBD_StatusTypeDef status = USBD_FAIL;
    status = USBD_RegisterClass(&Node->hUsbDevice, &USBD_MSC);
    res = usb_device_status_to_res( status);
    if (res) {
        LOG_INFO(USB_DEVICE, "RegMSCOk");
        status = USBD_MSC_RegisterStorage(&Node->hUsbDevice, &USBD_Storage_Interface_fops_HS);
        res = usb_device_status_to_res( status);
        if (res) {
            LOG_INFO(USB_DEVICE, "MSCRegStoreOk");
        }
    }
    return res;
}
#endif

static bool usb_devise_register_class(UsbHandle_t* const Node) {
    bool res = false;
    USBD_StatusTypeDef status = USBD_FAIL;

#ifdef HAS_USB_SERIAL
    status = USBD_RegisterClass((USBD_HandleTypeDef*) &Node->hUsbDevice, &USBD_CDC);
#endif

#ifdef HAS_PCAN_PRO
    status = USBD_RegisterClass( &Node->hUsbDevice, &usbd_pcanpro ) ;
#endif
    res = usb_device_status_to_res(status);
    return res;
}

static bool usb_devise_register_interface(UsbHandle_t* const Node) {
    bool res = false;
    USBD_StatusTypeDef status = USBD_FAIL;

#ifdef HAS_USB_SERIAL

#ifdef HAS_USB_FS
    status = USBD_CDC_RegisterInterface(&Node->hUsbDevice, &USBD_Interface_fops_FS);
#endif

#ifdef HAS_USB_HS
    status = USBD_CDC_RegisterInterface(&Node->hUsbDevice, &USBD_Interface_fops_HS);
#endif

#endif

    res = usb_device_status_to_res(status);
    return res;
}

bool usb_device_proc_one(uint8_t num){
    bool res = false;
    LOG_PARN(USB_DEVICE, "Proc:%u", num);
#ifdef HAS_USB_SERIAL
    res = usb_serial_proc_one(num);
#endif
    return res;
}

bool usb_device_init(uint8_t num) {
    bool res = false;
    LOG_WARNING(USB_DEVICE, "Init:%u", num);
    USBD_StatusTypeDef status = USBD_FAIL;
    UsbHandle_t *Node = UsbGetNode(num);
    if (Node) {
        key_insert_timeout_ms = BUTTON_INSERT_TIMEOUT_MS;
        const UsbConfig_t *Config = UsbGetConfig(num);
        if (Config) {
            res = UsbIsValidConfig(Config);
        }

        if (res) {
            res = false;
            uint8_t id = usb_device_speed_to_id(Config->speed);
            if (Node->Descriptors) {
                status = USBD_Init((USBD_HandleTypeDef*) &Node->hUsbDevice,
                        (USBD_DescriptorsTypeDef*) Node->Descriptors, id);
                res = usb_device_status_to_res(status);
                if (res) {
                    LOG_INFO(USB_DEVICE, "DevInitOk");
                    res = true;
                }
            }
        }

        if (res) {
            res = usb_devise_register_class(Node);
        }
        if (res) {
            res = usb_devise_register_interface(Node);
        }

#ifdef HAS_HID
        bool usb_device_init_hid(Node);
#endif

#ifdef HAS_MSC
        res = usb_device_init_msd(Node);
#endif

#if defined(HAS_MSC) && defined(HAS_HID)
        USBD_Init(&USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &USBD_MSC_HID_cb, &USR_cb);
        LOG_INFO(USB_DEVICE, "MSC+HIDRegStoreOk");
#endif /* HAS_MSC HAS_HID */

#if 0
        status = USBD_Stop( &Node->hUsbDevice );
        res = usb_device_status_to_res( status);

        HAL_Delay( 1000 );
#endif

        if (res) {
            status = USBD_Start(&Node->hUsbDevice);
            res = usb_device_status_to_res(status);
            log_info_res(USB_DEVICE, res, "DevStart");
        }

#ifdef HAS_USB_SERIAL
        res = usb_serial_init_one(num);
#endif

    }
    return res;
}

#ifdef HAS_HID
bool HID_IsIdle(USBD_HandleTypeDef* pdev) {
    bool res = false;
    if(HID_IDLE == ((USBD_HID_HandleTypeDef*)pdev->pClassData)->state) {
        res = true;
    }
    return res;
}
#endif

