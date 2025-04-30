#ifndef INTERRUPT_DRIVER_H
#define INTERRUPT_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "microcontroller_const.h"

bool interrupt_clear(void);
bool interrupt_init(void);
bool interrupt_disable(void);

#ifdef __cplusplus
}
#endif

#endif /* INTERRUPT_DRIVER_H  */
