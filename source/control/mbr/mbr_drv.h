#ifndef MBR_DRIVER_H
#define MBR_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "mbr_types.h"
#include "mbr_config.h"


bool mbr_init(void);
bool mbr_proc(void);

#ifdef __cplusplus
}
#endif

#endif /* MBR_DRIVER_H */
