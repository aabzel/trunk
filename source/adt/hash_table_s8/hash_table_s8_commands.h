#ifndef HASH_TABLE_S8_COMMANDS_H
#define HASH_TABLE_S8_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"


#ifndef HAS_HASH_TABLE_S8
#error "+ HAS_HASH_TABLE_S8"
#endif

#ifndef HAS_HASH_TABLE_S8_COMMANDS
#error "+ HAS_HASH_TABLE_S8_COMMANDS"
#endif

bool hash_table_s8_diag_command(int8_t argc, char* argv[]);
bool hash_table_s8_init_command(int8_t argc, char* argv[]);
bool hash_table_s8_pull_command(int8_t argc, char* argv[]);
bool hash_table_s8_push_command(int8_t argc, char* argv[]);
bool hash_table_s8_check_command(int8_t argc, char* argv[]);

#define HASH_TABLE_S8_COMMANDS                                                                                      \
        SHELL_CMD("hash_table_s8_push", "ht8s", hash_table_s8_push_command, "HashTableS8Push"),                     \
        SHELL_CMD("hash_table_s8_check", "ht8k", hash_table_s8_check_command, "HashTableS8Peek"),                     \
        SHELL_CMD("hash_table_s8_pull", "ht8l", hash_table_s8_pull_command, "HashTableS8Pull"),                     \
        SHELL_CMD("hash_table_s8_diag", "ht8d", hash_table_s8_diag_command, "HashTableS8Diag"),                     \
        SHELL_CMD("hash_table_s8_init", "ht8i", hash_table_s8_init_command, "HashTableS8Init"),

#ifdef __cplusplus
}
#endif

#endif /* HASH_TABLE_S8_COMMANDS_H */
