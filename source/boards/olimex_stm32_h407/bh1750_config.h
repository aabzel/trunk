
#ifndef BH1750_CONFIG_H
#define BH1750_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "bh1750_types.h"
#include "bh1750_dep.h"

extern const Bh1750Config_t Bh1750Config[];
extern Bh1750Handle_t Bh1750Instance[];

uint32_t bh1750_get_cnt(void);

#endif /* BH1750_CONFIG_H */
