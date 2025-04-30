#ifndef DDS_COMMANDS_H
#define DDS_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif


#include "std_includes.h"

#ifndef HAS_DDS
#error "+ HAS_DDS"
#endif /*HAS_DDS*/

#ifndef HAS_DDS_COMMANDS
#error "+ HAS_DDS_COMMANDS"
#endif /*HAS_DDS_COMMANDS*/


bool cmd_dds_phase(int32_t argc, char* argv[]);
bool cmd_dds_rev_sample(int32_t argc, char* argv[]);
bool cmd_dds_print_track(int32_t argc, char* argv[]);
bool cmd_dds_set_array(int32_t argc, char* argv[]);
bool cmd_dds_calc_static_tone(int32_t argc, char* argv[]);
bool cmd_dds_pattern(int32_t argc, char* argv[]);
bool cmd_dds_set_sample(int32_t argc, char* argv[]);
bool cmd_dds_fps(int32_t argc, char* argv[]);
bool cmd_dds_amp(int32_t argc, char* argv[]);
bool cmd_dds_set_pwm(int32_t argc, char* argv[]);
bool cmd_dds_set_sin(int32_t argc, char* argv[]);
bool cmd_dds_set_chirp(int32_t argc, char* argv[]);
bool cmd_dds_set_saw(int32_t argc, char* argv[]);
bool cmd_dds_set_fence(int32_t argc, char* argv[]);
bool cmd_dds_diag(int32_t argc, char* argv[]);
bool cmd_dds_play(int32_t argc, char* argv[]);

#define DDS_COMMANDS                                                       \
    SHELL_CMD("dds_phase", "ddp", cmd_dds_phase, "DdsPhase"),              \
    SHELL_CMD("dds_play", "ddl", cmd_dds_play, "DdsPlay"),                 \
    SHELL_CMD("dds_amp", "ddsa", cmd_dds_amp, "DdsAmp"),                                                        \
    SHELL_CMD("dds_fps", "ddsf", cmd_dds_fps, "DdsFps"),                                                        \
    SHELL_CMD("dds_pattern", "ddsp", cmd_dds_pattern, "DdsPattern"),                                            \
    SHELL_CMD("dds_calc_static_tone", "ddsst", cmd_dds_calc_static_tone, "DdsCalcStaticTone"),                  \
    SHELL_CMD("dds_set_array", "ddssa", cmd_dds_set_array, "DdsSetArray"),                                      \
    SHELL_CMD("dds_rev_data", "ddsrd", cmd_dds_rev_sample, "DdsRevHalfWords"),                              \
    SHELL_CMD("dds_print_track", "ddspt", cmd_dds_print_track, "DdsPrintTack"),                             \
    SHELL_CMD("dds_set_sapmle", "ddsss", cmd_dds_set_sample, "DdsSetSample"),                               \
    SHELL_CMD("dds_set_pwm", "ddssp", cmd_dds_set_pwm, "DdsSetPWMWave"),                                    \
    SHELL_CMD("dds_set_sin", "ddssin", cmd_dds_set_sin, "DdsSetSinWave"),                                   \
    SHELL_CMD("dds_set_chirp", "ddschir", cmd_dds_set_chirp, "DdsSetChirp"),                                \
    SHELL_CMD("dds_set_fence", "ddssf", cmd_dds_set_fence, "DdsSetFenceWave"),                              \
    SHELL_CMD("dds_diag", "ddsad", cmd_dds_diag, "DdsDiagnostic"),

#ifdef __cplusplus
}
#endif

#endif /* DDS_COMMANDS_H */
