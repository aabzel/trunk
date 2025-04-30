
#ifndef CLI_GENERAL_CONFIG_H
#define CLI_GENERAL_CONFIG_H

#include <stdint.h>

#include "cli_types.h"
#include "cli_config.h"

extern const CliCmdInfo_t shell_commands[];

uint32_t cli_commands_get_cnt(void);

#endif /*CLI_GENERAL_CONFIG_H*/
