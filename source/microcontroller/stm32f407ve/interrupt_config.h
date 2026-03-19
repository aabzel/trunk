#ifndef INTERRUPT_CONFIG_H
#define INTERRUPT_CONFIG_H

#include "interrupt_types.h"


#ifndef HAS_INTERRUPT
#error "+HAS_INTERRUPT"
#endif

extern const InterruptConfig_t InterruptConfig[];

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

//const char* InterruptNumToStr(int16_t int_n);
uint32_t interrupt_get_cnt(void);

#endif /* INTERRUPT_CONFIG_H  */
