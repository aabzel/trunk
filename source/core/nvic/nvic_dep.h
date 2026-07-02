#ifndef NVIC_DEPEND_H
#define NVIC_DEPEND_H


#ifdef HAS_VENDOR_SDK
#ifndef HAS_CMSIS
#error "+HAS_CMSIS"
#endif
#endif

#ifndef HAS_NVIC
#error "+HAS_NVIC"
#endif

#ifndef HAS_ARM
#error "+HAS_ARM"
#endif

#ifndef HAS_INTERRUPT
#error "+HAS_INTERRUPT"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#endif /* NVIC_DEPEND_H  */
