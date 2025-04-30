#ifndef WATCHDOG_PARAMS_H
#define WATCHDOG_PARAMS_H

#include "param_types.h"

#define PARAMS_WATCHDOG                                                                                                   \
  {.facility=WATCHDOG, .id=PAR_ID_WATCHDOG_BOOTLOADER_ON,  .default_value="0",   .len=1, .type=TYPE_UINT8,  .name="WatchDogBootLoaderOn"},   \
  {.facility=WATCHDOG, .id=PAR_ID_WATCHDOG_GENERIC_ON,    .default_value="0",    .len=1, .type=TYPE_UINT8,  .name="WatchDogGenericOn"},      \
  {.facility=WATCHDOG, .id=PAR_ID_WATCHDOG_TIME_OUT_MS,   .default_value="14000",    .len=4, .type=TYPE_UINT32, .name="WatchDogTimeOutMs"},

#endif /* WATCHDOG_PARAMS_H  */
