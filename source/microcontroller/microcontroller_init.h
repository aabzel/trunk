#ifndef MICROCONTROLLER_INIT_H
#define MICROCONTROLLER_INIT_H


#ifdef __cplusplus
 extern "C" {
#endif


#ifndef HAS_MICROCONTROLLER
#error  "+HAS_MICROCONTROLLER"
#endif

#include "microcontroller.h"

#ifdef HAS_LOG
#define MICROCONTROLLER_NAME  .name="Mcu",
#else
#define MICROCONTROLLER_NAME
#endif

#define MICROCONTROLLER_INIT { .init_function = microcontroller_init, MICROCONTROLLER_NAME },


#ifdef __cplusplus
}
#endif


#endif /* MICROCONTROLLER_INIT_H */
