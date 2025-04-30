#ifndef I_WATCHDOG_PARAMS_H
#define I_WATCHDOG_PARAMS_H

#include "param_types.h"

#define IWDG_PARAMS                                \
  {.facility=LG_IWDG, .default_value="0",  .id=PAR_ID_WATCHDOG_BOOTLOADER_ON, .len=1, .type=TYPE_UINT8, .name="WdgBootOn"},\
  {.facility=LG_IWDG, .default_value="0",  .id=PAR_ID_WATCHDOG_GENERIC_ON, .len=1, .type=TYPE_UINT8, .name="WdgGenerOn"},\
  {.facility=LG_IWDG, .default_value="14000", .id=PAR_ID_WATCHDOG_TIME_OUT_MS, .len=4, .type=TYPE_UINT32, .name="WDGOnPeriodMs"},


#endif /* I_WATCHDOG_PARAMS_H  */
