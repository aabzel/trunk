#ifndef WM8731_DEP_H
#define WM8731_DEP_H


#ifndef HAS_TIME
#error "+HAS_TIME"
#endif

#ifndef HAS_I2C
#error "+HAS_I2C"
#endif

/*Ble Headset uses its own I2S initialisation procedure*/
#ifndef HAS_I2S
#warning "+HAS_I2S"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#ifndef HAS_MULTIMEDIA
#error "+HAS_MULTIMEDIA"
#endif

#ifndef HAS_DDS
#error "+HAS_DDS"
#endif

#ifndef HAS_WM8731
#error "+HAS_WM8731"
#endif

#endif /* WM8731_DEP_H */
