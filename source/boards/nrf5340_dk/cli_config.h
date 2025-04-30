
#ifndef CLI_CONFIG_H
#define CLI_CONFIG_H

#include "cli_general_config.h"
#include "cli_types.h"

#if defined(HAS_CORE_NET) && defined(HAS_CORE_APP)
#error "One build for one core"
#endif

extern const CliConfig_t CliConfig[];
extern CliHandle_t CliInstance[];

uint32_t cli_get_cnt(void);

#endif /*CLI_CONFIG_H*/
