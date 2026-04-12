#ifndef ADT_COMMANDS_H
#define ADT_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_ADT_COMMANDS
#error "+HAS_ADT_COMMANDS"
#endif

#ifdef HAS_MAX_HEAP_COMMANDS
#include "max_heap_commands.h"
#else
#define MAX_HEAP_COMMANDS
#endif

#ifdef HAS_MIN_HEAP_COMMANDS
#include "min_heap_commands.h"
#else
#define MIN_HEAP_COMMANDS
#endif

#ifdef HAS_HASH_TABLE_COMMANDS
#include "hash_table_commands.h"
#else
#define HASH_TABLE_COMMANDS
#endif

#ifdef HAS_HASH_TABLE_S8_COMMANDS
#include "hash_table_s8_commands.h"
#else
#define HASH_TABLE_S8_COMMANDS
#endif

#define ADT_COMMANDS                                \
        HASH_TABLE_S8_COMMANDS                      \
        HASH_TABLE_COMMANDS                         \
        MAX_HEAP_COMMANDS                           \
        MIN_HEAP_COMMANDS

#ifdef __cplusplus
}
#endif

#endif /* ADT_COMMANDS_H */
