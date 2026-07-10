#ifndef REC_PLAY_COMMANDS_H
#define REC_PLAY_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_REC_PLAY
#error "+ HAS_REC_PLAY"
#endif

#ifndef HAS_REC_PLAY_COMMANDS
#error "+ HAS_REC_PLAY_COMMANDS"
#endif

bool rec_play_start_command(int32_t argc, char* argv[]);
bool rec_play_diag_command(int32_t argc, char* argv[]);
bool rec_play_init_command(int32_t argc, char* argv[]);

#define REC_PLAY_COMMANDS                                                                                  \
        SHELL_CMD("rec_play_diag", "rpd", rec_play_diag_command, "RecPlayDiag"),                           \
        SHELL_CMD("rec_play_init", "rpi", rec_play_init_command, "RecPlayInit"),                           \
        SHELL_CMD("rec_play_start", "rps", rec_play_start_command, "RecPlayStart"),

#ifdef __cplusplus
}
#endif

#endif /* REC_PLAY_COMMANDS_H */
