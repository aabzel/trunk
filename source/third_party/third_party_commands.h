#ifndef THIRD_PARTY_COMMANDS_H
#define THIRD_PARTY_COMMANDS_H

#ifdef HAS_ADT_CLI
#include "adt_cli.h"
#else
#define ADT_CLI
#endif

#ifdef HAS_ASICS_CLI
#include "asics_cli.h"
#else
#define ASICS_CLI
#endif

#ifdef HAS_COMPUTING_CLI
#include "computing_cli.h"
#else
#define COMPUTING_CLI
#endif

#ifdef HAS_CONNECTIVITY_CLI
#include "connectivity_cli.h"
#else
#define CONNECTIVITY_CLI
#endif

#ifdef HAS_SENSITIVITY_CLI
#include "sensitivity_cli.h"
#else
#define SENSITIVITY_CLI
#endif

#ifdef HAS_STORAGE_CLI
#include "storage_cli.h"
#else
#define STORAGE_CLI
#endif

#define THIRD_PARTY_COMMANDS        \
    ADT_CLI                         \
    ASICS_CLI                       \
    COMPUTING_CLI                   \
    CONNECTIVITY_CLI                \
    SENSITIVITY_CLI                 \
    STORAGE_CLI

#endif /* THIRD_PARTY_COMMANDS_H */
