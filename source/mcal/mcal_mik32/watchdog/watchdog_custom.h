#ifndef WATCHDOG_CUSTOM_DRV_H
#define WATCHDOG_CUSTOM_DRV_H

#include "std_includes.h"
#include "watchdog_custom_types.h"
#include "watchdog_types.h"

#ifndef HAS_WATCHDOG
#error "+HAS_WATCHDOG"
#endif

bool watchdog_apply_config(const WatchDogConfig_t *const Config,
		                   WatchDogRegConfig_t* const RegConfig);
uint32_t WatchDogPrescalerCodeToDivider(const Mik32WatchDogPreScale_t prescale);
uint32_t WatchDogDividerToPrescalerCode(const uint32_t divider);

#endif /* WATCHDOG_CUSTOM_DRV_H  */
