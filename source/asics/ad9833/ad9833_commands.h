#ifndef AD9833_COMMANDS_H
#define AD9833_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

bool cmd_ad9833_init(int32_t argc, char* argv[]);
bool cmd_ad9833_set_signal(int32_t argc, char* argv[]);
bool cmd_ad9833_set_freq(int32_t argc, char* argv[]);
bool cmd_ad9833_set_phase(int32_t argc, char* argv[]);
bool cmd_ad9833_set_form(int32_t argc, char* argv[]);

#define AD9833_COMMANDS                                                                  \
    SHELL_CMD("ad9833_set_form", "ado", cmd_ad9833_set_form, "Ad9833SetForm"),           \
    SHELL_CMD("ad9833_set_freq", "adf", cmd_ad9833_set_freq, "Ad9833SetFreq"),           \
    SHELL_CMD("ad9833_set_phase", "adp", cmd_ad9833_set_phase, "Ad9833SetPhase"),        \
    SHELL_CMD("ad9833_diag", "add", cmd_ad9833_set_signal, "Ad9833SetSignal"),           \
    SHELL_CMD("ad9833_init", "adi", cmd_ad9833_init, "Ad9833Init"),
                                                                            

#ifdef __cplusplus
}
#endif

#endif /* AD9833_COMMANDS_H */
