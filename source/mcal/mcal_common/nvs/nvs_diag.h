#ifndef NVS_DIAG_H
#define NVS_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

#ifndef HAS_NVS_DIAG
#error "+HAS_NVS_DIAG"
#endif

#ifndef HAS_NVS
#error "+HAS_NVS"
#endif

#ifndef HAS_FLASH
#error "+HAS_FLASH"
#endif

bool nvs_diag(void);

#ifdef __cplusplus
}
#endif

#endif /* NVS_DIAG_H */
