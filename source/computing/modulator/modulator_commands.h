#ifndef MODULATOR_COMMANDS_H
#define MODULATOR_COMMANDS_H

#ifdef HAS_LOG
#include "log.h"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_MODULATOR
#error "+HAS_MODULATOR"
#endif

#ifndef HAS_MODULATOR_COMMANDS
#error "+HAS_MODULATOR_COMMANDS"
#endif

#ifdef HAS_BPSK_COMMANDS
#include "bpsk_commands.h"
#else
#define BPSK_COMMANDS
#endif

#define MODULATOR_COMMANDS      \
    BPSK_COMMANDS

#endif /* MODULATOR_COMMANDS_H */
