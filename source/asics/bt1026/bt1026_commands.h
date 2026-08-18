#ifndef BT1026_COMMANDS_H
#define BT1026_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_DIAG
#error "+ HAS_DIAG"
#endif

#ifndef HAS_BT1026
#error "+ HAS_BT1026"
#endif

#ifndef HAS_I2S_DIAG
#error "+ HAS_I2S_DIAG"
#endif

#ifndef HAS_BT1026_COMMANDS
#error "+HAS_BT1026_COMMANDS"
#endif

bool bt1026_reboot_command(int32_t argc, char* argv[]);
bool bt1026_init_command(int32_t argc, char* argv[]);
bool bt1026_diag_command(int32_t argc, char* argv[]);
bool bt1026_pairing_command(int32_t argc, char* argv[]);
bool bt1026_send_command(int32_t argc, char* argv[]);
bool bt1026_play_command(int32_t argc, char* argv[]);
bool bt1026_play_swc_command(int32_t argc, char* argv[]);
bool bt1026_play_swj_command(int32_t argc, char* argv[]);
bool bt1026_i2s_read_command(int32_t argc, char* argv[]);
bool bt1026_reset_command(int32_t argc, char* argv[]);
bool bt1026_get_volume_command(int32_t argc, char* argv[]);
bool bt1026_set_volume_command(int32_t argc, char* argv[]);
bool bt1026_enable_command(int32_t argc, char* argv[]);

#define BT1026_COMMANDS                                                                                                \
    SHELL_CMD("bt1026_enable", "bte", bt1026_enable_command, "Bt1026Enable"),                                          \
    SHELL_CMD("bt1026_reboot", "btb", bt1026_reboot_command, "Bt1026Reboot"),                                          \
    SHELL_CMD("bt1026_pairing", "btpa", bt1026_pairing_command, "Bt1026Pairing"),                                      \
    SHELL_CMD("bt1026_diag", "btd", bt1026_diag_command, "Bt1026Diag"),                                                \
        SHELL_CMD("bt1026_i2s_read", "btr", bt1026_i2s_read_command, "Bt1026I2sRead"),                                 \
        SHELL_CMD("bt1026_play", "btp", bt1026_play_command, "Bt1026Play"),                                            \
        SHELL_CMD("bt1026_play_switch_co", "btpc", bt1026_play_swc_command, "Bt1026PlaySwCopy"),                       \
        SHELL_CMD("bt1026_play_switch_ju", "btpj", bt1026_play_swj_command, "Bt1026PlaySwJump"),                       \
        SHELL_CMD("bt1026_init", "bti", bt1026_init_command, "Bt1026Init"),                                            \
        SHELL_CMD("bt1026_get_vol", "btgv", bt1026_get_volume_command, "Bt1026GetVolume"),                             \
        SHELL_CMD("bt1026_reset", "btt", bt1026_reset_command, "Bt1026Reset"),                                         \
        SHELL_CMD("bt1026_set_vol", "bsv", bt1026_set_volume_command, "Bt1026SetVolume"),                              \
        SHELL_CMD("bt1026_send", "bts", bt1026_send_command, "Bt1026Send"),

#ifdef __cplusplus
}
#endif

#endif /* BT1026_COMMANDS_H */
