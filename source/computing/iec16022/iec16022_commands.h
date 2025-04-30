#ifndef IEC16022_COMMANDS_H
#define IEC16022_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool iec16022_encode_command(int32_t argc, char* argv[]);
bool iec16022_init_command(int32_t argc, char* argv[]);

#define IEC16022_COMMANDS                                               \
    SHELL_CMD("iec16022_encode", "dme", iec16022_encode_command, "Iec16022Encode"),   \
    SHELL_CMD("iec16022_init", "dmi", iec16022_init_command, "Iec16022Init"),


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /*IEC16022_COMMANDS_H*/
