#ifndef CLI_COMMANDS_H
#define CLI_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAS_APPLICATIONS_COMMANDS
#include "applications_commands.h"
#else
#define APPLICATIONS_COMMANDS
#endif



#ifdef HAS_MICROCONTROLLER
#include "microcontroller_commands.h"
#else
#define MICROCONTROLLER_COMMANDS
#endif


#ifdef HAS_BIT_COMMANDS
#include "bit_commands.h"
#else
#define BIT_COMMANDS
#endif

#ifdef HAS_MCAL_COMMANDS
#include "mcal_commands.h"
#else
#define MCAL_COMMANDS
#endif

#ifdef HAS_ASICS_COMMANDS
#include "asics_commands.h"
#else
#define ASICS_COMMANDS
#endif

#ifdef HAS_AES_COMMANDS
#include "aes_commands.h"
#else
#define AES_COMMANDS
#endif /*HAS_AES_COMMANDS*/

#ifdef HAS_CRYP_COMMANDS
#include "cryp_commands.h"
#else
#define CRYP_COMMANDS
#endif

#ifdef HAS_COMPUTING_COMMANDS
#include "computing_commands.h"
#else
#define COMPUTING_COMMANDS
#endif

#ifdef HAS_CONNECTIVITY_COMMANDS
#include "connectivity_commands.h"
#else
#define CONNECTIVITY_COMMANDS
#endif

#ifdef HAS_CONTROL_COMMANDS
#include "control_commands.h"
#else
#define CONTROL_COMMANDS
#endif

#ifdef HAS_MCO_COMMANDS
#include "mco_commands.h"
#else
#define MCO_COMMANDS
#endif

#ifdef HAS_MULTIMEDIA_COMMANDS
#include "multimedia_commands.h"
#else
#define MULTIMEDIA_COMMANDS
#endif

#ifdef HAS_PROTOTYPE_COMMANDS
#include "prototype_commands.h"
#else
#define PROTOTYPE_COMMANDS
#endif

#ifdef HAS_RNG_COMMANDS
#include "rng_commands.h"
#else
#define TRNG_COMMANDS
#endif

#ifdef HAS_GAMES_COMMANDS
#include "games_commands.h"
#else
#define GAMES_COMMANDS
#endif

#ifdef HAS_SENSITIVITY_COMMANDS
#include "sensitivity_commands.h"
#else
#define SENSITIVITY_COMMANDS
#endif

#ifdef HAS_SOFTWARE_TIMER_COMMANDS
#include "software_timer_commands.h"
#else
#define SOFTWARE_TIMER_COMMANDS
#endif


#ifdef HAS_STORAGE_COMMANDS
#include "storage_commands.h"
#else
#define STORAGE_COMMANDS
#endif

#ifdef HAS_FONT_COMMANDS
#include "font_commands.h"
#else
#define FONT_COMMANDS
#endif

#ifdef HAS_THIRD_PARTY_COMMANDS
#include "third_party_commands.h"
#else
#define THIRD_PARTY_COMMANDS
#endif

#define CLI_SECURITY_COMMANDS                                              \
    CRYP_COMMANDS                                                          \
    AES_COMMANDS                                                           \
    TRNG_COMMANDS

#define CLI_COMMANDS                                                       \
    CLI_SECURITY_COMMANDS                                                  \
    ASICS_COMMANDS                                                         \
    BIT_COMMANDS                                                           \
    APPLICATIONS_COMMANDS                                                  \
    CONTROL_COMMANDS                                                       \
    CONNECTIVITY_COMMANDS                                                  \
    COMPUTING_COMMANDS                                                     \
    MICROCONTROLLER_COMMANDS                                               \
    FONT_COMMANDS                                                          \
    GAMES_COMMANDS                                                         \
    MCO_COMMANDS                                                           \
    MCAL_COMMANDS                                                          \
    MULTIMEDIA_COMMANDS                                                    \
    PROTOTYPE_COMMANDS                                                     \
    STORAGE_COMMANDS                                                       \
    SENSITIVITY_COMMANDS                                                   \
    SOFTWARE_TIMER_COMMANDS                                                \
    THIRD_PARTY_COMMANDS                                                   \

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif //CLI_COMMANDS_H
