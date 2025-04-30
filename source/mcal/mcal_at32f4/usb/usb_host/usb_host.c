#include "usb_host.h"

#include "board_config.h"
#include "log.h"
#include "time_utils.h"
#include "usb_config.h"
#include "usb_drv.h"
#include "usbh_core.h"

#ifdef HAS_FREERTOS
#include "FreeRTOS.h"
#include "task.h"
#endif

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
    LOG_WARNING(USB_HOST, "Init");
    set_log_level(USB_HOST, LOG_LEVEL_DEBUG);
    USBH_StatusTypeDef ret;
    UsbHandle_t* Node = UsbGetNode(USB_HOST_NUM);
    if(Node) {
        const UsbConfig_t* Config = UsbGetConfNode(USB_HOST_NUM);
        if(Config) {
            /* Init host Library, add supported class and start the library. */
            // ret = USBH_Init(&Node->hUsbHost, USBH_UserProcess, HOST_HS Config->speed);
            ret = USBH_Init(&Node->hUsbHost, USBH_UserProcess, Config->host_speed);
            if(USBH_OK == ret) {
                LOG_INFO(USB_HOST, "InitOk");
                res = true;
            } else {
                LOG_ERROR(USB_HOST, "InitErr");
                res = false;
            }
        } else {
            LOG_ERROR(USB_HOST, "ConfigErr");
        }
#ifdef HAS_HID
        if(res) {
            ret = USBH_RegisterClass(&Node->hUsbHost, USBH_HID_CLASS);
            if(USBH_OK == ret) {
                res = true;
                LOG_INFO(USB_HOST, "RegisterClassOk");
            } else {
                LOG_ERROR(USB_HOST, "RegisterClassErr");
                res = false;
            }
        }
#endif
        if(res) {
            ret = USBH_Start(&Node->hUsbHost);
            if(USBH_OK == ret) {
                res = true;
                LOG_INFO(USB_HOST, "StartOk");
            } else {
                LOG_ERROR(USB_HOST, "StartErr");
                res = false;
            }
        }
    } else {
        LOG_ERROR(USB_HOST, "NodeErr");
    }

    set_log_level(USB_HOST, LOG_LEVEL_INFO);
    return res;
}

bool usb_host_process(void) {
    bool res = false;
    LOG_PARN(USB_HOST, "Proc");
    UsbHandle_t* Node = UsbGetNode(USB_HOST_NUM);
    if(Node) {
        USBH_HandleTypeDef* phost = &(Node->hUsbHost);
        if(phost) {
            USBH_StatusTypeDef ret = USBH_Process(phost);
            if(USBH_OK == ret) {
                res = true;
            } else {
                LOG_ERROR(USB_HOST, "ProcessErr: %u", ret);
            }
        } else {
            LOG_ERROR(USB_HOST, "HandleErr");
        }

        if(false == Node->host_init_done) {
            uint32_t cur = time_get_ms32();
            uint32_t time_out_ms = cur - Node->prev_init_ms;
            if(5000 < time_out_ms) {
                Node->prev_init_ms = time_get_ms32();
#ifdef HAS_MIC2026
                res = keyboard_reboot();
#endif
                res = usb_host_init();
            }
        }
    } else {
        LOG_ERROR(USB_HOST, "NodeErr %u", USB_HOST_NUM);
    }
    return res;
}

#ifdef HAS_FREERTOS
void usb_proc_task(void* argument) {
    for(;;) {
        // usb_host_process();
        vTaskDelay(1);
    }
}
#endif
