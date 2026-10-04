
#ifndef DS3231_CONFIG_H
#define DS3231_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "ds3231_types.h"

#ifndef HAS_DS3231
#error "+HAS_DS3231"
#endif

#ifndef HAS_I2C
#error "+HAS_I2C"
#endif

extern const Ds3231Config_t Ds3231Config[];
extern const Ds3231RegConfig_t Ds3231RegConfig[];
extern Ds3231Handle_t Ds3231Item[];

uint32_t ds3231_get_cnt(void);
uint32_t ds3231_get_reg_config_cnt(void);

#endif /* DS3231_CONFIG_H */
