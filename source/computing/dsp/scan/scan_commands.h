#ifndef SCAN_COMMANDS_H
#define SCAN_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif


#include <std_includes.h>

#include "ostream.h"

#ifndef HAS_SCAN
#error "+HAS_SCAN"
#endif  /*HAS_SCAN*/

#ifndef HAS_SCAN_COMMANDS
#error "+HAS_SCAN_COMMANDS"
#endif  /*HAS_SCAN_COMMANDS*/

bool scan_proc_command(int32_t argc, char* argv[]);
bool scan_diag_command(int32_t argc, char* argv[]);

#define SCAN_COMMANDS                                                                        \
    SHELL_CMD("scan_diag", "ded", scan_diag_command, "ScanDiag"),       \
    SHELL_CMD("scan_proc", "dep", scan_proc_command, "ScanProc"),

#ifdef __cplusplus
}
#endif

#endif /* SCAN_COMMANDS_H */
