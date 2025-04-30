#ifndef WATCHDOG_CUSTOM_DIAG_H
#define WATCHDOG_CUSTOM_DIAG_H

#include "watchdog_types.h"
#include "watchdog_register_types.h"

bool watchdog_diag_low_level(void) ;
bool WatchDogDiagRegStatus(const WatchDogRegStatus_t *const Reg);
bool WatchDogDiagRegConfig(const WatchDogRegConfig_t *const Reg);
bool WatchDogDiagRegKey(const WatchDogRegKey_t *const Reg) ;
bool watchdog_reg_map(void);
bool watchdog_raw_reg(void);


#endif /* WATCHDOG_CUSTOM_DIAG_H */







