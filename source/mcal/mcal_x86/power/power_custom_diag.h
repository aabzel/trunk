#ifndef POWER_CUSTOM_DIAG_H
#define POWER_CUSTOM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "power_custom_types.h"
#include "power_manager_X8632B1Mx.h"

bool power_raw_reg_diag(uint8_t num);
bool power_diag_low_level(uint8_t num, const char* const keyword);
const char* PowerFc73ModeToStr(power_mode_stat_t power_mode);

#ifdef __cplusplus
}
#endif

#endif /* POWER_CUSTOM_DIAG_H */
