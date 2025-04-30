#ifndef INTERRUPT_DEP_H
#define INTERRUPT_DEP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifndef HAS_INTERRUPT
#error "+HAS_INTERRUPT"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#ifdef __cplusplus
}
#endif

#endif /* INTERRUPT_DEP_H  */
