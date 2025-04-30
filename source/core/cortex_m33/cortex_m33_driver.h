#ifndef CORTEX_M33_DRV_H
#define CORTEX_M33_DRV_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdbool.h>
#include <stdint.h>

#include "cortex_m33_types.h"

bool cortex_m33_reboot(void);

#ifdef __cplusplus
}
#endif

#endif /* CORTEX_M33_DRV_H */
