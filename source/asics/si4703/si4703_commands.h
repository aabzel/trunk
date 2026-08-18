#ifndef SI4703_COMMANDS_H
#define SI4703_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_SI4703
#error "+ HAS_SI4703"
#endif

#ifndef HAS_SI4703_COMMANDS
#error "+ HAS_SI4703_COMMANDS"
#endif

bool si4703_xtall_en_command(int32_t argc, char* argv[]);
bool si4703_set_fm_freq_command(int32_t argc, char* argv[]);
bool si4703_reg_write_command(int32_t argc, char* argv[]);
bool si4703_rf_seek_command(int32_t argc, char* argv[]);
bool si4703_reg_read_command(int32_t argc, char* argv[]);
bool si4703_init_command(int32_t argc, char* argv[]);
bool si4703_reg_map_command(int32_t argc, char* argv[]);
bool si4703_diag_command(int32_t argc, char* argv[]);
bool si4703_reset_command(int32_t argc, char* argv[]);
bool si4703_diag_low_level_command(int32_t argc, char* argv[]);
bool si4703_power_up_command(int32_t argc, char* argv[]);
bool si4703_volume_command(int32_t argc, char* argv[]);

#define SI4703_COMMANDS                                                                     \
    SHELL_CMD("si4703_map", "sim", si4703_reg_map_command, "Si4703RegMap"),                 \
    SHELL_CMD("si4703_xtall_en", "six", si4703_xtall_en_command, "Si4703ExtallEnable"),     \
    SHELL_CMD("si4703_set_freq", "sif", si4703_set_fm_freq_command, "Si4703SetFreq"),       \
    SHELL_CMD("si4703_power", "sip", si4703_power_up_command, "Si4703PowerUp"),             \
    SHELL_CMD("si4703_volume", "siv", si4703_volume_command, "Si4703Volume"),               \
    SHELL_CMD("si4703_rf_seek", "sis",  si4703_rf_seek_command, "Si4703RfSeek"),            \
    SHELL_CMD("si4703_read", "sir", si4703_reg_read_command, "Si4703RegRead"),              \
    SHELL_CMD("si4703_diag", "sid", si4703_diag_command, "Si4703Diag"),                     \
    SHELL_CMD("si4703_diag_ll", "sidl", si4703_diag_low_level_command, "Si4703DiagLowLvl"), \
    SHELL_CMD("si4703_write", "siw", si4703_reg_write_command, "Si4703RegWrite"),           \
    SHELL_CMD("si4703_init", "sii", si4703_init_command, "Si4703Init"),                     \
    SHELL_CMD("si4703_reset", "sit", si4703_reset_command, "Si4703Reset"),


#ifdef __cplusplus
}
#endif

#endif /* SI4703_COMMANDS_H */
