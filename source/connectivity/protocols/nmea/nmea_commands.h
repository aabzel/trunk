#ifndef NMEA_COMMAND_H
#define NMEA_COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool nmea_messages_command(int32_t argc, char* argv[]);
bool nmea_diag_command(int32_t argc, char* argv[]);
bool nmea_data_command(int32_t argc, char* argv[]);
bool nmea_stat_command(int32_t argc, char* argv[]);

#define NMEA_COMMANDS                                                                    \
    SHELL_CMD("nmea_diag", "nmg", nmea_diag_command, "NmeaDiag"),                        \
    SHELL_CMD("nmea_stat", "nms", nmea_stat_command, "NmeaMessage stat"),                \
    SHELL_CMD("nmea_dat", "nmd", nmea_data_command, "NmeaData"),                         \
    SHELL_CMD("nmea_mess", "nmm", nmea_messages_command, "NmeaData"),

#ifdef __cplusplus
}
#endif

#endif /* NMEA_COMMAND_H */
