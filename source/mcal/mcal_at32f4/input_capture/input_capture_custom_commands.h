#ifndef INPUT_CAPTURE_CUSTOM_COMMANDS_H
#define INPUT_CAPTURE_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>


#ifndef HAS_INPUT_CAPTURE
#error "+HAS_INPUT_CAPTURE"
#endif

#ifndef HAS_CLI
#error "only for CLI"
#endif

#ifndef HAS_INPUT_CAPTURE_COMMANDS
#error "+HAS_INPUT_CAPTURE_COMMANDS"
#endif


#define INPUT_CAPTURE_CUSTOM_COMMANDS

#ifdef __cplusplus
}
#endif

#endif /* INPUT_CAPTURE_CUSTOM_COMMANDS_H */
