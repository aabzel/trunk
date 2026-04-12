#ifndef SW_SD_CARD_COMMANDS_H
#define SW_SD_CARD_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_SW_SD_CARD
#error "+ HAS_SW_SD_CARD"
#endif

#ifndef HAS_SW_SD_CARD_COMMANDS
#error "+ HAS_SW_SD_CARD_COMMANDS"
#endif

bool sw_sd_card_diag_command(int32_t argc, char* argv[]);
bool sw_sd_card_init_command(int32_t argc, char* argv[]);

#define SW_SD_CARD_COMMANDS                                                                                          \
        SHELL_CMD("sw_sd_card_diag", "sdd", sw_sd_card_diag_command, "SwSdCardDiag"),                           \
        SHELL_CMD("sw_sd_card_init", "sdi", sw_sd_card_init_command, "SwSdCardInit"),                           \

#ifdef __cplusplus
}
#endif

#endif /* SW_SD_CARD_COMMANDS_H */
