
#ifndef AUDIO_USB_CONFIG_H
#define AUDIO_USB_CONFIG_H

#ifdef HAS_USB_TO_I2S
#include "usb_to_i2s_types.h"
#endif

#include "usb_audio_types.h"

#ifndef HAS_USB
#error "+HAS_USB"
#endif

#ifndef HAS_AUDIO_USB
#error "+HAS_AUDIO_USB"
#endif

extern AudioUsb_t AudioUsbInstance;

#endif /* AUDIO_USB_CONFIG_H */
