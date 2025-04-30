
#ifndef FDA801_CONFIG_H
#define FDA801_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "fda801_types.h"

#define FDA801_MAIN 1


extern const Fda801Config_t Fda801Config[];
extern Fda801Handle_t Fda801Instance[];

uint32_t fda801_get_cnt(void);

#endif /* FDA801_CONFIG_H */
