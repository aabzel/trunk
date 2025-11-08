#ifndef GAME_PAD_PS2_COMMANDS_H
#define GAME_PAD_PS2_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_GAME_PAD_PS2
#error "+ HAS_GAME_PAD_PS2"
#endif

#ifndef HAS_GAME_PAD_PS2_COMMANDS
#error "+ HAS_GAME_PAD_PS2_COMMANDS"
#endif

bool game_pad_ps2_diag_command(int32_t argc, char* argv[]);
bool game_pad_ps2_init_command(int32_t argc, char* argv[]);
bool game_pad_ps2_reg_map_command(int32_t argc, char* argv[]);
bool game_pad_ps2_motor_command(int32_t argc, char* argv[]);
bool game_pad_ps2_tx_command(int32_t argc, char* argv[]);

#define GAME_PAD_PS2_COMMANDS                                                                                          \
        SHELL_CMD("game_pad_ps2_diag", "gpp2d", game_pad_ps2_diag_command, "GamePadPs2Diag"),                          \
        SHELL_CMD("game_pad_ps2_init", "gpp2i", game_pad_ps2_init_command, "GamePadPs2Init"),                          \
        SHELL_CMD("game_pad_ps2_motor", "gpp2r", game_pad_ps2_motor_command, "GamePadPs2Motor"),                       \
        SHELL_CMD("game_pad_ps2_tx", "gpp2t", game_pad_ps2_tx_command, "GamePadPs2SetTxByte"),                         \
        SHELL_CMD("game_pad_ps2_reg_map", "gprm", game_pad_ps2_reg_map_command, "GamePadPs2RawRegs"),

#ifdef __cplusplus
}
#endif

#endif /* GAME_PAD_PS2_COMMANDS_H */
