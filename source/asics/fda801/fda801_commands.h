#ifndef FDA801_COMMANDS_H
#define FDA801_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_FDA801
#error "+ HAS_FDA801"
#endif

#ifndef HAS_FDA801_COMMANDS
#error "+ HAS_FDA801_COMMANDS"
#endif

bool fda801_set_clock_command(int32_t argc, char* argv[]);
bool fda801_set_channel_gain_command(int32_t argc, char* argv[]);
bool fda801_get_channel_gain_command(int32_t argc, char* argv[]);
bool fda801_reg_write_command(int32_t argc, char* argv[]);
bool fda801_reg_read_command(int32_t argc, char* argv[]);
bool fda801_init_command(int32_t argc, char* argv[]);
bool fda801_reg_map_command(int32_t argc, char* argv[]);
bool fda801_diag_command(int32_t argc, char* argv[]);
bool fda801_reset_command(int32_t argc, char* argv[]);
bool fda801_channels_command(int32_t argc, char* argv[]);
bool fda801_channel_play_command(int32_t argc, char* argv[]);
bool fda801_diag_channels_command(int32_t argc, char* argv[]);
bool fda801_diag_low_level_command(int32_t argc, char* argv[]);
bool fda801_set_channel_command(int32_t argc, char* argv[]);
bool fda801_set_channel_pwm_command(int32_t argc, char* argv[]);
bool fda801_channel_dc_diag_start_command(int32_t argc, char* argv[]);
bool fda801_ac_diag_command(int32_t argc, char* argv[]);
bool fda801_test_command(int32_t argc, char* argv[]);

#define FDA801_COMMANDS                                                                                                \
    SHELL_CMD("fda801_test", "fdt", fda801_test_command, "Fda801Test"),                                                \
        SHELL_CMD("fda801_chan_set_clock", "fsc", fda801_set_clock_command, "Fda801SetClock"),                         \
        SHELL_CMD("fda801_chan_set_gain", "fscg", fda801_set_channel_gain_command, "Fda801ChanGainSet"),               \
        SHELL_CMD("fda801_chan_gel_gain", "fgcg", fda801_get_channel_gain_command, "Fda801ChanGainGet"),               \
        SHELL_CMD("fda801_chan_play", "fdcp", fda801_channel_play_command, "Fda801ChanPlay"),                          \
        SHELL_CMD("fda801_map", "fdam", fda801_reg_map_command, "Fda801RegMap"),                                       \
        SHELL_CMD("fda801_read", "fdar", fda801_reg_read_command, "Fda801RegRead"),                                    \
        SHELL_CMD("fda801_diag", "fdad", fda801_diag_command, "Fda801Diag"),                                           \
        SHELL_CMD("fda801_diag_ll", "fdadl", fda801_diag_low_level_command, "Fda801DiagLowLvl"),                       \
        SHELL_CMD("fda801_chan", "fdac", fda801_channels_command, "Fda801Channels"),                                   \
        SHELL_CMD("fda801_chan_dc_diag", "fdacdc", fda801_channel_dc_diag_start_command, "Fda801ChannelDcDiagStart"),  \
        SHELL_CMD("fda801_diag_chan", "fdadc", fda801_diag_channels_command, "Fda801DiagChannels"),                    \
        SHELL_CMD("fda801_ac_diag", "fdaac", fda801_ac_diag_command, "Fda801AcDiag"),                                  \
        SHELL_CMD("fda801_write", "fdaw", fda801_reg_write_command, "Fda801RegWrite"),                                 \
        SHELL_CMD("fda801_set_ch", "fdasc", fda801_set_channel_command, "Fda801SetChannel"),                           \
        SHELL_CMD("fda801_set_ch_pwm", "fdascp", fda801_set_channel_pwm_command, "Fda801SetChannelPwm"),               \
        SHELL_CMD("fda801_init", "fdai", fda801_init_command, "Fda801Init"),                                           \
        SHELL_CMD("fda801_reset", "fdat", fda801_reset_command, "Fda801Reset"),

#ifdef __cplusplus
}
#endif

#endif /* FDA801_COMMANDS_H */
