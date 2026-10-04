#ifndef WATCHDOG_MCAL_H
#define WATCHDOG_MCAL_H

#include "std_includes.h"
#include "watchdog_types.h"
#include "watchdog_config.h"

#ifdef HAS_WATCHDOG_DIAG
#include "watchdog_diag.h"
#endif

bool watchdog_mcal_init(void);
bool WatchDogIsValidConfig(const WatchDogConfig_t* const Config);

bool watchdog_proc(void);

bool watchdog_ctrl(bool on_off);
bool watchdog_timeout_set( uint32_t timeout_ms);

bool watchdog_timeout_get( uint32_t* const timeout_ms);

#endif /* WATCHDOG_MCAL_H */
