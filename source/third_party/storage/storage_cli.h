#ifndef STORAGE_CLI_H
#define STORAGE_CLI_H

#ifdef HAS_EEPROM_EMULATION_CLI
#include "eeprom_emulation_cli.h"
#else
#define EEPROM_EMULATION_CLI
#endif

#ifdef HAS_MEMORY_MANAGER_CLI
#include "memory_manager_cli.h"
#else
#define MEMORY_MANAGER_CLI
#endif

#ifdef HAS_NVRAM_CLI
#include "nvram_cli.h"
#else
#define NVRAM_CLI
#endif

#define STORAGE_CLI         \
    EEPROM_EMULATION_CLI    \
    MEMORY_MANAGER_CLI      \
    NVRAM_CLI


#endif /* STORAGE_CLI_H */
