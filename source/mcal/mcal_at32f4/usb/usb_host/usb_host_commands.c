#include "usb_host_commands.h"


#include <string.h>

#include "usb_host_diag.h"
#include "usbh_hid.h"
#include "usbh_def.h"
#include "usb_drv.h"
#include "usb_host.h"
#include "array.h"
#include "convert.h"
#include "none_blocking_pause.h"

bool usb_host_init_command(int32_t argc, char* argv[]){
    bool res = false;
    res = usb_host_init();
    return res;
}

bool usb_host_diag_command(int32_t argc, char* argv[]){
    bool res = false;
    res = usb_host_diag();
    return res;
}

/*
uhls 0 1
uhls 0 7
uhls 2 7
uhls 3 7
uhls 1 7 ->100
uhls 0 5 ->000
uhls 1 2
uhls 1 3
uhls 2 3
uhls 2 7
uhls 3 1
uhls 1 7 ->100
uhls 7 2
uhls 0xff
uhls 0xf6
uhls 0xff 1
uhls 0 4
uhls 0 7
uhls 1
uhls 3
uhls 7
*/
bool usb_host_led_set_command(int32_t argc, char* argv[]){
    bool res = false;

    uint8_t kbd_led[2] = { 0x00, 0x00 };
    uint8_t size = 0;

    if(1<=argc){
        res = try_str2uint8(argv[0], &kbd_led[0]);
        if(res){
            size = 1;
        }
    }

    if(2<=argc){
        res = try_str2uint8(argv[1], &kbd_led[1]);
        if(res){
            size = 2;
        }
    }

    if(res) {
        UsbHandle_t* Node = UsbGetNode(USB_HOST_NUM);
        if(Node) {
            USBH_HandleTypeDef* phost = &(Node->hUsbHost);
            if(phost) {
                LOG_INFO(USB_HOST,"Size:%u,   %x,%x",size,kbd_led[0],kbd_led[1]);
                USBH_StatusTypeDef status = USBH_BUSY;
                while(USBH_OK!=status) {
	    			status = USBH_HID_SetReport(phost, 2, 0, kbd_led, size);
                    res = wait_in_loop_ms(10);
                }
                LOG_INFO(USB_HOST, "%s", UsbHostStatus2Str(status));
                LOG_INFO(USB_HOST,"Done Size:%u,   %x,%x",size,kbd_led[0],kbd_led[1]);
                //USBH_StatusTypeDef status = USBH_Set_Report(pdev,phost,0x02,0x00,0x01,&c);
            }
        }
    }else{
        LOG_ERROR(USB_HOST,"Usage: uhls Config");
    }
    return res;
}

/*
 uhlg 2
 */

static bool hid_keyboard_led_get_test(uint8_t rep_type, uint8_t rep_id, uint8_t size){
	  bool res = false;

	  if(size<4) {
		  if((0x51==rep_id)||(0x53==rep_id)||(0x5e==rep_id)
				  ||(0x55==rep_id)||(0x58==rep_id)||(0x59==rep_id)) {
			  return false; //KeyBoard reconnect
		  }
		  if(0x56==rep_id) {
			  return false; //KeyBoard reconnect
		  }
		  if(0x52==rep_id) {
			  return false; //KeyBoard reconnect
		  }
		  if(0x54==rep_id) {
			  return false; //KeyBoard reconnect
		  }
	  LOG_DEBUG(USB_HOST,"Type:0x%x,Id:0x%x,Size:%u",rep_type,rep_id,size);
          uint8_t arr[4];
          memset(arr,0,sizeof(arr));
          UsbHandle_t* Node = UsbGetNode(USB_HOST_NUM);
          if(Node) {
              USBH_HandleTypeDef* phost = &(Node->hUsbHost);
              if(phost) {
            	  uint32_t wait_ms = 0;
                  USBH_StatusTypeDef status = USBH_BUSY;
                  while(USBH_OK!=status) {
    	    	      status = USBH_HID_GetReport(phost, rep_type, rep_id, arr, size);
                      wait_in_loop_ms(10);
                      wait_ms += 10;

                      if (4000 < wait_ms ) {
                    	  LOG_ERROR(USB_HOST, "TimeOut");
                    	  break;
                      }
                  }

                  if(USBH_OK==status) {
                      uint32_t sum = arr_sum(arr, size);
                      if(sum) {
                          LOG_INFO(USB_HOST,"SpotData: Size:%u,   %x,%x",size,arr[0],arr[1]);
                          //LOG_INFO(USB_HOST, "%s", UsbHostStatus2Str(status));
                          res = true;
                      }else{
                    	  res = false;
                      }
                  }
              }
          }
	  }
	  return res;
}

