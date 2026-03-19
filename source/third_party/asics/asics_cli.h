#ifndef ASICS_CLI_H
#define ASICS_CLI_H

#ifdef HAS_LIS3DH_CLI
#include "lis3dh_cli.h"
#else
#define LIS3DH_CLI
#endif

#ifdef HAS_NAU8814_CLI
#include "nau8814_cli.h"
#else
#define NAU8814_CLI
#endif

#define ASICS_CLI    \
    LIS3DH_CLI       \
    NAU8814_CLI

#endif /* ASICS_CLI_H */
