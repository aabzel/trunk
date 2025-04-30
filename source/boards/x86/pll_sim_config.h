#ifndef PLL_SIM_CONFIG_H
#define PLL_SIM_CONFIG_H

#include <stdbool.h>

#include "pll_sim_types.h"

extern const PllSimConfig_t PllSimConfig[];
extern PllSimHandle_t PllSimInstance[];

uint32_t pll_sim_get_cnt(void);

#endif /* PLL_SIM_CONFIG_H  */
