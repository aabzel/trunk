#ifndef INTERRUPT_CONFIG_H
#define INTERRUPT_CONFIG_H

#include "interrupt_types.h"


#ifndef HAS_INTERRUPT
#error "+HAS_INTERRUPT"
#endif

extern const InterruptConfig_t InterruptConfig[];

uint32_t interrupt_get_cnt(void);

#endif /* INTERRUPT_CONFIG_H  */
