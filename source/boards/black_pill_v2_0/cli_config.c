#include "cli_config.h"

const CliConfig_t CliConfig = {
    .num = 1,
    .valid= true,
    .interface = IF_UART1,
    .if_num = 1,
#ifdef HAS_LED
    .feedback_led = 1,
#endif
};
