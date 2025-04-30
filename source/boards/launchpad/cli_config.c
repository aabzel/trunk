#include "cli_config.h"

const CliConfig_t CliConfig = {
    .num = 1,
    .valid= true,
#ifdef HAS_UART0
    .interface = IF_UART0,
#endif
    .if_num = 0,
    .feedback_led=1,
};
