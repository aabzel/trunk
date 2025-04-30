#ifndef THIRD_PARTY_COMMANDS_H
#define THIRD_PARTY_COMMANDS_H


#ifdef ASICS_CLI_IN_USE
#include "asics_cli.h"
#else
#define ASICS_CLI
#endif

#ifdef COMPUTING_CLI_IN_USE
#include "computing_cli.h"
#else
#define COMPUTING_CLI
#endif

#ifdef SENSITIVITY_CLI_IN_USE
#include "sensitivity_cli.h"
#else
#define SENSITIVITY_CLI
#endif

#ifdef STORAGE_CLI_IN_USE
#include "storage_cli.h"
#else
#define STORAGE_CLI
#endif

#define THIRD_PARTY_COMMANDS        \
    ASICS_CLI                       \
    COMPUTING_CLI                   \
    SENSITIVITY_CLI                 \
    STORAGE_CLI

#endif /* THIRD_PARTY_COMMANDS_H */
