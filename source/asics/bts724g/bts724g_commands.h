#ifndef BTS724G_COMMANDS_H
#define BTS724G_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"


#ifndef HAS_BTS724G
#error "+ HAS_BTS724G"
#endif

#ifndef HAS_BTS724G_COMMANDS
#error "+ HAS_BTS724G_COMMANDS"
#endif

bool bts724g_test_overtemperature_command(int32_t argc, char* argv[]) ;
bool bts724g_duty_command(int32_t argc, char* argv[]) ;
bool bts724g_diag_command(int32_t argc, char* argv[]);
bool bts724g_frequency_command(int32_t argc, char* argv[]) ;
bool bts724g_init_command(int32_t argc, char* argv[]);
bool bts724g_set_command(int32_t argc, char* argv[]);

#define BTS724G_COMMANDS                                                                                               \
        SHELL_CMD("bts724g_test_overtemperature", "btso", bts724g_test_overtemperature_command, "Bts724gOverTemp"),    \
        SHELL_CMD("bts724g_freq", "btsf", bts724g_frequency_command, "Bts724gFreq"),                                   \
        SHELL_CMD("bts724g_duty", "btsd", bts724g_duty_command, "Bts724gDuty"),                                        \
        SHELL_CMD("bts724g_diag", "btsg", bts724g_diag_command, "Bts724gDiag"),                                        \
        SHELL_CMD("bts724g_set", "btss", bts724g_set_command, "Bts724gSet"),                                           \
        SHELL_CMD("bts724g_init", "btsi", bts724g_init_command, "Bts724gInit"),

#ifdef __cplusplus
}
#endif

#endif /* BTS724G_COMMANDS_H */
