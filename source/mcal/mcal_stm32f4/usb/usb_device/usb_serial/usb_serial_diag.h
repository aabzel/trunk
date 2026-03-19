#ifndef USB_SERIAL_DIAG_H
#define USB_SERIAL_DIAG_H

#include "std_inc.h"

const char* UsbSerialCdcCmdToStr(const uint8_t cmd);
bool usb_serial_diag(void);

#endif
