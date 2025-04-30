#include "usb_hid.h"

#include <string.h>

#include "log.h"
#ifdef HAS_KEYBOARD
#include "keyboard.h"
#endif
//#include "fifo_array.h"
#include "fifo_char.h"
#ifdef HAS_TBFP
#include "tbfp_protocol.h"
#endif
#include "usbh_hid.h"

#ifdef HAS_LED_RGB
#include "led_rgb_drv.h"
#endif /*HAS_LED_RGB*/

#ifdef HAS_LED_MONO
#include "led_mono_drv.h"
#endif /*HAS_LED_MONO*/

#ifdef HAS_PASTILDA
#include "pastilda.h"
#endif

#ifdef HAS_KEYLOG
#include "keylog.h"
#endif /*HAS_KEYLOG*/

#ifdef HAS_USB_DEVICE
#include "usb_device.h"
#endif

KeyBoard_t KeyBoard={0};
// USBH_HID_SetReport
void USBH_HID_EventCallback(USBH_HandleTypeDef *phost){
    bool res = false;
    HID_TypeTypeDef dev_type= USBH_HID_GetDeviceType(phost);
    switch( (uint8_t) dev_type) {
    case HID_MOUSE: { // if the HID is Mouse
        HID_MOUSE_Info_TypeDef *Mouse_Info;
        Mouse_Info = USBH_HID_GetMouseInfo(phost);  // Get the info
        int X_Val = Mouse_Info->x;  // get the x value
        int Y_Val = Mouse_Info->y;  // get the y value
        if (X_Val > 127) X_Val -= 255;
        if (Y_Val > 127) Y_Val -= 255;


        LOG_INFO (HID, "X=%d, Y=%d, Button1=%d, Button2=%d, Button3=%d\n", X_Val,
                 Y_Val, Mouse_Info->buttons[0],
                 Mouse_Info->buttons[1],
                 Mouse_Info->buttons[2]);
    }        break;
    case HID_KEYBOARD: {
        uint8_t key;
        HID_KEYBD_Info_TypeDef* KeyBoardInfoNode=NULL;
        KeyBoardInfoNode = USBH_HID_GetKeybdInfo(phost);  // get the info
        if(KeyBoardInfoNode) {
            key = USBH_HID_GetASCIICode(KeyBoardInfoNode);  // get the key pressed
            LOG_DEBUG(HID,"KeyPressed: [%c]",key);
            KeyBoard.modifier.left_alt=KeyBoardInfoNode->lalt;
            KeyBoard.modifier.left_ctrl=KeyBoardInfoNode->lctrl;
            KeyBoard.modifier.left_gui=KeyBoardInfoNode->lgui;
            KeyBoard.modifier.left_shift=KeyBoardInfoNode->lshift;
            KeyBoard.modifier.right_alt=KeyBoardInfoNode->ralt;
            KeyBoard.modifier.right_ctrl=KeyBoardInfoNode->rctrl;
            KeyBoard.modifier.right_gui=KeyBoardInfoNode->rgui;
            KeyBoard.modifier.right_shift=KeyBoardInfoNode->rshift;

            memcpy(KeyBoard.key_code,KeyBoardInfoNode->keys,6);
#ifdef HAS_KEYBOARD_DIAG
            LOG_DEBUG(HID,"%s", KeyBoard2Str(&KeyBoard));
            #endif
            res = key_is_valid(&KeyBoard);
            if(res) {
#ifdef HAS_LED_RGB
                res= led_rgb_blink(LED_HEARTBEAT_ID, 200, COLOR_BLUE) ;
#endif /*HAS_LED_RGB*/
#ifdef HAS_LED_MONO
                res= led_mono_blink(LED_HEARTBEAT_ID, 200) ;
#endif /*HAS_LED_RGB*/

#ifdef HAS_PASTILDA
                res = pastilda_key_proc(&Pastilda,KeyBoard);
                if(res) {
                	LOG_DEBUG(HID,"ProcOk");
                }else{
                	LOG_ERROR(HID,"ProcErr Pas~State:%s",PasTildaMode2Str(Pastilda.state));
                }
#endif /*HAS_PASTILDA*/

#if defined(HAS_KEYBOARD_FORWARDING) && defined(HAS_USB_DEVICE) && !defined(HAS_PASTILDA)
#error ererere
            res = usb_dev_send(&KeyBoard);
#endif /*HAS_KEYBOARD_FORWARDING HAS_USB_DEVICE*/

#ifdef HAS_KEYLOG
                uint8_t buff[80]={0};
                res = tbfp_compose_frame((uint8_t*) &KeyBoard, (uint16_t) sizeof(KeyBoard_t),
                            IF_FAT_FS, FRAME_ID_KEYBOARD, buff, sizeof(buff));
                if(res) {
                	LOG_DEBUG(KEYLOG,"ComposeOk");
                    res = fifo_push_array(&KeyLog.Fifo, buff, sizeof(KeyBoard_t)+TBFP_OVERHEAD_SIZE );
                    if (res) {
                        LOG_DEBUG(KEYLOG,"KeyBoardPushOk");
                    } else {
                        LOG_ERROR(KEYLOG,"PushError");
                    }
                }else {
                    LOG_ERROR(KEYLOG,"ComposeError");
                }
#endif /*HAS_KEYLOG*/
            } else {
#if defined(HAS_KEYBOARD_FORWARDING) && defined(HAS_USB_DEVICE)
            	 res = usb_dev_send(&KeyBoard);
#endif /*HAS_KEYBOARD_FORWARDING HAS_USB_DEVICE*/
            }
        }

    } break;
    } //switch
}
