#ifndef IF_CONFIG_H
#define IF_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_SYSTEM
#error "+HAS_SYSTEM"
#endif

#include <stdint.h>

#include "sys_constants.h"
#ifdef HAS_INTERFACES
#include "interfaces_const.h"
extern const Interfaces_t AvailableInterfacesLUT[];
#endif

uint32_t interface_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* IF_CONFIG_H */
