#ifndef CONNECTIVITY_COMMANDS_H
#define CONNECTIVITY_COMMANDS_H

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifdef HAS_INTERFACES_COMMANDS
#include "interfaces_commands.h"
#else
#define INTERFACES_COMMANDS
#endif

#ifndef HAS_CONNECTIVITY
#error "+HAS_CONNECTIVITY"
#endif

#ifndef HAS_CONNECTIVITY_COMMANDS
#error "+HAS_CONNECTIVITY_COMMANDS"
#endif

#ifdef HAS_IPC_COMMANDS
#include "ipc_commands.h"
#else
#define IPC_COMMANDS
#endif

#ifdef HAS_DECADRIVER_COMMANDS
#include "decadriver_commands.h"
#else
#define DECADRIVER_COMMANDS
#endif

#ifdef HAS_DW1000_COMMANDS
#include "dw1000_commands.h"
#else
#define DW1000_COMMANDS
#endif

#ifdef HAS_DWM1000_COMMANDS
#include "dwm1000_commands.h"
#else
#define DWM1000_COMMANDS
#endif

#ifdef HAS_DWM3000_COMMANDS
#include "dwm3000_commands.h"
#else
#define DWM3000_COMMANDS
#endif

#ifdef HAS_DWS3000_COMMANDS
#include "dws3000_commands.h"
#else
#define DWS3000_COMMANDS
#endif

#ifdef HAS_LORA_COMMANDS
#include "sx1262_lora_commands.h"
#else
#define SX1262_LORA_COMMANDS
#endif

#ifdef HAS_RF_COMMANDS
#include "rf_commands.h"
#else
#define RF_COMMANDS
#endif /*HAS_RF*/


#ifdef HAS_TCAN4550_COMMANDS
#include "tcan4550_commands.h"
#include "tcan4550_ti_commands.h"
#else
#define TCAN4550_COMMANDS
#define TCAN4550_TI_COMMANDS
#endif


#ifdef HAS_SX1262_COMMANDS
#include "sx1262_commands.h"
#else
#define SX1262_COMMANDS
#endif

#ifdef HAS_TELEMATIC_COMMANDS
#include "telematic_commands.h"
#else
#define TELEMATIC_COMMANDS
#endif

#ifdef HAS_PROTOCOLS_COMMANDS
#include "protocols_commands.h"
#else
#define PROTOCOLS_COMMANDS
#endif

#define CONNECTIVITY_ASICS_COMMANDS      \
    SX1262_COMMANDS                      \
    SX1262_LORA_COMMANDS                 \
    TCAN4550_TI_COMMANDS                 \
    TCAN4550_COMMANDS                    \
    DW1000_COMMANDS                      \
    DWM1000_COMMANDS                     \
    DWS3000_COMMANDS                     \
    DWM3000_COMMANDS

#define CONNECTIVITY_COMMANDS            \
    INTERFACES_COMMANDS                  \
    PROTOCOLS_COMMANDS                   \
    CONNECTIVITY_ASICS_COMMANDS          \
    DECADRIVER_COMMANDS                  \
    IPC_COMMANDS                         \
    RF_COMMANDS                          \
    TELEMATIC_COMMANDS

#endif /* CONNECTIVITY_COMMANDS_H */
