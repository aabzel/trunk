#ifndef PLL_SIM_DRV_H
#define PLL_SIM_DRV_H

/*PLL_SIM receiver invariant component*/
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

#include "pll_sim_diag.h"
#include "pll_sim_types.h"
#include "pll_sim_config.h"

PllSimHandle_t* PllSimGetNode(uint8_t num);
const PllSimConfig_t* PllSimGetConfig(uint8_t num);

double sign_v(double value);
bool pll_sim_init_one(uint8_t num);
bool pll_sim_mcal_init(void);
bool pll_sim_proc(void);
bool pll_sim_proc_one(uint8_t num);
bool pll_sim_divider_set(uint8_t num,uint32_t divider);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*PLL_SIM_DRV_H*/
