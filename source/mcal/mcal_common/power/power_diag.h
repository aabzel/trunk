#ifndef POWER_DIAG_H
#define POWER_DIAG_H

#include "std_includes.h"
#include "power_types.h"

const char* PowerModeToStr(PowerMode_t power_mode) ;
bool power_diag(void);
bool power_diag_one(uint8_t num);
bool PowerDiagConfig(const PowerConfig_t* const Config);
const char* PowerConfigToStr(const PowerConfig_t* const Config);

#endif /* POWER_DIAG_H */
