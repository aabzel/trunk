#ifndef SI4737_COMMANDS_H
#define SI4737_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_SI4737
#error "+ HAS_SI4737"
#endif

#ifndef HAS_SI4737_COMMANDS
#error "+ HAS_SI4737_COMMANDS"
#endif

bool si4737_get_rds_command(int32_t argc, char* argv[]);
bool si4737_set_rx_volume_command(int32_t argc, char* argv[]);
bool si4737_set_rf_freq_command(int32_t argc, char* argv[]);
bool si4737_rf_seek_command(int32_t argc, char* argv[]);
bool si4737_property_set_command(int32_t argc, char* argv[]);
bool si4737_property_get_command(int32_t argc, char* argv[]);
bool si4737_init_command(int32_t argc, char* argv[]);
bool si4737_property_map_command(int32_t argc, char* argv[]);
bool si4737_diag_command(int32_t argc, char* argv[]);
bool si4737_reset_command(int32_t argc, char* argv[]);
bool si4737_get_interrupts_command(int32_t argc, char* argv[]);
bool si4737_diag_low_level_command(int32_t argc, char* argv[]);
bool si4737_get_stations_command(int32_t argc, char* argv[]);
bool si4737_set_stations_command(int32_t argc, char* argv[]);
bool si4737_set_hard_mute_command(int32_t argc, char* argv[]);
bool si4737_power_down_command(int32_t argc, char* argv[]);


#define SI4737_COMMANDS                                                                    \
    SHELL_CMD("si4737_get_rds",    "sgr",  si4737_get_rds_command, "Si4737GetRds"), \
    SHELL_CMD("si4737_power_down", "spd",  si4737_power_down_command, "Si4737PowerDown"), \
    SHELL_CMD("si4737_set_hw_mute","shm",  si4737_set_hard_mute_command, "Si4737SetHardMute"), \
    SHELL_CMD("si4737_stations",   "sst",  si4737_get_stations_command, "Si4737GetStations"), \
    SHELL_CMD("si4737_set_stations", "sss",  si4737_set_stations_command, "Si4737SetStations"), \
    SHELL_CMD("si4737_set_vol",    "siv",  si4737_set_rx_volume_command, "Si4737SetRxVol"),\
    SHELL_CMD("si4737_get_int",    "sin",  si4737_get_interrupts_command, "Si4737GetInt"),\
    SHELL_CMD("si4737_rf_seek",    "sis",  si4737_rf_seek_command, "Si4737RfSeek"),        \
    SHELL_CMD("si4737_set_rf_freq","sirf", si4737_set_rf_freq_command, "Si4737SetRfFreq"), \
    SHELL_CMD("si4737_map",        "sim",  si4737_property_map_command,  "Si4737PropMap"), \
    SHELL_CMD("si4737_prop_get",   "sir",  si4737_property_get_command, "Si4737PropRead"), \
    SHELL_CMD("si4737_diag",       "sid",  si4737_diag_command, "Si4737Diag"),             \
    SHELL_CMD("si4737_diag_ll",    "sidl", si4737_diag_low_level_command, "Si4737DiagLowLvl"), \
    SHELL_CMD("si4737_prop_set",   "sps",  si4737_property_set_command, "Si4737PropSet"),  \
    SHELL_CMD("si4737_init",       "sii",  si4737_init_command, "Si4737Init"),             \
    SHELL_CMD("si4737_reset",      "sit",  si4737_reset_command, "Si4737Reset"),

#ifdef __cplusplus
}
#endif

#endif /* SI4737_COMMANDS_H */
