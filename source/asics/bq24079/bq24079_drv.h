#ifndef BQ24079_H
#define BQ24079_H

#include <stdbool.h>
#include <stdint.h>

#include "bq24079_types.h"
#include "bq24079_config.h"

bool bq24079_init(void);
bool bq24079_proc(void);
Bq24079Settings_t bq24079_settings_get(void);
bool bq24079_settings_set(Bq24079Settings_t settings);

#endif /* BQ24079_H */
