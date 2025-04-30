#ifndef PROTOCOLS_COMMANDS_H
#define PROTOCOLS_COMMANDS_H

#ifdef HAS_INTERFACES_COMMANDS
#include "interfaces_commands.h"
#else
#define INTERFACES_COMMANDS
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_PROTOCOLS
#error "+HAS_PROTOCOLS"
#endif

#ifndef HAS_PROTOCOLS_COMMANDS
#error "+HAS_PROTOCOLS_COMMANDS"
#endif

#ifdef HAS_CLI_NATIVE_COMMANDS
#include "cli_native_commands.h"
#else
#define CLI_NATIVE_COMMANDS
#endif

#ifdef HAS_DS_TWR_COMMANDS
#include "ds_twr_commands.h"
#else
#define DS_TWR_COMMANDS
#endif

#ifdef HAS_DECAWAVE_COMMANDS
#include "decawave_commands.h"
#else
#define DECAWAVE_COMMANDS
#endif

#ifdef HAS_DECAWAVE_NATIVE_COMMANDS
#include "decawave_native_commands.h"
#else
#define DECAWAVE_NATIVE_COMMANDS
#endif

#ifdef HAS_LOG_COMMANDS
#include "log_commands.h"
#else
#define LOG_COMMANDS
#endif

#ifdef HAS_ISO_TP_COMMANDS
#include "iso_tp_commands.h"
#else
#define ISO_TP_COMMANDS
#endif

#ifdef HAS_RTCM3_COMMANDS
#include "rtcm3_commands.h"
#else
#define RTCM3_COMMANDS
#endif

#ifdef HAS_RDS_COMMANDS
#include "rds_commands.h"
#else
#define RDS_COMMANDS
#endif

#ifdef HAS_TBFP_COMMANDS
#include "tbfp_commands.h"
#else
#define TBFP_COMMANDS
#endif

#ifdef HAS_UBX_COMMANDS
#include "ubx_commands.h"
#else
#define UBX_COMMANDS
#endif

#ifdef HAS_UDS_COMMANDS
#include "uds_commands.h"
#else
#define UDS_COMMANDS
#endif

#ifdef HAS_NMEA_COMMANDS
#include "nmea_commands.h"
#else
#define NMEA_COMMANDS
#endif


#define PROTOCOLS_COMMANDS               \
    CLI_NATIVE_COMMANDS                  \
    DECAWAVE_COMMANDS                    \
    NMEA_COMMANDS                        \
    DECAWAVE_NATIVE_COMMANDS             \
    DS_TWR_COMMANDS                      \
    LOG_COMMANDS                         \
    RDS_COMMANDS                         \
    RTCM3_COMMANDS                       \
    TBFP_COMMANDS                        \
    ISO_TP_COMMANDS                      \
    UBX_COMMANDS                         \
    UDS_COMMANDS

#endif /* PROTOCOLS_COMMANDS_H */
