#ifndef WM8731_COMMANDS_H
#define WM8731_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

bool cmd_wm8731_bypass(int32_t argc, char* argv[]);
bool cmd_wm8731_diag(int32_t argc, char* argv[]);
bool cmd_wm8731_get_reg(int32_t argc, char* argv[]);
bool cmd_wm8731_init(int32_t argc, char* argv[]);
bool cmd_wm8731_reg_map(int32_t argc, char* argv[]);
bool cmd_wm8731_reset(int32_t argc, char* argv[]);
bool cmd_wm8731_set_volume(int32_t argc, char* argv[]);
bool cmd_wm8731_set_sidetone(int32_t argc, char* argv[]);
bool cmd_wm8731_set_reg(int32_t argc, char* argv[]);
bool cmd_wm8731_listen(int32_t argc, char* argv[]);

#define WM8731_RECORD_COMMANDS                                                 \
    SHELL_CMD("wm8731_listen", "wml", cmd_wm8731_listen, "Wm8731Listen"),      \

bool cmd_wm8731_tone(int32_t argc, char* argv[]);
bool cmd_wm8731_1khz(int32_t argc, char* argv[]);

#define WM8731_PLAY_COMMANDS                                                   \
    SHELL_CMD("wm8731_play", "wmp", cmd_wm8731_tone, "Wm8731Play"),            \
    SHELL_CMD("wm8731_1khz", "wmk", cmd_wm8731_1khz, "Wm8731Play1kHz"),

#define WM8731_COMMANDS                                                         \
    WM8731_RECORD_COMMANDS                                                      \
    WM8731_PLAY_COMMANDS                                                        \
    SHELL_CMD("wm8731_bypass", "wmb", cmd_wm8731_bypass, "Wm8731ByPass"),       \
    SHELL_CMD("wm8731_diag", "wmd", cmd_wm8731_diag, "Wm8731Diag"),             \
    SHELL_CMD("wm8731_vol", "wmv", cmd_wm8731_set_volume, "Wm8731SetVol"),      \
    SHELL_CMD("wm8731_side", "wms", cmd_wm8731_set_sidetone, "Wm8731SetSideTone"),   \
    SHELL_CMD("wm8731_init", "wmi", cmd_wm8731_init, "Wm8731Init"),              \
    SHELL_CMD("wm8731_map", "wmm", cmd_wm8731_reg_map, "Wm8731Map"),             \
    SHELL_CMD("wm8731_reset", "wmt", cmd_wm8731_reset, "Wm8731Reset"),           \
    SHELL_CMD("wm8731_read", "wmr", cmd_wm8731_get_reg, "Wm8731GetReg"),         \
    SHELL_CMD("wm8731_write", "wmw", cmd_wm8731_set_reg, "Wm8731SetReg"),
                                                                            

#ifdef __cplusplus
}
#endif

#endif /* WM8731_COMMANDS_H */
