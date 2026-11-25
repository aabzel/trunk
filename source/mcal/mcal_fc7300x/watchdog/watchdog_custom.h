#ifndef WATCHDOG_DRV_H
#define WATCHDOG_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "wdt_types.h"

uint16_t PrescalerCode2Num(wdt_division_type code) ;
wdt_division_type PrescalerToCode(uint32_t divider);

#endif /* WATCHDOG_DRV_H  */
