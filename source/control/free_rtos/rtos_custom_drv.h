#ifndef FREE_RTOS_DRV_H
#define FREE_RTOS_DRV_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "rtos_custom_types.h"

void bare_bone(void * argument);
void default_task(void  * argument);
bool free_rtos_init(void);

#ifdef __cplusplus
}
#endif

#endif /* FREE_RTOS_DRV_H */
