#ifndef USB_DEVICE_CONST_H
#define USB_DEVICE_CONST_H

#ifdef __cplusplus
 extern "C" {
#endif

#define USB_DEVICE_PERIOD_US 3000000
#define BUTTON_INSERT_TIMEOUT_MS 48 //10<19..<<20<< 25 <<40
 // olimex
 // 3 - small (drops character)
 // 24 - small (drops character)

//3-stable
//7-stable
//15-stable
//30-stable
//40-drops character
//50-drops character
//60-relatively stable
//75-ok
//100-ok

#ifdef __cplusplus
}
#endif

#endif /* USB_DEVICE_CONST_H */
