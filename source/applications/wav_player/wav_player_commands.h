#ifndef WAV_PLAYER_COMMANDS_H
#define WAV_PLAYER_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_WAV_PLAYER_CUSTOM_COMMANDS
#include "wav_player_custom_commands.h"
#else
#define WAV_PLAYER_CUSTOM_COMMANDS
#endif


#ifndef HAS_WAV_PLAYER
#error "+ HAS_WAV_PLAYER"
#endif

#ifndef HAS_WAV_PLAYER_COMMANDS
#error "+ HAS_WAV_PLAYER_COMMANDS"
#endif

bool wav_player_play_file_command(int32_t argc, char* argv[]) ;
bool wav_player_diag_command(int32_t argc, char* argv[]);
bool wav_player_init_command(int32_t argc, char* argv[]);

#define WAV_PLAYER_COMMANDS                                                                                      \
        WAV_PLAYER_CUSTOM_COMMANDS                                                                               \
        SHELL_CMD("wav_player_diag", "wpd", wav_player_diag_command, "WavPlayerDiag"),                           \
        SHELL_CMD("wav_player_init", "wpi", wav_player_init_command, "WavPlayerInit"),                           \
        SHELL_CMD("wav_player_play_file", "wpf", wav_player_play_file_command, "WavPlayerRawRegs"),

#ifdef __cplusplus
}
#endif

#endif /* WAV_PLAYER_COMMANDS_H */
