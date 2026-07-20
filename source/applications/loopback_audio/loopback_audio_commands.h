#ifndef LOOPBACK_AUDIO_COMMANDS_H
#define LOOPBACK_AUDIO_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_LOOPBACK_AUDIO
#error "+ HAS_LOOPBACK_AUDIO"
#endif

#ifndef HAS_LOOPBACK_AUDIO_COMMANDS
#error "+ HAS_LOOPBACK_AUDIO_COMMANDS"
#endif

bool loopback_audio_diag_command(int32_t argc, char* argv[]);
bool loopback_audio_init_command(int32_t argc, char* argv[]);
bool loopback_audio_start_command(int32_t argc, char* argv[]);
bool loopback_audio_rec_start_command(int32_t argc, char* argv[]);
bool loopback_audio_rec_test_command(int32_t argc, char* argv[]);
bool loopback_audio_play_start_command(int32_t argc, char* argv[]);
bool loopback_audio_play_rec_test_command(int32_t argc, char* argv[]);

#define LOOPBACK_AUDIO_COMMANDS                                                                                        \
        SHELL_CMD("loopback_audio_play_rec_test", "laprt", loopback_audio_play_rec_test_command, "LoopbackAudioPlayRecTest"),         \
        SHELL_CMD("loopback_audio_rec_test", "lart", loopback_audio_rec_test_command, "LoopbackAudioRecTest"),         \
        SHELL_CMD("loopback_audio_diag", "lad", loopback_audio_diag_command, "LoopbackAudioDiag"),                     \
        SHELL_CMD("loopback_audio_init", "lai", loopback_audio_init_command, "LoopbackAudioInit"),                     \
        SHELL_CMD("loopback_audio_start", "las", loopback_audio_start_command, "LoopbackAudioStart"),                  \
        SHELL_CMD("loopback_audio_rec_start", "lars", loopback_audio_rec_start_command, "LoopbackAudioRecStart"),      \
        SHELL_CMD("loopback_audio_play_start", "laps", loopback_audio_play_start_command, "LoopbackAudioPlayStart"),

#ifdef __cplusplus
}
#endif

#endif /* LOOPBACK_AUDIO_COMMANDS_H */
