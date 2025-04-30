#ifndef USB_DEVICE_H
#define USB_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "stm32f4xx.h"
#include "artery_at32f4xx.h"
#include "usbd_def.h"

#include "key_board_drv.h"
#include "usb_device_types.h"
#include "usbd_customhid.h"

#ifndef HAS_USB_DEVICE
#error "Error +HAS_USB_DEVICE"
#endif

extern uint8_t rx_buf[CUSTOM_HID_EPOUT_SIZE];

uint8_t* USBD_HID_GetData(void);
const char* UsbErr2Str(uint8_t status);
bool usb_device_proc(void);
bool usb_dev_press_key(KeyBoard_t key_code, uint32_t wait_pause_ms);
bool usb_dev_send(KeyBoard_t* const key_code);
bool usb_device_init(void);
bool usb_key_board_press(uint8_t ascii_code, uint32_t time_out_ms);
bool usb_keyboard_unpress(uint32_t time_out_ms);
bool usb_key_board_send_text(const char* const text, uint32_t time_out);
bool usb_key_board_send_array(uint8_t* array, uint32_t size, uint32_t time_out);

#ifdef __cplusplus
}
#endif

#endif /* USB_DEVICE_H */
