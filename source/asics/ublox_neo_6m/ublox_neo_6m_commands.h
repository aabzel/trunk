#ifndef UBLOX_NEO_6M_COMMANDS_H
#define UBLOX_NEO_6M_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool ublox_neo_6m_diag_command(int32_t argc, char* argv[]);

#define UBLOX_NEO_6M_COMMANDS                                                                                               \
    SHELL_CMD("ublox_neo_6m_diag", "zfd", ublox_neo_6m_diag_command, "ZEDF9Pdiag"),                                              \

#ifdef __cplusplus
}
#endif

#endif /* UBLOX_NEO_6M_COMMANDS_H */
