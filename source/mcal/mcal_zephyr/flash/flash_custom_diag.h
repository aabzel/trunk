
#ifndef FLASH_DIAG_H
#define FLASH_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_FLASH
#error "It is needed HAS_FLASH option for that component"
#endif

#ifndef HAS_DIAG
#error "It is needed HAS_DIAG option for that component"
#endif

#ifndef HAS_FLASH_DIAG
#error "It is needed HAS_FLASH_DIAG option for that component"
#endif

bool flash_custom_diag(void);

#ifdef __cplusplus
}
#endif

#endif /* FLASH_DIAG_H */
