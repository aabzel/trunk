#ifndef PROTOCOL_COMMANDS_H
#define PROTOCOL_COMMANDS_H

#ifdef HAS_LOG
#include "log.h"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif


#ifdef HAS_CLI_NATIVE_COMMANDS
#include "cli_native_commands.h"
#else
#define CLI_NATIVE_COMMANDS
#endif

#ifndef HAS_PROTOCOLS
#error "+HAS_PROTOCOLS"
#endif

#ifndef HAS_PROTOCOLS_COMMANDS
#error "+HAS_PROTOCOLS_COMMANDS"
#endif

#ifdef HAS_DECADRIVER_COMMANDS
#include "decadriver_commands.h"
#else
#define DECADRIVER_COMMANDS
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

#ifdef HAS_TBFP_COMMANDS
#include "tbfp_commands.h"
#else
#define TBFP_COMMANDS
#endif

#ifdef HAS_RDS_COMMANDS
#include "rds_commands.h"
#else
#define RDS_COMMANDS
#endif

#ifdef HAS_TELEMATIC_COMMANDS
#include "telematic_commands.h"
#else
#define TELEMATIC_COMMANDS
#endif


#define PROTOCOLS_COMMANDS              \
   CLI_NATIVE_COMMANDS                  \
   DECAWAVE_COMMANDS                    \
   DS_TWR_COMMANDS                      \
   NMEA_COMMANDS                        \
   RTCM3_COMMANDS                       \
   RDS_COMMANDS                         \
   UBX_COMMANDS                         \
   TBFP_COMMANDS                        \
   TELEMATIC_COMMANDS                   


#endif /* PROTOCOLS_COMMANDS_H */
