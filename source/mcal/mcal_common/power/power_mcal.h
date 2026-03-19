#ifndef POWER_MCAL_H
#define POWER_MCAL_H

#include "std_includes.h"
#include "power_config.h"
#include "power_types.h"
#ifdef HAS_POWER_DIAG
#include "power_diag.h"
#endif

const PowerConfig_t* PowerGetConfig(uint8_t num);
const PowerInfo_t* PowerGetInfo(uint8_t num);
PowerHandle_t* PowerGetNode(uint8_t num);

bool power_init_common(const PowerConfig_t* const Config, PowerHandle_t* const Node);
bool power_mcal_init(void);
bool power_init_custom(void);
bool power_proc(void);
bool power_init_one(uint8_t num);
bool power_proc_one(uint8_t num);

bool PowerIsValidConfig(const PowerConfig_t* const Config);

#endif /* POWER_MCAL_H */
