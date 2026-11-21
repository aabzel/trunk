#ifndef ILI9341_COMMANDS_H
#define ILI9341_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_ILI9341_CUSTOM_COMMANDS
#include "ili9341_custom_commands.h"
#else
#define ILI9341_CUSTOM_COMMANDS
#endif

#ifndef HAS_ILI9341
#error "+ HAS_ILI9341"
#endif

#ifndef HAS_ILI9341_COMMANDS
#error "+ HAS_ILI9341_COMMANDS"
#endif

bool ili9341_read_memory_command(int32_t argc, char* argv[]);
bool ili9341_writer_set_command(int32_t argc, char* argv[]);
bool ili9341_diag_command(int32_t argc, char* argv[]);
bool ili9341_init_command(int32_t argc, char* argv[]);
bool ili9341_cmd_command(int32_t argc, char* argv[]);
bool ili9341_reg_map_command(int32_t argc, char* argv[]);

#define ILI9341_COMMANDS                                                                                          \
        ILI9341_CUSTOM_COMMANDS                                                                                   \
        SHELL_CMD("ili9341_read_memory", "ilirm", ili9341_read_memory_command, "Ili9341ReadMemory"),                           \
        SHELL_CMD("ili9341_writer_set", "iliws", ili9341_writer_set_command, "Ili9341WriterSet"),                           \
        SHELL_CMD("ili9341_cmd", "ilic", ili9341_cmd_command, "Ili9341Cmd"),                           \
        SHELL_CMD("ili9341_diag", "ilid", ili9341_diag_command, "Ili9341Diag"),                           \
        SHELL_CMD("ili9341_init", "ilii", ili9341_init_command, "Ili9341Init"),                           \
        SHELL_CMD("ili9341_reg_map", "ilirm", ili9341_reg_map_command, "Ili9341RawRegs"),

#ifdef __cplusplus
}
#endif

#endif /* ILI9341_COMMANDS_H */
