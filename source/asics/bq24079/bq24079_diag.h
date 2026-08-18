#ifndef BQ24079_DIAG_H
#define BQ24079_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "bq24079_types.h"

#ifndef HAS_BQ24079
#error "+HAS_BQ24079"
#endif

bool bq24079_diag(void);
const char* Bq24079SettingsToStr(Bq24079Settings_t mode);
const char* Bq24079PgoodToStr(GpioLogicLevel_t pgood_lev) ;

#endif /* BQ24079_DIAG_H  */
