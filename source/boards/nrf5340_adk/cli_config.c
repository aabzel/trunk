
#include "cli_config.h"

const CliConfig_t CliConfig = {
    .num = 1,
    .valid = true,
    .interface = IF_UART0,
    .if_num = 0,
#ifdef HAS_LED
    .feedback_led = 1,
#endif /*HAS_LED*/
};

