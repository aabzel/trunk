#ifndef SENSITIVITY_CLI_H
#define SENSITIVITY_CLI_H


#ifdef HAS_ACCELEROMETER_EHAL_COMMANDS
#include "accelerometer_cli.h"
#else
#define ACCELEROMETER_EHAL_COMMANDS
#endif

#define SENSITIVITY_CLI                  \
    ACCELEROMETER_EHAL_COMMANDS

#endif /* SENSITIVITY_CLI_H */
