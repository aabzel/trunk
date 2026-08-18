#ifndef MIC2026_COMMANDS_H
#define MIC2026_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_MIC2026
#error "+HAS_MIC2026"
#endif

bool cmd_mic2026_init(int32_t argc, char* argv[]);
bool cmd_mic2026_diag(int32_t argc, char* argv[]);
bool cmd_mic2026_get_channel(int32_t argc, char* argv[]);
bool cmd_mic2026_set_channel(int32_t argc, char* argv[]);

#define MIC2026_COMMANDS                                                       \
    SHELL_CMD("mic2026_diag", "mid", cmd_mic2026_diag, "Mic2026Diag"),         \
    SHELL_CMD("mic2026_init", "mii", cmd_mic2026_init, "Mic2026Init"),         \
	    SHELL_CMD("mic2026_get_ch", "mig", cmd_mic2026_get_channel, "Mic2026GetChan"),   \
	    SHELL_CMD("mic2026_set_ch", "mis", cmd_mic2026_set_channel, "Mic2026SetChan"),
                                                                            

#ifdef __cplusplus
}
#endif

#endif /* MIC2026_COMMANDS_H */
