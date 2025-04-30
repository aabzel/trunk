#ifndef I_WATCHDOG_PARAMS_H
#define I_WATCHDOG_PARAMS_H

#include "param_types.h"

#define IWDG_PARAMS \
  {.facility=LG_IWDG, .id=PAR_ID_IWDG_BOOTLOADER_ON,     .len=1, .type=TYPE_UINT8,  .name="iWdgBootOn"},\
  {.facility=LG_IWDG, .id=PAR_ID_IWDG_GENERIC_ON,        .len=1, .type=TYPE_UINT8,  .name="iWdgGenerOn"},\
  {.facility=LG_IWDG, .id=PAR_ID_IWDG_PERIOD_MS, .len=4, .type=TYPE_UINT32, .name="IWDGOnPeriodMs"},

#endif /* I_WATCHDOG_PARAMS_H  */
