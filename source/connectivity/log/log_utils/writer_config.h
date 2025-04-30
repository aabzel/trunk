#ifndef WRITER_CONFIG_H
#define WRITER_CONFIG_H

#include "writer_generic.h"

#ifdef HAS_LORA
#include "writer_lora.h"
#endif /*HAS_LORA*/

#ifdef HAS_CAN
#include "writer_can.h"
#endif /*HAS_CAN*/

#ifdef HAS_UART
#include "writer_uart.h"
#endif /*HAS_UART*/

#ifdef HAS_SWD
#include "writer_swd.h"
#endif /*HAS_SWD*/

#if defined(HAS_HID) && defined(HAS_USB_DEVICE)
#include "writer_usb_hid.h"
#endif /*HAS_HID*/

#ifdef HAS_X86_64
#include "writer_stdout.h"
#endif /*HAS_X86_64*/

extern generic_writer_t *curWriterPtr;


#endif /* WRITER_CONFIG_H */
