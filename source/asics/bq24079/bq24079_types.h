#ifndef BQ24079_TYPES_H
#define BQ24079_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "bq24079_const.h"
#include "bq24079_dep.h"
#include "data_types.h"
#include "gpio_types.h"

#define BQ24079_COMMON_VAR     \
    Bq24079Settings_t setting; \
	Pad_t en1;     \
	Pad_t en2;   \
	Pad_t pgood; \
    bool valid;

typedef struct {
    BQ24079_COMMON_VAR
	char* name;
} Bq24079Config_t;

typedef struct {
    BQ24079_COMMON_VAR
    GpioLogicLevel_t en1_lev;
    GpioLogicLevel_t en2_lev;
	GpioLogicLevel_t pgood_lev;
    bool init;
    uint32_t err_cnt;
} Bq24079Item_t;

#endif /* BQ24079_TYPES_H */
