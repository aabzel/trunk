#ifndef MICROCONTROLLER_INIT_H
#define MICROCONTROLLER_INIT_H

#ifndef HAS_MICROCONTROLLER
#error  "+HAS_MICROCONTROLLER"
#endif

#include "microcontroller.h"

#define MICROCONTROLLER_INIT {.init_function=mcu_init, .name="Mcu",},


#endif /* MICROCONTROLLER_INIT_H */
