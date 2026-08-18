#ifndef NAU8814_DAC_COMMANDS_H
#define NAU8814_DAC_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_NAU8814
#error "+ HAS_NAU8814"
#endif

#ifndef HAS_NAU8814_COMMANDS
#error "+ HAS_NAU8814_COMMANDS"
#endif

bool nau8814_dac_gain_command(int32_t argc, char* argv[]);
bool nau8814_play_infinite_command(int32_t argc, char* argv[]);
bool nau8814_play_1kHz_tone_command(int32_t argc, char* argv[]);
bool nau8814_play_tone_command(int32_t argc, char* argv[]);

#define NAU8814_DAC_COMMANDS                                                                          \
    SHELL_CMD("nau8814_play1kHz", "no", nau8814_play_1kHz_tone_command, "Nau8814Play1kHz"),           \
    SHELL_CMD("nau8814_play", "np", nau8814_play_tone_command, "Nau8814Play"),                        \
    SHELL_CMD("nau8814_dac_gain", "ng", nau8814_dac_gain_command, "Nau8814DacGain"),                  \
    SHELL_CMD("nau8814_play_infinite", "npi", nau8814_play_infinite_command, "Nau8814PlayInfinite"),

#ifdef __cplusplus
}
#endif

#endif /* NAU8814_DAC_COMMANDS_H */
