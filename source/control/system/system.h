#ifndef SYSTEM_H
#define SYSTEM_H

#include "std_includes.h"
#include "system_types.h"
#ifdef HAS_INTERFACES
#include "interfaces_const.h"
#endif

#if defined(HAS_MBR) && defined(HAS_BOOTLOADER)
#error "Impossible config"
#endif /*HAS_MBR HAS_BOOTLOADER*/

#if defined(HAS_BOOTLOADER) && defined(HAS_GENERIC)
#error "Impossible config"
#endif /* HAS_BOOTLOADER HAS_GENERIC*/

#if defined(HAS_MBR) && defined(HAS_GENERIC)
#error "Impossible config"
#endif /* HAS_MBR HAS_GENERIC*/

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

extern const SystemInitInstance_t SystemInitInstance[];

extern uint32_t send_err_cnt;
extern System_t System;

bool system_init(void);
#ifdef HAS_SYSTEM_EXT
bool system_init_array_uniq(void);
#endif
BuildType_t system_get_prog_type(void);
uint32_t system_init_get_cnt(void);


#endif /* SYSTEM_H  */
