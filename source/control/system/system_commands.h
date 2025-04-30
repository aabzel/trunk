#ifndef SYSTEM_COMMANDS_H
#define SYSTEM_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

bool sys_diag_command(int32_t argc, char* argv[]);
bool sys_rate_command(int32_t argc, char* argv[]);
bool sys_available_interfaces_command(int32_t argc, char* argv[]);

#ifdef HAS_GNSS
bool sys_bypass_nmea_rs232_command(int32_t argc, char* argv[]);

#define SYSTEM_GNSS_COMMANDS                                                                  \
    SHELL_CMD("nmea_rs", "nmrs", sys_bypass_nmea_rs232_command, "Bypass NMEA to RS232"),
#else
#define SYSTEM_GNSS_COMMANDS
#endif

#define SYSTEM_COMMANDS                                                    \
        SYSTEM_GNSS_COMMANDS                                               \
        SHELL_CMD("sys_diag", "sd", sys_diag_command, "SystemDiag"),              \
        SHELL_CMD("sys_if_rates", "rate", sys_rate_command, "Rate"),              \
        SHELL_CMD("sys_if", "if", sys_available_interfaces_command, "AvailableInterface"),

#ifdef __cplusplus
}
#endif

 
#endif /* SYSTEM_COMMANDS_H  */
