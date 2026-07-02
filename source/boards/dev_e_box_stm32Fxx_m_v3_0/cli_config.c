#include "cli_config.h"

#include "data_utils.h"
#include "cli_commands.h"

static const CliCmdInfo_t CliCommands[] = {CLI_COMMANDS COMMANDS_END};

const CliConfig_t SECTION_CFG_DATA CliConfig[] = {
    {
        .num = 1,
        .rtc_num = 1,
        .valid = true,
        .CommandArray = (CliCmdInfo_t*) CliCommands,
        .cmd_cnt = ARRAY_SIZE(CliCommands),
#ifdef HAS_LED
        .feedback_led = 1,
#endif
    },
};

CliHandle_t CliInstance[] = {
    { .num = 1, .valid = true, },
};

uint32_t cli_get_command_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(CliCommands);
    return cnt;
}

COMPONENT_GET_CNT(Cli, cli)
