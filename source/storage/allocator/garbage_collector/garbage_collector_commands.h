#ifndef GARBAGE_COLLECTOR_COMMANDS_H
#define GARBAGE_COLLECTOR_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_GARBAGE_COLLECTOR_COMMANDS
#error "+HAS_GARBAGE_COLLECTOR_COMMANDS"
#endif

/*Add diag*/

#define GARBAGE_COLLECTOR_COMMANDS


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /*GARBAGE_COLLECTOR_COMMANDS_H*/
