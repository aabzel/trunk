#include "usb_device_diag.h"

#include "usbd_def.h"
#include "usb_drv.h"
#include "usb_device.h"
#include "debug_info.h"
#include "usbd_customhid.h"
//#include "usbd_def.h"

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

bool UsbDeviveDiag(const USBD_HandleTypeDef* const DeviceNode){
	bool res = false;
	if(DeviceNode){
	    LOG_INFO(HID, "Id %u", DeviceNode->id);
	    LOG_INFO(HID, "dev_config %u", DeviceNode->dev_config);
	    LOG_INFO(HID, "dev_default_config %u", DeviceNode->dev_default_config);
	    LOG_INFO(HID, "dev_config_status %u", DeviceNode->dev_config_status);
	    LOG_INFO(HID, "dev_speed %u", DeviceNode->dev_speed);
	    LOG_INFO(HID, "ep0_state %u", DeviceNode->ep0_state);
	    LOG_INFO(HID, "ep0_data_len %u", DeviceNode->ep0_data_len);
	    LOG_INFO(HID, "dev_state %u", DeviceNode->dev_state);
	    LOG_INFO(HID, "dev_old_state %u", DeviceNode->dev_old_state);
	    LOG_INFO(HID, "dev_address %u", DeviceNode->dev_address);
	    LOG_INFO(HID, "dev_connection_status %u", DeviceNode->dev_connection_status);
	    LOG_INFO(HID, "dev_test_mode %u", DeviceNode->dev_test_mode);
	    LOG_INFO(HID, "dev_remote_wakeup %u", DeviceNode->dev_remote_wakeup);
	    LOG_INFO(HID, "classId %u", DeviceNode->classId);
	    LOG_INFO(HID, "ConfIdx %u", DeviceNode->ConfIdx);
	    LOG_INFO(HID, "NumClasses %u", DeviceNode->NumClasses);


		HAL_StatusTypeDef ret=HAL_ERROR;
		ret = HAL_PCD_EP_Receive(DeviceNode->pData, CUSTOM_HID_EPOUT_ADDR, rx_buf, CUSTOM_HID_EPOUT_SIZE);
		if (HAL_OK==ret) {
			print_hex(rx_buf,   CUSTOM_HID_EPOUT_SIZE);
			res = true;
		}else{
			res = false;
		}

//  USBD_SetupReqTypedef    request;
  //USBD_DescriptorsTypeDef *pDesc;
 // USBD_ClassTypeDef       *pClass[USBD_MAX_SUPPORTED_CLASS];
	}
    return res;
}

bool usb_device_diag(void){
	bool res = false;
    UsbHandle_t* Node = UsbGetNode(USB_DEVICE_NUM);
    if(Node) {
        res=UsbDeviveDiag(&Node->hUsbDevice);
    }


	return res;
}
