#ifndef SYSTEM_H
#define SYSTEM_H

#include "std_includes.h"
#include "system_types.h"

#ifdef HAS_SYSTEM_DIAG
#include "system_diag.h"
#endif

#ifdef HAS_INTERFACES
#include "interfaces_const.h"
#endif

#if defined(HAS_MBR) && defined(HAS_BOOTLOADER)
#error "Impossible config"
#endif

#if defined(HAS_BOOTLOADER) && defined(HAS_GENERIC)
#error "Impossible config"
#endif

#if defined(HAS_MBR) && defined(HAS_GENERIC)
#error "Impossible config"
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

extern const SystemInitInstance_t SystemInitInstance[];

extern uint32_t send_err_cnt;
extern System_t System;

bool sysrem_pre_init(void);
bool system_mcal_init(void);
bool system_is_all_init(void);
bool system_init_one(const SystemInitInstance_t* const Node,
                     const uint32_t init_cnt) ;

bool system_init_array_uniq(void);
BuildType_t system_get_prog_type(void);
uint32_t system_init_get_cnt(void);


#endif /* SYSTEM_H  */
