#ifndef GRAPHVIZ_TO_TSORT_COMMANDS_H
#define GRAPHVIZ_TO_TSORT_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool cmd_graphviz_to_tsort_diag(int32_t argc, char* argv[]);
bool cmd_graphviz_to_tsort_proc(int32_t argc, char* argv[]);

#define GRAPHVIZ_TO_TSORT_COMMANDS                                                                \
    SHELL_CMD("graphviz_to_tsort_diag", "gtd", cmd_graphviz_to_tsort_diag, "GraphvizToTsortDiag"),         \
    SHELL_CMD("graphviz_to_tsort_proc", "gts", cmd_graphviz_to_tsort_proc, "GraphvizToTsortProc"),

#ifdef __cplusplus
}
#endif

#endif /* GRAPHVIZ_TO_TSORT_COMMANDS_H */
