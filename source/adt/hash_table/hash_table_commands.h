#ifndef HASH_TABLE_COMMANDS_H
#define HASH_TABLE_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"


#ifndef HAS_HASH_TABLE
#error "+ HAS_HASH_TABLE"
#endif

#ifndef HAS_HASH_TABLE_COMMANDS
#error "+ HAS_HASH_TABLE_COMMANDS"
#endif

bool hash_table_diag_command(int32_t argc, char* argv[]);
bool hash_table_init_command(int32_t argc, char* argv[]);
bool hash_table_pull_command(int32_t argc, char* argv[]);
bool hash_table_push_command(int32_t argc, char* argv[]);
bool hash_table_peek_command(int32_t argc, char* argv[]);

#define HASH_TABLE_COMMANDS                                                                                      \
        SHELL_CMD("hash_table_push", "hts", hash_table_push_command, "HashTablePush"),                           \
        SHELL_CMD("hash_table_peek", "htk", hash_table_peek_command, "HashTablePeek"),                           \
        SHELL_CMD("hash_table_pull", "htl", hash_table_pull_command, "HashTablePull"),                           \
        SHELL_CMD("hash_table_diag", "htd", hash_table_diag_command, "HashTableDiag"),                           \
        SHELL_CMD("hash_table_init", "hti", hash_table_init_command, "HashTableInit"),

#ifdef __cplusplus
}
#endif

#endif /* HASH_TABLE_COMMANDS_H */
