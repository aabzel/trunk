#include "cli_config.h"

#include "cli_commands.h"
#include "data_utils.h"

static const CliCmdInfo_t CliCommands[] = {CLI_COMMANDS COMMANDS_END};

const CliConfig_t CliConfig[] = {
    {
        .num = 1,
        .valid = true,
        .CommandArray = CliCommands,
        .cmd_cnt = ARRAY_SIZE(CliCommands),
    }
};


CliHandle_t CliInstance[] = {
    {
        .num = 1,
        .valid = true,
    }
};


uint32_t cli_get_command_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(CliCommands);
    return cnt;
}

COMPONENT_GET_CNT(Cli, cli)
