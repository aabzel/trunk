#ifndef TPA2013D1_COMMANDS_H
#define TPA2013D1_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_TPA2013D1
#error "+ HAS_TPA2013D1"
#endif

#ifndef HAS_TPA2013D1_COMMANDS
#error "+ HAS_TPA2013D1_COMMANDS"
#endif

bool tpa2013d1_init_command(int32_t argc, char* argv[]);
bool tpa2013d1_diag_command(int32_t argc, char* argv[]);

#define TPA2013D1_COMMANDS                                                                            \
        SHELL_CMD("tpa2013d1_diag", "tpad", tpa2013d1_diag_command, "Tpa2013Diag"),                   \
        SHELL_CMD("tpa2013d1_init", "tpai", tpa2013d1_init_command, "Tpa2013Init"),                   \

#ifdef __cplusplus
}
#endif

#endif /* TPA2013D1_COMMANDS_H */