bool usb_host_led_get_test_command(int32_t argc, char* argv[]){
	bool res = false;
	uint8_t size = 1;
	uint16_t rep_type = 1;
	uint16_t rep_id = 0;

    if(0<=argc) {
    	size = 1;
    }

    if(1<=argc) {
        res = try_str2uint8(argv[0], &size);
    }

    if(2<=argc) {
        res = try_str2uint16(argv[1], &rep_type);
    }

    for(;rep_type<=0xFF;rep_type++){
    	for(rep_id=0;rep_id<=0xFF;rep_id++){
            res = hid_keyboard_led_get_test((uint8_t) rep_type,( uint8_t) rep_id, size);
            if(res){
            	LOG_INFO(USB_HOST,"Type:0x%x,Id:0x%x",rep_type,rep_id);
            }
    	}
    }

    if(false==res) {
        LOG_ERROR(USB_HOST,"Usage: uhlgt size TypeStart");
    }
	return res;
}

bool usb_host_led_get_command(int32_t argc, char* argv[]){
    bool res = true;

    uint8_t kbd_led[2] = { 0x00, 0x00 };
    uint8_t size = 1;

    if(0<=argc) {
    	size = 1;
    }

    if(1<=argc){
        res = try_str2uint8(argv[0], &size);
    }

    if(res) {
        LOG_INFO(USB_HOST, "TryGetLed Size %u...",size);
        UsbHandle_t* Node = UsbGetNode(USB_HOST_NUM);
        if(Node) {
            USBH_HandleTypeDef* phost = &(Node->hUsbHost);
            if(phost) {
            	uint32_t timeout_ms = 0 ;
                USBH_StatusTypeDef status = USBH_BUSY;
                while(USBH_OK!=status) {
	    			status = USBH_HID_GetReport(phost, 2, 0, kbd_led, size);
                    res = wait_in_loop_ms(10);
                    timeout_ms += 10;
                    if(10000 < timeout_ms){
                    	break;
                    }
                }
                LOG_INFO(USB_HOST,"Size:%u,   0x%x,0x%x",size,kbd_led[0],kbd_led[1]);
                LOG_INFO(USB_HOST, "Status:%s", UsbHostStatus2Str(status));
            }
        }
    }else{
        LOG_ERROR(USB_HOST,"Usage: uhlg");
    }
    return res;
}

bool usb_host_led_test_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t i=0;
    uint32_t j=0;
    for(i=1; i<=0xb; i++) {
        for(j=0; j<255; j++) {
            UsbHandle_t* Node = UsbGetNode(USB_HOST_NUM);
            if(Node) {
                USBH_HandleTypeDef* phost = &(Node->hUsbHost);
                if(phost) {
                    uint8_t kbd_led[2] = { i, j };
                    LOG_DEBUG(USB_HOST,"Size:%u,   0x%x,0x%x",2,kbd_led[0],kbd_led[1]);
                    USBH_StatusTypeDef status = USBH_HID_SetReport(phost, 2, 0, kbd_led, 2);
                    if(USBH_OK==status){
                        LOG_INFO(USB_HOST,"Size:%u,   0x%x,0x%x",2,kbd_led[0],kbd_led[1]);
                        LOG_INFO(USB_HOST, "%s", UsbHostStatus2Str(status));
                    }
                    //USBH_StatusTypeDef status = USBH_Set_Report(pdev,phost,0x02,0x00,0x01,&c);
                    res = wait_in_loop_ms(100);
                }
            }
        }
    }
    return res;
}
