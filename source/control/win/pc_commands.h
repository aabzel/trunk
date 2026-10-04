#ifndef PC_COMMANDS_H
#define PC_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool plot_graph_command(int32_t argc, char* argv[]);
bool exit_command(int32_t argc, char* argv[]);

#define PC_COMMANDS                                                       \
    SHELL_CMD("plot_graph", "pg", plot_graph_command, "PlotGrapFromCsv"), \
    SHELL_CMD("exit", "exit", exit_command, "Exit"),

#ifdef __cplusplus
}
#endif

#endif /* PC_COMMANDS_H */
