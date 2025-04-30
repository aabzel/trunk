#ifndef PLL_SIM_DIAG_H
#define PLL_SIM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include  "pll_sim_types.h"

bool pll_sim_diag(uint8_t num);
const char* PllSinConfigToStr(const PllSimConfig_t* const Config);
const char* PllSinNodeToStr(const PllSimHandle_t* const Node);


#ifdef __cplusplus
}
#endif

#endif /* PLL_SIM_DIAG_H */
