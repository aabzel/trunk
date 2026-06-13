#ifndef SCRIPT_CONFIG_H
#define SCRIPT_CONFIG_H

#include "script_types.h"

extern const ScriptConfig_t ScriptConfig[];
extern ScriptHandle_t ScriptInstance[];

uint32_t script_get_cnt(void);

#endif /* SCRIPT_CONFIG_H  */
