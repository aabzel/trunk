#ifndef SW_DAC_COMMANDS_H
#define SW_DAC_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_SW_DAC
#error "+ HAS_SW_DAC"
#endif /*HAS_SW_DAC*/

#ifndef HAS_SW_DAC_COMMANDS
#error "+ HAS_SW_DAC_COMMANDS"
#endif /*HAS_SW_DAC_COMMANDS*/

bool cmd_sw_dac_rev_sample(int32_t argc, char* argv[]);
bool cmd_sw_dac_print_track(int32_t argc, char* argv[]);
bool cmd_sw_dac_set_array(int32_t argc, char* argv[]);
bool cmd_sw_dac_calc_static_tone(int32_t argc, char* argv[]);
bool cmd_sw_dac_pattern(int32_t argc, char* argv[]);
bool cmd_sw_dac_set_sample(int32_t argc, char* argv[]);
bool cmd_sw_dac_fps(int32_t argc, char* argv[]);
bool cmd_sw_dac_amp(int32_t argc, char* argv[]);
bool cmd_sw_dac_set_pwm(int32_t argc, char* argv[]);
bool cmd_sw_dac_set_sin(int32_t argc, char* argv[]);
bool cmd_sw_dac_set_saw(int32_t argc, char* argv[]);
bool cmd_sw_dac_set_fence(int32_t argc, char* argv[]);
bool cmd_sw_dac_diag(int32_t argc, char* argv[]);

#define SW_DAC_COMMANDS                                                                                                \
    SHELL_CMD("sw_dac_amp", "sda", cmd_sw_dac_amp, "SwDacAmp"),                                                        \
    SHELL_CMD("sw_dac_fps", "sdf", cmd_sw_dac_fps, "SwDacFps"),                                                        \
    SHELL_CMD("sw_dac_pattern", "sdp", cmd_sw_dac_pattern, "SwDacPattern"),                                            \
    SHELL_CMD("sw_dac_calc_static_tone", "sdst", cmd_sw_dac_calc_static_tone, "SwDacCalcStaticTone"),                  \
    SHELL_CMD("sw_dac_set_array", "sdsa", cmd_sw_dac_set_array, "SwDacSetArray"),                                      \
    SHELL_CMD("sw_dac_rev_data", "sdrd", cmd_sw_dac_rev_sample, "SwDacRevHalfWords"),                              \
    SHELL_CMD("sw_dac_print_track", "sdpt", cmd_sw_dac_print_track, "SwDacPrintTack"),                             \
    SHELL_CMD("sw_dac_set_sapmle", "sdss", cmd_sw_dac_set_sample, "SwDacSetSample"),                               \
    SHELL_CMD("sw_dac_set_pwm", "sdsp", cmd_sw_dac_set_pwm, "SwDacSetPWMWave"),                                    \
    SHELL_CMD("sw_dac_set_sin", "sdsin", cmd_sw_dac_set_sin, "SwDacSetSinWave"),                                   \
    SHELL_CMD("sw_dac_set_fence", "sdsf", cmd_sw_dac_set_fence, "SwDacSetFenceWave"),                              \
    SHELL_CMD("sw_dac_diag", "sdad", cmd_sw_dac_diag, "SwDacDiagnostic"),

#ifdef __cplusplus
}
#endif

#endif /* SW_DAC_COMMANDS_H */
