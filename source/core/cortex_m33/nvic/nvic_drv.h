#ifndef INTERRUPT_DRV_H
#define INTERRUPT_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_NVIC
#error "+HAS_NVIC"
#endif

bool nvic_clear(void);
bool nvic_init(void);
bool nvic_disable(void);

#ifdef __cplusplus
}
#endif

#endif /* INTERRUPT_DRV_H  */
