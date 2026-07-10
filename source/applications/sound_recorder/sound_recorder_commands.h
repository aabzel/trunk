#ifndef SOUND_RECORDER_COMMANDS_H
#define SOUND_RECORDER_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_SOUND_RECORDER
#error "+ HAS_SOUND_RECORDER"
#endif

#ifndef HAS_SOUND_RECORDER_COMMANDS
#error "+ HAS_SOUND_RECORDER_COMMANDS"
#endif

bool sound_recorder_test_rec_command(int32_t argc, char* argv[]);
bool sound_recorder_rec_command(int32_t argc, char* argv[]);
bool sound_recorder_diag_command(int32_t argc, char* argv[]);
bool sound_recorder_init_command(int32_t argc, char* argv[]);
bool sound_recorder_fs_command(int32_t argc, char* argv[]);

#define SOUND_RECORDER_COMMANDS                                                                                        \
        SHELL_CMD("sound_rec_rect", "sorrt", sound_recorder_test_rec_command, "SoundRecorderTestRec"),                \
        SHELL_CMD("sound_rec_set_fs", "srsf", sound_recorder_fs_command, "SoundRecorderSampleFreq"),                  \
        SHELL_CMD("sound_rec_rec", "sorr", sound_recorder_rec_command, "SoundRecorderRec"),                            \
        SHELL_CMD("sound_rec_diag", "sord", sound_recorder_diag_command, "SoundRecorderDiag"),                         \
        SHELL_CMD("sound_rec_init", "sori", sound_recorder_init_command, "SoundRecorderInit"),

#ifdef __cplusplus
}
#endif

#endif /* SOUND_RECORDER_COMMANDS_H */
