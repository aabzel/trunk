#ifndef INTERRUPT_CUSTOM_DRIVER_H
#define INTERRUPT_CUSTOM_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "microcontroller_const.h"

bool interrupt_clear(void);
bool interrupt_init(void);
bool interrupt_disable(void);

#ifdef __cplusplus
}
#endif

#endif /* INTERRUPT_CUSTOM_DRIVER_H  */
