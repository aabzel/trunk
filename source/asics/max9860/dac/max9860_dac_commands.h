#ifndef MAX9860_DAC_COMMANDS_H
#define MAX9860_DAC_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_MAX9860
#error "+ HAS_MAX9860"
#endif

#ifndef HAS_MAX9860_COMMANDS
#error "+ HAS_MAX9860_COMMANDS"
#endif

bool max9860_test_command(int32_t argc, char* argv[]);
bool max9860_attenuation_command(int32_t argc, char* argv[]);
bool max9860_dac_gain_command(int32_t argc, char* argv[]);
bool max9860_play_infinite_command(int32_t argc, char* argv[]);
bool max9860_stereo_command(int32_t argc, char* argv[]);
bool max9860_play_1kHz_tone_command(int32_t argc, char* argv[]);


#define MAX9860_DAC_COMMANDS                                                                          \
    SHELL_CMD("max9860_stereo", "ms", max9860_stereo_command, "Max9860Stereo"),                       \
    SHELL_CMD("max9860_play_1kHz_tone", "mo", max9860_play_1kHz_tone_command, "Max9860Play1kHzTone"), \
    SHELL_CMD("max9860_dac_gain", "mg", max9860_dac_gain_command, "Max9860DacGain"),                  \
    SHELL_CMD("max9860_attenuation", "ma", max9860_attenuation_command, "Max9860Attenuation"),        \
    SHELL_CMD("max9860_test", "mte", max9860_test_command, "Max9860Test"),                            \
    SHELL_CMD("max9860_play_infinite", "mpi", max9860_play_infinite_command, "Max9860PlayInfinite"),

#ifdef __cplusplus
}
#endif

#endif /* MAX9860_DAC_COMMANDS_H */
