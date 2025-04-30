
#ifndef FDA801_CONFIG_H
#define FDA801_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "fda801_types.h"

#ifndef HAS_FDA801
#error " +HAS_FDA801"
#endif

#ifndef HAS_GPIO
#error " +HAS_GPIO"
#endif

#ifndef HAS_I2C
#error " +HAS_I2C"
#endif

#ifndef HAS_I2S
//#error " +HAS_I2S"
#endif

#define FDA801_MAIN 1
#define I2S_FDA801 0

extern const Fda801Config_t Fda801Config[];
extern Fda801Handle_t Fda801Instance[];

uint32_t fda801_get_cnt(void);

#endif /* FDA801_CONFIG_H */
