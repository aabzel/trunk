#ifndef CLOCK_NRF_COMMANDS_H
#define CLOCK_NRF_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_CLOCK_COMMANDS
#error "+HAS_CLOCK_COMMANDS"
#endif

#ifndef HAS_CLOCK
#error "+HAS_CLOCK"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

bool clock_nrfx_sleep_command(int32_t argc, char* argv[]);
bool clock_nrfx_audio_command(int32_t argc, char* argv[]);
bool clock_nrfx_div_command(int32_t argc, char* argv[]);
bool clock_diag_low_freq_command(int32_t argc, char* argv[]);
bool clock_diag_high_frequency_command(int32_t argc, char* argv[]);
bool clock_control_command(int32_t argc, char* argv[]);
bool clock_diag_low_level_command(int32_t argc, char* argv[]);

#define CLOCK_CUSTOM_COMMANDS                                                                         \
    SHELL_CMD("clock_nrfx_audio", "cna", clock_nrfx_audio_command, "ClockNrfxAudio"),                 \
    SHELL_CMD("clock_nrfx_sleep", "cns", clock_nrfx_sleep_command, "ClockNrfxSleep"),                 \
    SHELL_CMD("clock_diag_hi_freq", "clhf", clock_diag_high_frequency_command, "ClockDiagHighFrequency"),    \
    SHELL_CMD("clock_diag_low_freq", "cldl", clock_diag_low_freq_command, "ClockDiagLowFreq"),    \
    SHELL_CMD("clock_div", "cldv", clock_nrfx_div_command, "ClockDivider"),    \
    SHELL_CMD("clock_diag", "clkd", clock_diag_low_level_command, "ClockDiagLowLevel"),    \
    SHELL_CMD("clock_control", "clct", clock_control_command, "ClockControl"),

#ifdef __cplusplus
}
#endif

#endif /* CLOCK_NRF_COMMANDS_H */
