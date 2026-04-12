#include "cli_config.h"

#include "data_utils.h"
#include "cli_commands.h"

static const CliCmdInfo_t CliCommands[] = {CLI_COMMANDS COMMANDS_END};

const CliConfig_t CliConfig[] = {
    {
        .num = 1,
        .valid = true,
        .CommandArray = (CliCmdInfo_t*) CliCommands,
        .cmd_cnt = ARRAY_SIZE(CliCommands),
#ifdef HAS_LED
        .feedback_led = 4,
#endif
    },
    {
        .num = 2,
        .valid = true,
        .CommandArray = (CliCmdInfo_t*) CliCommands,
        .cmd_cnt = ARRAY_SIZE(CliCommands),
#ifdef HAS_LED
        .feedback_led = 4,
#endif
    },
    {
        .num = 3,
        .valid = true,
        .CommandArray = (CliCmdInfo_t*) CliCommands,
        .cmd_cnt = ARRAY_SIZE(CliCommands),
#ifdef HAS_LED
        .feedback_led = 4,
#endif
    },
};

CliHandle_t CliInstance[] = {
    {    .num = 1,    .valid = true,    },
    {    .num = 2,    .valid = true,    },
    {    .num = 3,    .valid = true,    },
};

uint32_t cli_get_command_cnt(void) {
	uint32_t cnt = ARRAY_SIZE(CliCommands);
	return cnt;
}


uint32_t cli_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(CliInstance);
    cnt2 = ARRAY_SIZE(CliConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
