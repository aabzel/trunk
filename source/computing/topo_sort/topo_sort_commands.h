#ifndef TOPO_SORT_COMMANDS_H
#define TOPO_SORT_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool topo_sort_run_command(int32_t argc, char* argv[]);
bool topo_sort_diag_command(int32_t argc, char* argv[]);

#define TOPO_SORT_COMMANDS                                                   \
    SHELL_CMD("topo_sort_run", "osr", topo_sort_run_command, "TopoSortRun"),           \
    SHELL_CMD("topo_sort_diag", "osd", topo_sort_diag_command, "TopoSortDiag"),


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /*TOPO_SORT_COMMANDS_H*/
