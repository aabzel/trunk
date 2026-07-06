#ifndef IQUEUE_CLI_H
#define IQUEUE_CLI_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_IQUEUE
#error "+ HAS_IQUEUE"
#endif

#ifndef HAS_IQUEUE_CLI
#error "+ HAS_IQUEUE_CLI"
#endif


bool iqueue_diag_cli(int32_t argc, char* argv[]);
bool iqueue_init_cli(int32_t argc, char* argv[]);
bool iqueue_push_cli(int32_t argc, char* argv[]);
bool iqueue_pull_cli(int32_t argc, char* argv[]);

#define IQUEUE_CLI                                                                                 \
        SHELL_CMD("iqueue_diag", "iqd", iqueue_diag_cli, "iQueueDiag"),                            \
        SHELL_CMD("iqueue_init", "iqi", iqueue_init_cli, "iQueueInit"),                            \
        SHELL_CMD("iqueue_push", "iqsh", iqueue_push_cli, "iQueuePush"),                           \
        SHELL_CMD("iqueue_pull", "iqll", iqueue_pull_cli, "iQueuePull"),

#ifdef __cplusplus
}
#endif

#endif /* IQUEUE_CLI_H */
